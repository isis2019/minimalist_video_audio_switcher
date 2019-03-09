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
        setFixedSize(1920/5,1080/5);
    }
}
