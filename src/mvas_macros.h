/** @file mvas_macros.h
 *  @brief Contains all the defines used in the API
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

/** Number of program buttons on the panel **/
#define MVAS_PRG_BUT_COUNT 4

/** Number of preview buttons on the panel **/
#define MVAS_PRW_BUT_COUNT 4

/** Minimum index for the port on linux with the following form:
 * "ttyACM" + number **/
#define MVAS_MIN_PORT_INDEX 0

/** Maximum index for the port on linux with the following form:
 *  "ttyACM" + number **/
#define MVAS_MAX_PORT_INDEX 3

/** Number of audio input/aux on the panel **/
#define MVAS_AUDIO_SLICE_COUNT 2

/** Baudrate for the reading and writing on serial port **/
#define MVAS_BAUDSPEED 9600
