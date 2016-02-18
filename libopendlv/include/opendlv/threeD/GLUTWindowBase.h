/**
 * OpenDLV - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifndef HESPERIA_THREED_GLUTWINDOWBASE_H_
#define HESPERIA_THREED_GLUTWINDOWBASE_H_

#include <GL/gl.h>
#include <GL/glut.h>

#include "opendlv/threeD/FrameCounter.h"

namespace opendlv {
    namespace threeD {

    /**
     * This class provides an interface for GLUT callback functions. Since methods cannot be
     * used as callback functions, this template class provides static methods that can be used
     * instead. Calls to the static callback methods are delegated to the non-static versions.
     * Note: This will not work properly if there is more than one instance of the same class.
     *
     * class VisualisationWindow : public GLUTCallbackBase<VisualisationWindow>
     * {
     *     VisualisationWindow() : GLUTCallbackBase<VisualisationWindow>(this)
     *     {
     *          // Your own GLUT init stuff
     *          setupGLUTCallbacks()
     *          // ...
     *     }
     * }
     */

    template< class T > class GLUTWindowBase
    {
            public:
                /**
                 * The constructs takes a pointer to the one and
                 * only instance of a child class of GLUTWindowBase<T>
                 * where T is the type of the child class. This pointer
                 * is used to delegate calls from the static callback
                 * methods to the implemented pure virtual methods in
                 * the child class.
                 */
                GLUTWindowBase(T* instance)
                {
                    m_instance = instance;
                    m_frameCounter = FrameCounter();
                }

                virtual ~GLUTWindowBase() {
                    m_instance = NULL;
                }

                /**
                 * Registers the static callback methods to GLUT. This
                 * needs to be done exactly one time before entering
                 * the GLUT mainloop.
                 */
                void setupGLUTCallbacks() {
                    glutDisplayFunc( T::DisplayFunc );
                    glutIdleFunc( T::IdleFunc );
                    glutReshapeFunc( T::ReshapeFunc );
                    glutKeyboardFunc( T::KeyboardFunc );
                    glutMotionFunc( T::MotionFunc );
                    glutMouseFunc( T::MouseFunc );
                }

                /**
                 * Implement this method to render the scene.
                 */
                virtual void render() = 0;

                /**
                 * This method is called by the GLUT main loop. Just return if
                 * you want maximum frame rate, call GLUTWindowBase::lockFrameRate()
                 * or do something different to adjust the frame rate.
                 */
                virtual void doIdle() = 0;

                /**
                 * Implement this method to handle window resizing
                 *
                 * @param w new width.
                 * @param h new height.
                 */
                virtual void resize(int32_t w, int32_t h) = 0;

                /**
                 * Implement this method to process any key event.
                 *
                 * @param key The pressed key.
                 * @param x
                 * @param y
                 */
                virtual void processKey(unsigned char key, int32_t x, int32_t y) = 0;

                /**
                 * Implement this method to process any mouse motion event.
                 *
                 * @param x Mouse's X position.
                 * @param y Mouse's Y position.
                 */
                virtual void processMouseMotion(int32_t x, int32_t y) = 0;

                /**
                 * Implement this method to process any mouse event.
                 *
                 * @param button The pressed mouse button.
                 * @param state GLUT_DOWN or GLUT_UP.
                 * @param x Mouse's X position.
                 * @param y Mouse's Y position.
                 */
                virtual void processMouseEvent(int32_t button, int32_t state, int32_t x, int32_t y) = 0;

                /**
                 * This method can be called from within the doIdle()-methode to
                 * provide a fixed frame rate. It basicly waits 1000ms/fps between two
                 * frames, so it will not work properly if the hardware is not capable
                 * of rendering the scene with the desired framerate.
                 */
                void lockFrameRate(const uint32_t fps) {
                    usleepFor(1000*(1000/fps));
                }

                /**
                 * Returns the current frames per second.
                 */
                double getFramesPerSecond() {
                    return m_frameCounter.getFPS();
                }

                /**
                 * Callback function for glutDisplayFunc(). Delegates a call
                 * to GLUTWindowBase::render().
                 */
                static void DisplayFunc() {
                    m_frameCounter.update();
                    m_instance->render();
                    glutSwapBuffers();
                }

                static void IdleFunc() {
                    m_instance->doIdle();
                    glutPostRedisplay();
                }

                /**
                 * Callback function for glutReshapeFunc(). Delegates a call
                 * to GLUTWindowBase::resize().
                 */
                static void ReshapeFunc(int32_t w, int32_t h) {
                    m_instance->resize(w,h);
                    glutPostRedisplay();
                }

                /**
                 * Callback function for glutKeyboardFunc(). Delegates a call
                 * to GLUTWindowBase::processKey()
                 */
                static void KeyboardFunc(unsigned char key, int32_t x, int32_t y) {
                    m_instance->processKey(key, x, y);
                    glutPostRedisplay();
                }

                /**
                 * Callback function for glutMotionFunc(). Delegates a call
                 * to GLUTWindowBase::processMouseMotion().
                 */
                static void MotionFunc(int32_t x, int32_t y) {
                    m_instance->processMouseMotion(x,y);
                    glutPostRedisplay();
                }

                /**
                 * Callback function for glutMouseFunc(). Delegates a call
                 * to GLUTWindowBase::processMouseEvent.
                 */
                static void MouseFunc(int32_t button, int32_t state, int32_t x, int32_t y) {
                    m_instance->processMouseEvent(button, state, x, y);
                    glutPostRedisplay();
                }

            protected:
                static T* m_instance;
                static FrameCounter m_frameCounter;
        };

    template< typename T> T* GLUTWindowBase<T>::m_instance = NULL;
    template< typename T> FrameCounter GLUTWindowBase<T>::m_frameCounter = FrameCounter();
    }
}
#endif // HESPERIA_THREED_GLUTCALLBACKBASE_H_
