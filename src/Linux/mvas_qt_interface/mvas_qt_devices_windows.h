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
        const blackmagic_decklink_driver* m_driver;

    public:
        /**
         * @brief devices_infos_window Default constructor
         * @param driver Black magic driver
         * @param parent Widget's parent
         */
        devices_infos_window(const blackmagic_decklink_driver* driver, QWidget* parent);

    public:
        /**
         * @brief init_widgets initialize qt widgets
         */
        void init_widgets();
    };
}


