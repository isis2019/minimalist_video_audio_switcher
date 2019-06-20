#include "mvas_video_panel.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
mvas::video_panel vp(&lcd);

void setup()
{
  vp.init_pins();
  Serial.begin(9600);
}

void loop()
{
  vp.write_potars_to_serial();
  vp.write_tbar_to_serial();
  vp.write_buttons_to_serial();
  delay(10);
}
