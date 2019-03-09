/** @file mvas_qt_audio_slice.cpp
 *  @brief Contains sources of mvas_qt_audio_slice.h
 *  @author Mohammed Khalil El Kasmi
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include"mvas_qt_audio_slice.h"

namespace mvas
{
     audio_slice::audio_slice(const QString& title, QWidget *parent):QWidget(parent)
     {
         m_title = new QLabel(title,this);
         m_pan  = new QDial(this);
         m_slider = new QSlider(this);
         m_mute = new QPushButton("mute", this);

         QVBoxLayout* layout = new QVBoxLayout(this);
         layout->addWidget(m_title);
         layout->addWidget(m_pan);
         layout->addWidget(m_mute);
         layout->addWidget(m_slider);
         setLayout(layout);
     }
}

