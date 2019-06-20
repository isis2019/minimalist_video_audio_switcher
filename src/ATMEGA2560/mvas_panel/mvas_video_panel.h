/** @file mvas_panel_panel.h
 *  @brief Contains features for controling the panel
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include <LiquidCrystal_I2C.h>
#include "mvas_video_panel.h"
#include "mvas_panel_macros.h"
#include "mvas_panel_utilities.h"
#include "/home/isis/Documents/minimalist_video_audio_switcher/src/mvas_macros.h"

namespace mvas
{
  class video_panel
  {
    LiquidCrystal_I2C* m_lcd;
    
  public:
    video_panel(LiquidCrystal_I2C* lcd);

    void init_pins() const;
    uint16_t tbar_value() const;
    bool write_tbar_to_serial() const;
    void write_buttons_to_serial() const;
    void write_potars_to_serial() const;
    void read_feedback() const;

    void print_value_to_lcd(const char type, const int num, const int val);

  };
}
