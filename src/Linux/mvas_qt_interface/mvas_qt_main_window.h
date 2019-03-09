/** @file mvas_qt_main_window.h
 *  @brief Main file for all the user and driver interactions
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/

#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QPalette>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <QToolButton>
#include <iostream>

#include "mvas_qt_video_interface.h"
#include "mvas_qt_audio_interface.h"
#include "mvas_qt_utilities.h"
#include "../../mvas_panel_driver.h"
#include "../../mvas_error.h"
#include "../../mvas_panel/mvas_panel_macros.h"

namespace mvas
{
    /**
     * @class main_window
     * @brief The main_window class describe the graphical interface and handle
     * all the interaction from the user
     */
    class main_window : public QMainWindow
    {
        Q_OBJECT

    private:
        /**< Audio interface for the mixer handling **/
        audio_interface* m_audio_gui;
        /**< Video interface for the switcher handling **/
        video_interface* m_video_gui;
        /**< Object for manipulating panel IO **/
        panel_driver m_driver;
        /**< Button to exit the application **/
        QToolButton* m_exit;

    public:
        /**
         * @brief main_window Default constructor
         */
        main_window();

    private:
        /**
         * @brief listen_arduino_panel Start an asynchronous task for getting
         * all the input from the panel. It also start a different thread for
         * update the graphic interface
         * @return error code
         */
        int listen_arduino_panel();

        /**
         * @brief init_widgets Initialize the widgets and their sizes
         */
        void init_widgets();

        /**
         * @brief set_graphics apply all graphics style for the different widget
         * and the main_window
         * @return error code
         */
        int set_graphics();

        /**
         * @brief set_widgets_layout organize the positions of the widgets in
         * the main_window
         */
        void set_widgets_layout();

        /**
         * @brief connect_widgets connect the feature for all related widgets
         */
        void connect_widgets();

    public slots:
        /**
         * @brief refresh Update the window's widgets every 10ms
         */
        void refresh();

        /**
         * @brief shutdown Exit the app in a proper way and close the serial
         *  port
         */
        void shutdown();
    };
}
