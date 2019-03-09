/** @file mvas_error.h
 *  @brief Contains all the defines and functions for error handling in the mvas
 *      API
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <cstdio>

/** Send when process is success **/
#define MVAS_ERR_SUCCESS 0
/** Send when a file cannot be open **/
#define MVAS_ERR_FILE_NOT_FOUND 1
/**Send when the arduino panel is not detected **/
#define MVAS_ERR_ARDUINO_PANEL_NOT_FOUND 2

namespace mvas
{
    /**
     * @brief print_error Print the error define in a caracter form on terminal,
     * this functions is used for debugging.
     * @param err Error number you want to print
     */
    void print_error(const int err);
}
