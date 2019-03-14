#pragma once

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTableWidget>
#include <QMainWindow>
#include <QString>
#include <QChar>
#include <iostream>
#include <QTextBrowser>

using namespace std;

namespace mvas
{

class devices_infos_window: public QTabWidget
{
public:
    devices_infos_window();

};

class devices_error_window: public QWidget
{
private:
    QPushButton* m_boutonDialogue_error;

public:
    devices_error_window();
};

class MyTextBrowser : public QTextBrowser
{
// ...
protected:
    void mousePressEvent(QMouseEvent *mouseEvent);
// ...
};

}


