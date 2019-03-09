#include <QApplication>
#include "mvas_qt_main_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    mvas::main_window* w = new mvas::main_window();
    w->show();
    return app.exec();
}
