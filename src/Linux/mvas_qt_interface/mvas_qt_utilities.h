/** @file mvas_qt_utilities.h
 *  @brief Describe extra features related to Qt interface
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <QGroupBox>

#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

namespace mvas
{
    /**
     * @brief load_stylesheet load a css file and returns it into a standard c++
     * string
     * @param path Path to the css file
     *
     * @see also QWidget::setStyleSheet(const QString&)
     * @return text from file
     */
    std::string load_stylesheet(const char* path);

    /**
     * @brief get_src_path find the absolute source path for the src folder
     * @return Absolute path to the src folder
     */
    std::string get_src_path();

    /**
     * @brief wrap_with_groupbox wrap the widget in a group box and to set a
     * title for display
     * @param widget_to_wrap is a pointer to a QWidget you want to wrap
     * @param title string you want to display over the groupbox
     * @param parent parent's widget
     * @return Pointer to the groupbox where the widget is wrapped
     */
    QGroupBox* wrap_in_groupbox(QWidget* widget_to_wrap,
                                const QString& title,
                                QWidget* parent);
}
