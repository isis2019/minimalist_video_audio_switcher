#include "mvas_video_panel.h"

namespace mvas
{
  video_panel::video_panel(LiquidCrystal_I2C* lcd) : m_lcd(lcd)
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

      m_lcd->begin();
      m_lcd->backlight();
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
    uint16_t val = exponential_smoothing(tbar_value(), 0.5f);
    
    static uint16_t prev_val = val;

    //If the previous value is not the same we can write to serial
    if(val != prev_val)
    {
      memcpy(buff+1, &val, 2);
      Serial.write(buff, 4);      
      prev_val = val;

      print_value_to_lcd('T', 0, val); 
      return true;
    }

    return false;
  }

  void video_panel::write_buttons_to_serial() const
  {
    for(size_t i=0; i<MVAS_PRW_BUT_COUNT+MVAS_PRG_BUT_COUNT; i++)
    {
      if(digitalRead(MVAS_PRW1_PIN+i) == 0)
      { 
        Serial.write(serial_packet('B',0,i-MVAS_PRW1_PIN),4);
        print_value_to_lcd('B', 0, MVAS_PRW1_PIN+i); 
      }
    }
  }

  void video_panel::write_potars_to_serial() const
  {    
    static uint16_t old_potar[MVAS_AUDIO_SLICE_COUNT] = {0};
    
    uint16_t tmps[MVAS_AUDIO_SLICE_COUNT] = {0};

    if(old_potar[0] != (tmps[0]=analogRead(A1)) )
    {
      Serial.write(serial_packet('P',tmps[0],0),4);
      old_potar[0] = tmps[0];
      print_value_to_lcd('P', 0, old_potar[0]);  
    }

    if(old_potar[1] != (tmps[1]=analogRead(A2)) )
    {
      Serial.write(serial_packet('P',tmps[1],1),4);
      old_potar[1] = tmps[1];
      print_value_to_lcd('P', 1, old_potar[1]);
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

  void video_panel::print_value_to_lcd(const char type, const int num, const int val)
  {
    m_lcd->setCursor(0,0);

    switch (type)
    {
    case 'B':
      m_lcd->print("Bouton ");
      m_lcd->setCursor(0,1);
      if (val > 43)
      {
        m_lcd->print("PRG ");
        m_lcd->print(val-43);
        m_lcd->print("               ");
        
      }
      else if(val < 44)
      {
        m_lcd->print("PRW ");
        m_lcd->print(val-39);
        m_lcd->print("               ");
      }
      break;

    case 'F':
      m_lcd->print("Fader    ");
      break;

    case 'P':
      m_lcd->print("Potar ");
      m_lcd->print(num+1);
      m_lcd->setCursor(0,1);

      if (val < 500)
      {
        m_lcd->print("left    ");
      }
      else if (val > 512-24 && val < 512+24)
      {
        m_lcd->print("center     ");
      }
      else if (val > 524)
      {
        m_lcd->print("right      ");
      }
      break;

    case 'T':
      m_lcd->print("T-Bar    ");
      m_lcd->setCursor(0,1);
      m_lcd->print((float)val * (100.0f/1024.0f));
      m_lcd->print("%");
      break;
    }
  }
}
