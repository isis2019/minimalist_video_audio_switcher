#include "mvas_qt_toolbar.h"
#include <QPushButton>

namespace mvas
{
    toolbar::toolbar(blackmagic_decklink_driver* bm_driver, QWidget*parent)
        : QMenuBar(parent),
          m_bm_driver(bm_driver)
    {
        init_widgets();
        organize_widgets();
        connect_widgets();
    }

    void toolbar::init_widgets()
    {
        m_devices = new QMenu("Devices", this);
        m_infos_video_action = new QAction("Infos video");
        m_infos_audio_action = new QAction("Infos audio");
    }

    void toolbar::organize_widgets()
    {
        addMenu(m_devices);
        m_devices->addAction(m_infos_video_action);
        m_devices->addAction(m_infos_audio_action);
    }

    void toolbar::connect_widgets()
    {
        connect(m_infos_video_action, SIGNAL(triggered()), this, SLOT(show_decklink_infos()));
    }

    void toolbar::show_decklink_infos()
    {
        if(m_bm_driver->infos.model_names.size())
        {
            devices_infos_window* infos = new devices_infos_window(m_bm_driver,this);
            infos->show();
        }
        else
        {
            QErrorMessage* err = new QErrorMessage(this);
            err->showMessage(get_error_name(MVAS_ERR_DECKLINK_NOT_FOUND).c_str());
        }
    }
}
