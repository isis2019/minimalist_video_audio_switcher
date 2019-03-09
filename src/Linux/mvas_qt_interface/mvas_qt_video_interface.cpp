/** @file mvas_qt_video_interface.cpp
 *  @brief Sources from the mvas_qt_interface.h
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include "mvas_qt_video_interface.h"

namespace mvas
{
    video_interface::video_interface(QWidget* parent) : QWidget(parent)
    {
        init_widgets();
        set_widgets_layout();
        connect_widgets();
    }

    void video_interface::init_widgets()
    {
        m_prw = new video_preview(this);
        m_prg = new video_preview(this);

        for(size_t i=0; i<MVAS_PRG_BUT_COUNT; i++)
        {

            QString button_title("PG");
            button_title.append(QString::number(i+1));
            m_prg_buts[i] = new QPushButton(button_title,this);
        }

        for(size_t i=0; i<MVAS_PRW_BUT_COUNT; i++)
        {
            QString button_title("PW");
            button_title.append(QString::number(i+1));
            m_prw_buts[i] = new QPushButton(button_title,this);
        }

        m_tbar = new QSlider(Qt::Vertical, this);

        m_cut = new QPushButton("CUT",this);
        m_auto_trans = new QPushButton("AUTO-TRANS",this);
        m_ftb = new QPushButton("FTB",this);

        m_tbar_txt = new QLabel(this);
            m_tbar_txt->setText("00%");
    }

    void video_interface::set_widgets_layout()
    {

        QHBoxLayout* screens = new QHBoxLayout(this);
        screens->addWidget(m_prw);
        screens->addWidget(m_prg);
        QGridLayout* layout = new QGridLayout(this);
        for(size_t i=0; i<MVAS_PRG_BUT_COUNT; i++)
        {
            layout->addWidget(m_prg_buts[i],1,i);
            layout->addWidget(m_prw_buts[i],2,i);
        }
        layout->addWidget(m_tbar,1,MVAS_PRG_BUT_COUNT,3,1);
        layout->addWidget(m_tbar_txt,5,MVAS_PRG_BUT_COUNT);
        layout->addWidget(m_cut,3,MVAS_PRG_BUT_COUNT+1);
        layout->addWidget(m_auto_trans,2,MVAS_PRG_BUT_COUNT+1);
        layout->addWidget(m_ftb,1,MVAS_PRG_BUT_COUNT+1);

        QWidget* prox1 = new QWidget(this);
        QWidget* prox2 = new QWidget(this);

        prox1->setLayout(screens);
        prox2->setLayout(layout);

        QVBoxLayout* main_layout = new QVBoxLayout(this);
        main_layout->addWidget(prox1);
        main_layout->addWidget(prox2);

    }

    void video_interface::connect_widgets()
    {
        connect(m_tbar, &QSlider::valueChanged, [this](const int value)
        {
            m_tbar_txt->setText(QString::number(value).append("%"));

            if(value < 10)
                m_tbar_txt->setText(QString("0").append(QString::number(value).append("%")));
        });
    }
}
