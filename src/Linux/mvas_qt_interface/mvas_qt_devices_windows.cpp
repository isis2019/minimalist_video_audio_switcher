#include "mvas_qt_devices_windows.h"
#include "../include/DeckLinkAPI.h"

namespace mvas
{
devices_infos_window::devices_infos_window() : QTabWidget()
{
    IDeckLinkIterator*  DeckLinkIterator;
    DeckLinkIterator = CreateDeckLinkIteratorInstance();

    IDeckLink* DeckLink;

    while (DeckLinkIterator->Next(&DeckLink) == S_OK)
    {
        const char* deviceNameString = NULL;
        DeckLink->GetModelName(&deviceNameString);

        const char* displayNameString = NULL;
        DeckLink->GetDisplayName(&displayNameString);

        QString title_info = QString("Device name: ").append(deviceNameString).append('\n').append("Display name: ").append(displayNameString);
        this->addTab(new QLabel(title_info) ,deviceNameString);
    }
}

devices_error_window::devices_error_window() : QWidget()
{
    QMessageBox::information(this, "Error", "Aucune carte vidéo détecter");
}
}
