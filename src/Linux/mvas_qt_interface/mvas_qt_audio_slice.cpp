/** @file mvas_qt_audio_slice.cpp
 *  @brief Contains sources of mvas_qt_audio_slice.h
 *  @author Mohammed Khalil El Kasmi
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include"mvas_qt_audio_slice.h"

namespace mvas
{
     audio_slice::audio_slice(QWidget *parent):QWidget(parent)
     {
         m_pan  = new QDial(this);
         m_pan->setFixedSize(size().width()*0.5,
                             size().width()*0.5);
         m_slider = new QSlider(this);
         m_mute = new QPushButton("m", this);
         m_mute->setFixedSize(size().width()*0.3,
                              size().width()*0.3);

         QGridLayout* layout = new QGridLayout(this);
         layout->addWidget(m_pan,0,0,Qt::AlignHCenter);
         layout->addWidget(m_mute,1,0,Qt::AlignHCenter);
         layout->addWidget(m_slider,2,0,Qt::AlignHCenter);
     }
}

