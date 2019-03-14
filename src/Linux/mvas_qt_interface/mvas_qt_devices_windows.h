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

#include "../mvas_blackmagic_decklink/mvas_blackmagic_decklink.h"

namespace mvas
{

/**
 * @class devices_infos_window
 * @brief The devices_infos_window class
 */
class devices_infos_window: public QTabWidget
{
private:
    /** Handle the blackmagic decklink card **/
    blackmagic_decklink_driver m_driver;

public:
    /**
     * @brief devices_infos_window Default constructor
     */
    devices_infos_window();

public:
    /**
     * @brief init_widgets initialize qt widgets
     */
    void init_widgets();

    /**
     * @brief get_infos return all information related to the decklink card
     * @return infos in structure
     */
    blackmagic_decklink_info get_infos() const;
};

/**
 * @brief The devices_error_window class
 */
class devices_error_window: public QWidget
{
private:
    QPushButton* m_boutonDialogue_error;

public:
    /**
     * @brief devices_error_window Default constructor
     */
    devices_error_window();
};

/**
 * @brief The MyTextBrowser class
 */
class MyTextBrowser : public QTextBrowser
{
protected:
    void mousePressEvent(QMouseEvent *mouseEvent);
};

}


