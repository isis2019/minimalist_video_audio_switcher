/** @file mvas_qt_audio_interface.cpp
 *  @brief Contains the source of mvas_qt_audio_interface.h
 *  @author Mohammed Khalil El Kasmi
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include"mvas_qt_audio_interface.h"

namespace mvas
{
     audio_interface::audio_interface(QWidget *parent):QWidget(parent)
     {
        QHBoxLayout* layout=new QHBoxLayout(this);
        for (int i=0; i<4; i++)
        {
            m_audio_slices[i]=new audio_slice(QString("in ").append(QString::number(i+1)),this);
            layout->addWidget(m_audio_slices[i]);
        }

        m_audio_slices[4]=new audio_slice("AUX",this);
        layout->addWidget(m_audio_slices[4]);
        m_audio_slices[5]=new audio_slice("L",this);
        layout->addWidget(m_audio_slices[5]);
        m_audio_slices[6]=new audio_slice("R",this);
        layout->addWidget(m_audio_slices[6]);
        setLayout(layout);
     }
}

