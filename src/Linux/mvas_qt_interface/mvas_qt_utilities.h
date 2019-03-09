/** @file mvas_qt_utilities.h
 *  @brief Describe extra features related to Qt interface
 *  @author Baptiste Drapeaud
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

namespace mvas
{
    /**
     * @brief load_stylesheet load a css file and returns it into a char array
     * @param path Path to the css file
     *
     * @see also QWidget::setStyleSheet(const QString&)
     * @return text from file
     */
    const char* load_stylesheet(const char* path);

    /**
     * @brief get_src_path find the absolute source path for the src folder
     * @return Absolute path to the src folder
     */
    std::string get_src_path();
}
