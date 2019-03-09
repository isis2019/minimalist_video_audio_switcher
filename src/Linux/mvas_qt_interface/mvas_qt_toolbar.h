#pragma once
#include <QMenuBar>
#include "../include/DeckLinkAPI.h"
#include "mvas_qt_devices_windows.h"

namespace mvas
{
    class toolbar : public QMenuBar
    {
        Q_OBJECT

    private:
        QMenu* m_device;

    public:
        toolbar(QWidget*parent);

    public slots:
        void check_decklink();
    };
}
