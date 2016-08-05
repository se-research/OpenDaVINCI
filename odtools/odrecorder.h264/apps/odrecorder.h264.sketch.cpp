/**
 * odrecorder.h264 - Tool for recording data and encoding video streams with h264.
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
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

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

int32_t main(int32_t /*argc*/, char **/*argv*/) {
    const bool lossless = true;
    string outputFilename = "output.mp4";

    // Use OpenCV to grab images from camera.
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "Failed to open capturing device." << endl;
        return -1;
    }

    // Show a window to display images.
    cv::namedWindow("recorder");

    // Specify image dimensions.
    const uint32_t width = 640;
    const uint32_t height = 480;

    // Register all codecs from FFMPEG.
    avcodec_register_all();

    // Find proper encoder for h264.
    AVCodec *encodeCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!encodeCodec) {
        cout << "Codec h264 not found." << endl;
        return -2;
    }

    // Configure encoding context.
    AVCodecContext *encodeContext = avcodec_alloc_context3(encodeCodec);
    encodeContext->width = width;
    encodeContext->height = height;
    encodeContext->pix_fmt = AV_PIX_FMT_YUV420P; // Pixel format.

    // Setup h264-specific parameters.
    AVDictionary *param = NULL;
    if (lossless) {
        av_dict_set(&param, "qp", "0", 0);
    }
    av_dict_set(&param, "preset", "ultrafast", 0);

    // Try to open codec.
    if (avcodec_open2(encodeContext, encodeCodec, &param) < 0) {
        cout << "Could not open codec h264 with given parameters." << endl;
        return -3;
    }

    // Setup output file.
    FILE *f = fopen(outputFilename.c_str(), "wb");
    if (!f) {
        cout << "Could not open " << outputFilename << endl;
        return -4;
    }

    // Allocate memory to transfer raw uncompressed image data to encoder.
    AVFrame *frame = av_frame_alloc();
    if (!frame) {
        cout << "Could not allocate video frame." << endl;
        return -5;
    }
    frame->width  = encodeContext->width;
    frame->height = encodeContext->height;
    frame->format = encodeContext->pix_fmt;

    // Allocate raw picture buffer.
    int ret = av_image_alloc(frame->data, frame->linesize, encodeContext->width, encodeContext->height, encodeContext->pix_fmt, 32);
    if (ret < 0) {
        cout << "Could not allocate raw picture buffer." << endl;
        return -6;
    }

    // Image pixel transformation context.
    SwsContext *pixelTransformationContext = sws_getContext(width, height,
                                              AV_PIX_FMT_BGR24, width, height,
                                              AV_PIX_FMT_YUV420P, 0, 0, 0, 0);

    // Matrix to store capture video frame.
    cv::Mat cvFrame;


    // Now, start the actual encoding.
    int succeeded = 0;
    int frameCounter = 0;
    while (true) {
        // This variable contains the encoded packets to be written to file.
        AVPacket packet;
        av_init_packet(&packet);
        packet.data = NULL;
        packet.size = 0;

        // Frame counter.
        frame->pts = frameCounter;

        // Grab next frame from camera.
        {
            capture >> cvFrame;
            if (cvFrame.empty()) {
                cout << "Error grabbing frame." << endl;
                break;
            }

            // Display grabbed frame.
            cv::imshow("recorder", cvFrame);
            if (cv::waitKey(10) > 0) {
                // Did the user press a key to stop recording?
                break;
            }

            // Transform frame from BGR to YUV420P for encoding.
            {
                uint8_t *inData[1] = { cvFrame.data };
                int inLinesize[1] = { 3*width };
                sws_scale(pixelTransformationContext, inData, inLinesize, 0, height, frame->data, frame->linesize);
            }
        }

        // Encoding image.
        ret = avcodec_encode_video2(encodeContext, &packet, frame, &succeeded);
        if (ret < 0) {
            cout << "Error encoding frame." << endl;
            return -7;
        }
        if (succeeded) {
            cout << "Writing frame " << frameCounter++ << ", size = " << packet.size << endl;
            fwrite(packet.data, 1, packet.size, f);
            // Release packet.
            av_free_packet(&packet);
        }
    }

    // Process any delayed frames in the encoder (feeding NULL images).
    for (succeeded = 1; succeeded; frameCounter++) {
        AVPacket packet;
        av_init_packet(&packet);
        packet.data = NULL;
        packet.size = 0;

        // Feeding NULL to indicate end-of-stream.
        ret = avcodec_encode_video2(encodeContext, &packet, NULL, &succeeded);
        if (ret < 0) {
            cout << "Error encoding frame." << endl;
            return -8;
        }
        if (succeeded) {
            cout << "Writing frame " << frameCounter++ << ", size = " << packet.size << endl;
            fwrite(packet.data, 1, packet.size, f);
            av_free_packet(&packet);
        }
    }

    // Close file.
    fclose(f);

    // Cleanup.
    avcodec_close(encodeContext);
    av_free(encodeContext);
    av_freep(&frame->data[0]);
    av_frame_free(&frame);

    return 0;
}

