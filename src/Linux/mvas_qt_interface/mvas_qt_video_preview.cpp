/** @file mvas_qt_video_preview.cpp
 *  @brief Sources of the video_preview header
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include "mvas_qt_video_preview.h"

namespace mvas
{
    video_preview::video_preview(QWidget* parent) : QGLWidget(parent)
    {
    }

    void video_preview::resizeEvent(QResizeEvent *event)
    {
        size_t new_width = event->size().width();
        size_t new_height = (new_width/16)*9;
        QWidget::resize(new_width,new_height);
    }
}
