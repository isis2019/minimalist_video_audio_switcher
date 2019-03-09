/** @file mvas_panel_macros.h
 *  @brief Contains some useful functions for serial communication and smoothing values
 *  @author Baptiste DRAPEAUD
 *  @date 21 february 2019
 *  @version 0.1
 **/

#pragma once

namespace mvas
{
  /**
   * @brief exponential smoothing smooth value like a low-pass filter
   * more alpha is near to zero, the more it going to be smoothed.
   * @param alpha Smoothing coefficient
   * @warning If alpha is too low, it can create some serious latency
   * @return Smoothed value
   */
  template <typename T>
  inline T exponential_smoothing(const T value, const float alpha)
  {
    static T prev_value = value;
    T new_value = value*alpha + (1-alpha)*prev_value;
    prev_value = new_value;
    return new_value;
  }

  /**
   * @brief Generate a custom serial packet for serial communication 
   * with the interface.
   * @param type Type of the device: 'T' for Tbar, 'B' for button, 'P' for potentionmeter
   * @param value Current value of the device (This is not used for button)
   * @param number Number of the device, for example the prg2 button is the second button
   * so the number is 2 -1(because we start from 0)
   * @return Serial packet ready to be send
   */
  inline const char* serial_packet(const char type, const uint16_t value, const uint8_t number = 0)
  {
    char* buf = new char[4];

    switch(type)
    {
    case 'P':
      buf[0] = 'P';
      memcpy(buf+1, &value, 2);
      buf[3] = number;
      break;  
    }
    
    return buf;
  }
}
