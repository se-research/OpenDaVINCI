/**
 * odplayer.h264 - Tool for playing back recorded data and videos encoded in h264
 * Copyright (C) 2016 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

// Include files to open a capturing device.
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

bool getNextFrame();
int fillBuffer();
bool update(bool &readMoreBytes);
void decodeFrame(uint8_t* data, int size);
void nextFrameReady(AVFrame* frame);


// Image dimensions.
const int width = 640;
const int height = 480;
const uint32_t BUFFER_SIZE = 16384;

// Buffer to read from video file.
uint8_t inbuf[BUFFER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];
// Internal buffer to handle processed and unprocessed data.
std::vector<uint8_t> buffer;

// Handle to input file.
FILE *f;

// Decoder context.
AVCodecContext *decodeContext = NULL;

// Parser for decoding.
AVCodecParserContext* parser = NULL;

// Picture will hold the decoded picture.
AVFrame* picture = NULL;

// Image pixel transformation context.
SwsContext *pixelTransformationContext = NULL;

// OpenCV uses BGR pixel format; thus, we need to transform the data from the decoder.
AVFrame *frameBGR = NULL;

void nextFrameReady(AVFrame* frame) {
    static uint32_t frameCounter = 0;

    frameCounter++;
    cout << "Call back for frame = " << frameCounter << endl;

    sws_scale(pixelTransformationContext, frame->data, frame->linesize, 0, height, frameBGR->data, frameBGR->linesize);
    cv::Mat cvFrame(height, width, CV_8UC3, frameBGR->data[0], frameBGR->linesize[0]);

    //display and delay
    cv::imshow("player", cvFrame);
    cv::waitKey(10);
}

bool getNextFrame() {
    bool readMore = false;

    while (!update(readMore)) {
        if (readMore) {
            fillBuffer();
        }
        if (feof(f)) {
            return false;
        }
    }

    return true;
}

int fillBuffer() {
    int nbytes = (int)fread(inbuf, 1, BUFFER_SIZE, f);

    if (nbytes) {
        copy(inbuf, inbuf + nbytes, back_inserter(buffer));
    }

    return nbytes;
}

bool update(bool &readMoreBytes) {
    readMoreBytes = false;

    if (feof(f)) {
        return false;
    }

    if (!f) {
        cout << "Cannot read from file." << endl;
        return false;
    }

    if (buffer.size() == 0) {
        readMoreBytes = true;
        return false;
    }
 
    uint8_t* data = NULL;
    int size = 0;
    int len = av_parser_parse2(parser, decodeContext, &data, &size, &buffer[0], buffer.size(), 0, 0, AV_NOPTS_VALUE);

    if (size == 0 && len >= 0) {
        readMoreBytes = true;
        return false;
    }

    if (len) {
        decodeFrame(&buffer[0], size);
        buffer.erase(buffer.begin(), buffer.begin() + len);
        return true;
    }

    return false;
}

void decodeFrame(uint8_t* data, int size) {
    AVPacket packet;
    int gotPicture = 0;
    int len = 0;

    av_init_packet(&packet);
    packet.data = data;
    packet.size = size;

    len = avcodec_decode_video2(decodeContext, picture, &gotPicture, &packet);
    if (len < 0) {
        cout << "Error while decoding a frame." << endl;
    }

    if (gotPicture) {
        nextFrameReady(picture);
    }
}


int32_t main(int32_t /*argc*/, char **/*argv*/) {
    string inputFilename = "output.mp4";

    // Register all codecs from FFMPEG.
    avcodec_register_all();

    // Show a window to display images.
    cv::namedWindow("player");

    // Allocating memory to hold resulting image.
    frameBGR = av_frame_alloc();
    if (!frameBGR) {
        cout << "Could not allocate buffer for resulting frame." << endl;
        return -1;
    }

    // Acquire memory for raw picture.
    const uint32_t bytes = avpicture_get_size(PIX_FMT_BGR24, width, height);
    uint8_t *buf = static_cast<uint8_t*>(av_malloc(bytes * sizeof(uint8_t)));
    avpicture_fill((AVPicture *)frameBGR, buf, PIX_FMT_BGR24, width, height);

    // Image pixel transformation context.
    pixelTransformationContext = sws_getContext(width, height,
                         AV_PIX_FMT_YUV420P, width, height,
                         AV_PIX_FMT_BGR24, 0, 0, 0, 0);

    // Find proper decoder for h264.
    AVCodec *decodeCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!decodeCodec) {
        cout << "Codec h264 not found." << endl;
        return -1;
    }

    // Configure decoding context.
    decodeContext = avcodec_alloc_context3(decodeCodec);

    // Allow partial data handover to decoder.
    if (decodeCodec->capabilities & CODEC_CAP_TRUNCATED) {
        decodeContext->flags |= CODEC_FLAG_TRUNCATED;
    }

    // Open codec.
    if (avcodec_open2(decodeContext, decodeCodec, NULL) < 0) {
        cout << "Could not open codec h264 with given parameters." << endl;
        return -2;
    }

    // Open video file.
    f = fopen(inputFilename.c_str(), "rb");
    if (!f) {
        cout << "Could not open " << inputFilename << endl;
        return -3;
    }

    // Allocate picture.
    picture = av_frame_alloc();

    // Initialize parser.
    parser = av_parser_init(AV_CODEC_ID_H264);
    if (!parser) {
        cout << "Could not create H264 parser." << endl;
        return -4;
    }

    // Fill buffer.
    fillBuffer();

    // Process entire file.
    while (getNextFrame());

    // Cleanup.
    av_parser_close(parser);
    avcodec_close(decodeContext);
    av_free(decodeContext);
    av_free(picture);
    fclose(f);

    return 0;
}
