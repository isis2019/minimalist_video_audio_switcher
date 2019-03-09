#include "mvas_video_panel.h"

mvas::video_panel vp;

void setup()
{
  vp.init_pins();
  Serial.begin(9600);
    pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
}

void loop()
{
  vp.write_potars_to_serial();
  delay(10);
}
