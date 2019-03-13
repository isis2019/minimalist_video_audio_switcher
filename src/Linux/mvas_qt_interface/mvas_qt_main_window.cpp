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
        std::cout << "Set Graphics: " << get_error_name(set_graphics()) << std::flush;
        init_widgets();
        set_widgets_layout();
        connect_widgets();
        std::cout << "Listenning Arduino: " << get_error_name(listen_arduino_panel()) << std::flush;
    }

    void main_window::init_widgets()
    {
        setFixedSize(QApplication::desktop()->screenGeometry().width()*0.9f,
                       QApplication::desktop()->screenGeometry().height()*0.5f);
        m_video_gui = new video_interface(this);
        m_audio_gui = new audio_interface(this);
        m_tb = new toolbar(this);
            m_tb->setMaximumHeight(m_tb->m_device->height());
    }

    int main_window::set_graphics()
    {
        std::string main_stylesheet = mvas::load_stylesheet(get_src_path().append("/Linux/mvas_qt_interface/stylesheets/mvas_main_window.css").c_str());

        if(main_stylesheet != "")
            setStyleSheet(main_stylesheet.c_str());
        else
            return MVAS_ERR_FILE_NOT_FOUND;

        QPalette palette = QPalette();
        palette.setColor(QPalette::Background, QColor(20,18,18));
        setPalette(palette);

        return MVAS_ERR_SUCCESS;
    }

    void main_window::set_widgets_layout()
    {
        QWidget* proxy = new QWidget(this);
        QGridLayout* layout = new QGridLayout(proxy);
        layout->addWidget(m_tb,0,0,1,2);
        layout->addWidget(m_audio_gui,1,0,1,1);
        layout->addWidget(m_video_gui,1,1,1,1,Qt::AlignHCenter);
        setCentralWidget(proxy);
    }

    void main_window::connect_widgets()
    {
    }

    int main_window::listen_arduino_panel()
    {
        std::string panel_path = m_driver.open_panel_port().c_str();
        if(panel_path.size())
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


