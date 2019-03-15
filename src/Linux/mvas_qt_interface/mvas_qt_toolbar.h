#pragma once
#include <QMenuBar>
#include <QErrorMessage>
#include "../include/DeckLinkAPI.h"
#include "mvas_qt_devices_windows.h"

namespace mvas
{
    class toolbar : public QMenuBar
    {
        Q_OBJECT

    private:
        blackmagic_decklink_driver* m_bm_driver;
        QMenu* m_devices;
        QAction* m_infos_video_action;
        QAction* m_infos_audio_action;

    public:
        toolbar(blackmagic_decklink_driver* bm_driver, QWidget*parent);

        void init_widgets();
        void organize_widgets();
        void connect_widgets();

    public slots:
        void show_decklink_infos();

        friend class main_window;
    };
}
