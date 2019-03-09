/** @file mvas_qt_main_window.cpp
 *  @brief Sources from the interface main_window
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#include "mvas_qt_main_window.h"

namespace mvas
{
    main_window::main_window() : QMainWindow(nullptr)
    {
        set_graphics();
        init_widgets();
        set_widgets_layout();
        connect_widgets();
        listen_arduino_panel();
    }

    void main_window::init_widgets()
    {
        m_video_gui = new video_interface(this);
        m_audio_gui = new audio_interface(this);
        m_exit = new QToolButton(this);
            m_exit->setText("X");
            m_tb = new toolbar(this);
    }

    int main_window::set_graphics()
    {
        const char* main_stylesheet = mvas::load_stylesheet(get_src_path().append("/Linux/mvas_qt_interface/stylesheets/mvas_main_window.css").c_str());

        if(main_stylesheet)
            setStyleSheet(main_stylesheet);
        else
            return MVAS_ERR_FILE_NOT_FOUND;

        QPalette palette = QPalette();
        palette.setColor(QPalette::Background, QColor(20,18,18));
        setPalette(palette);

        setWindowFlags(Qt::CustomizeWindowHint);

        return MVAS_ERR_SUCCESS;
    }

    void main_window::set_widgets_layout()
    {
        QWidget* proxy = new QWidget(this);
        QGridLayout* layout = new QGridLayout(this);
            layout->addWidget(m_video_gui,1,1);
            proxy->setLayout(layout);

        QHBoxLayout* main_layout = new QHBoxLayout(this);
        main_layout->addWidget(m_exit);
        main_layout->addWidget(m_audio_gui);
        main_layout->addWidget(proxy);

        QVBoxLayout* top_layout = new QVBoxLayout(this);
        top_layout->addWidget(m_tb);
        top_layout->addLayout(main_layout);

        QWidget* proxy2 = new QWidget(this);
            proxy2->setLayout(top_layout);
        setCentralWidget(proxy2);
    }

    void main_window::connect_widgets()
    {
        connect(m_exit, SIGNAL(clicked(bool)), this, SLOT(shutdown()));
    }

    int main_window::listen_arduino_panel()
    {
        if(const char* panel_path = m_driver.open_panel_port().c_str())
        {
            printf("path to panel:%s\n", panel_path);
            fflush(stdout);
        }
        else
            return MVAS_ERR_ARDUINO_PANEL_NOT_FOUND;

        QtConcurrent::run(&m_driver, &panel_driver::listen_to_port);

        QTimer* timer = new QTimer(this);
        timer->setInterval(10);
        connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
        timer->start();

        return MVAS_ERR_SUCCESS;
    }

    void main_window::refresh()
    {
        static uint16_t old_ratio = 0;
        uint16_t ratio = (100.0f/1024.0f) * (float)m_driver.values.tbar;
        if(old_ratio != ratio)
        {
            m_video_gui->m_tbar->setValue(ratio);
            old_ratio = ratio;

            char buff[4] = {0};
            buff[0] = 'T';
            std::memcpy(buff+1,&ratio,2);
            buff[3] = '\0';
            m_driver.write_to_panel_port(buff);
        }

        static uint8_t old_prg = 0;
        if(old_prg != m_driver.values.prg_but_pressed)
        {
            for(size_t i=0; i<MVAS_PRG_BUT_COUNT; i++)
                m_video_gui->m_prg_buts[i]->setDown(false);

            m_video_gui->m_prg_buts[m_driver.values.prg_but_pressed-MVAS_PRG1_PIN]->setDown(true);
            old_prg = m_driver.values.prg_but_pressed;
        }

        static uint8_t old_potars[MVAS_AUDIO_SLICE_COUNT] = {0};
        for(size_t i=0; i<MVAS_AUDIO_SLICE_COUNT; i++)
        {
            if(old_potars[i] != m_driver.values.potars[i])
            {
                m_audio_gui->m_audio_slices[i]->m_pan->setValue((100.0f/1024.0f) * (float)m_driver.values.potars[i]);
            }
        }
    }

    void main_window::shutdown()
    {
        m_driver.close_panel_port();
        qApp->exit();
    }

}


