/** @file mvas_panel_macros.h
 *  @brief Contains the defines and pin number of all the buttons, faders...
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

//Will be compiled only on the arduino
#if defined(__AVR_ATmega2560__)

  #include <Arduino.h>
  
  /** Pin for the Transition bar **/
  #define MVAS_TBAR_PIN A0

  /** Pin for the audio pan **/
  #define MVAS_POTA1_PIN A1
  #define MVAS_POTA2_PIN A2
  #define MVAS_POTA3_PIN A3
  #define MVAS_POTA4_PIN A4
  #define MVAS_POTA5_PIN A5
  #define MVAS_POTA6_PIN A6
  #define MVAS_POTA7_PIN A7
  #define MVAS_POTA8_PIN A8
  
#endif

/** Clock pin for the rotary **/
#define MVAS_ROTARY_CLOCK 20
/** Data pin for the rotary **/
#define MVAS_ROTARY_DATA 21
/** Click pin for the rotary **/
#define MVAS_ROTARY_CLICK 22

/**< Preview buttons pin **/
#define MVAS_PRW1_PIN 40
#define MVAS_PRW2_PIN 41
#define MVAS_PRW3_PIN 42
#define MVAS_PRW4_PIN 43

/**< Program buttons pin **/
#define MVAS_PRG1_PIN 44
#define MVAS_PRG2_PIN 45
#define MVAS_PRG3_PIN 46
#define MVAS_PRG4_PIN 47
