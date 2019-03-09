/** @file mvas_driver.h
 *  @brief Contains functions for manipulating the panel from interface
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <cstdio>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>

#include "mvas_macros.h"
#include "mvas_error.h"

/**
 * @namespace mvas
 * @brief This namespace contains all the mvas functions, members and other
 * features... The purpose of this namespace is for avoiding repeating names
 * over other libraries or conflict
 */
namespace mvas
{
    /**
     * @struct panel_values
     * @brief All the values read from the panel are stored here, the common use
     * of this structure is to write on it with a separate thread or tasks
     */
    struct panel_values
    {
        /**< Value from the video T-bar **/
        uint16_t tbar = 0;
        /**< Id of the program button pressed**/
        uint8_t prg_but_pressed = 0;
        /**< Values of the potentiometer on the panel **/
        uint16_t potars[MVAS_AUDIO_SLICE_COUNT] = {0};
    };

    /**
     * @class panel_driver
     * @brief Handle all the serial communication between the panel and the
     * interface.
     */
    class panel_driver
    {
    private:
        /**< File descriptor for IO manipulation on the panel **/
        int m_fd;
        /**< Flag telling if the port is open or not**/
        bool is_opened;

    public:
        /**< Structure used for transferring values to another interface or
         * object **/
        panel_values values;

    public:
        /**
         * @brief panel_driver Default Constructor
         */
        panel_driver();

    public:
        /**
         * @brief open_panel_port look for the serial port where the panel is
         * plugged, if it find it, it open it and return the path to the port,
         * else it return an empty string
         * @return A standard string where the path is contained, if it's empty
         * then the panel is not detected or plugged
         */
        std::string open_panel_port();

        /**
         * @brief close_panel_port close the panel serial port and set all the
         * members to their original value
         */
        void close_panel_port();

        /**
         * @brief write_to_panel_port write a caracter line to the panel. It is
         * used to send feedback message in the form of a custom serial packet
         * @param msg Message in char you want to write to the panel
         * @see const char* serial_packet(const char type, const uint16_t value, const uint8_t number = 0) for more details of the custom serial packet
         */
        void write_to_panel_port(const char* msg);

        /**
         * @brief read_from_panel read 4 byte long caracter array from the panel
         * and then returns it.
         * @return NULL if nothing is read or the panel is unplugged
         */
        const char* read_from_panel() const;

        /**
         * @brief listen_to_port read all the information from the port and
         * modify the struct value with it.
         * @warning This function will pause the main thread, please use with
         * a different thread or an asynchronous task
         */
        void listen_to_port();

    private:
        /**
         * @brief set_serial_settings set the proper setting for IO operation on
         * the serial port
         * @return False if the setting are not in the proper form
         */
        bool set_serial_settings();
    };
}
