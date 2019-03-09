/** @file mvas_panel_panel.h
 *  @brief Contains features for controling the panel
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/
#pragma once

#include "mvas_video_panel.h"
#include "mvas_panel_macros.h"
#include "mvas_panel_utilities.h"
#include "/home/bdrapea/Documents/02_ISIS/M2/PROJET/V2/mvas/mvas_macros.h"

namespace mvas
{
  class video_panel
  {    
  public:
    video_panel();

    void init_pins() const;
    uint16_t tbar_value() const;
    bool write_tbar_to_serial() const;
    void write_buttons_to_serial() const;
    void write_potars_to_serial() const;
    void read_feedback() const;
  };
}
