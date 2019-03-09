#include "mvas_video_panel.h"

namespace mvas
{
  video_panel::video_panel()
  {
  }

  void video_panel::init_pins() const
  {
    pinMode(MVAS_TBAR_PIN, INPUT);
    pinMode(MVAS_POTA1_PIN,INPUT);
    pinMode(MVAS_POTA2_PIN,INPUT);
    
    pinMode(LED_BUILTIN, OUTPUT);

    for(size_t i=0; i<MVAS_PRW_BUT_COUNT; i++)
      pinMode(MVAS_PRW1_PIN+i, INPUT_PULLUP);
      
    for(size_t i=0; i<MVAS_PRG_BUT_COUNT; i++)
      pinMode(MVAS_PRG1_PIN+i, INPUT_PULLUP);
  }

  uint16_t video_panel::tbar_value() const
  {
    return analogRead(MVAS_TBAR_PIN);
  }

  bool video_panel::write_tbar_to_serial() const
  {
    char buff[4];

    //Tbar prefix
    buff[0] = 'T';
    buff[3] = 0;

    //Smoothing values
    uint16_t val = exponential_smoothing(tbar_value(), 0.1f);
    
    static uint16_t prev_val = val;

    //If the previous value is not the same we can write to serial
    if(val != prev_val)
    {
      memcpy(buff+1, &val, 2);
      Serial.write(buff, 4);      
      prev_val = val;
      return true;
    }

    return false;
  }

  void video_panel::write_buttons_to_serial() const
  {
    for(size_t i=0; i<MVAS_PRW_BUT_COUNT+MVAS_PRG_BUT_COUNT; i++)
    {
      if(!digitalRead(MVAS_PRW1_PIN+i))
      {
        Serial.write(serial_packet('B',0,i-MVAS_PRW1_PIN),4);
      }
    }
  }

  void video_panel::write_potars_to_serial() const
  {
    static uint16_t old_potar[MVAS_AUDIO_SLICE_COUNT] = {0};
    
    uint16_t tmp = 0;
    
    if(old_potar[0] != (tmp=exponential_smoothing(analogRead(A1), 0.1f)) )
    {
      Serial.write(serial_packet('P',tmp,0),4);
      old_potar[0] = tmp;
    }

    if(old_potar[1] != (tmp=exponential_smoothing(analogRead(A2), 0.1f)) )
    {
      Serial.write(serial_packet('P',tmp,1),4);
      old_potar[1] = tmp;
    }
  }

  void video_panel::read_feedback() const
  {
    char buf[4] = {0};
    if(Serial.available())
    {
      size_t ind = 0;
      char tmp = 0;
      
      while((tmp=Serial.read()) != -1 && ind < 4)
      {
        buf[ind] = tmp;
        ind ++;
      }
    }
  }
}
