/** @file mvas_qt_video_preview.h
 *  @brief Describe an opengl widget for visualizing the video sources
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <QtOpenGL>
#include <iostream>

namespace mvas
{
    /**
     * @class video_preview
     * @brief Define a widget for previewing the source and manipulating those
     */
    class video_preview : public QGLWidget
    {
    public:
        /**
         * @brief video_preview Parameter constructor
         * @param parent Widget's parent
         */
        video_preview(QWidget* parent);

    public:
        /**
         * @brief resizeEvent call when the window is resized, it is used for
         * keeping the video aspect ratio (16:9)
         * @param event
         */
        void resizeEvent(QResizeEvent* event);
    };
}
