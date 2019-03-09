#include "mvas_qt_toolbar.h"

namespace mvas
{

toolbar::toolbar(QWidget*parent) : QMenuBar(parent)
{
    m_device = addMenu("Device");
    m_device->addAction("Infos");
    m_device->addAction("Configure");

    connect(m_device, SIGNAL(triggered(QAction*)), this, SLOT(check_decklink()));
}

void toolbar::check_decklink()
{
    IDeckLinkIterator*  DeckLinkIterator;
    DeckLinkIterator = CreateDeckLinkIteratorInstance();
    IDeckLink* DeckLink;

    if (DeckLinkIterator == NULL)
    {
        devices_error_window* err_window = new devices_error_window();
        err_window->show();
    }

    else
    {
        devices_infos_window* inf_window = new devices_infos_window();
        inf_window->show();
    }
}

}
