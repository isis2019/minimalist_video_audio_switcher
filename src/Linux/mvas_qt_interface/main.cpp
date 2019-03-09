#include <QApplication>
#include "mvas_qt_main_window.h"
#include "mvas_qt_devices_windows.h"
#include "../include/DeckLinkAPI.h"
#include <iostream>
#include "mvas_qt_toolbar.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    mvas::main_window* w = new mvas::main_window();
    w->show();

    return app.exec();
}
