#include <Arduino.h>
#include "SBUS.h"

SBUS RX(Serial2);

uint16_t RX_channels[12];
bool RX_failSafe;
bool RX_lostFrame;

uint16_t RX_channels_out[12];

void setup()
{
  Serial.begin(115200);
  RX.begin();
}

void loop()
{
  if (RX.read(&RX_channels[0], &RX_failSafe, &RX_lostFrame))
  {
    for (int i = 0; i < 12; i++)
    {
      RX_channels_out[i] = map(RX_channels[i], 170, 1815, 0, 1023);
      Joystick.X(RX_channels_out[0]);
      Joystick.Y(RX_channels_out[1]);
      Joystick.Z(RX_channels_out[2]);
      Joystick.Zrotate(RX_channels_out[3]);
      Joystick.sliderLeft(RX_channels_out[4]);
      Joystick.sliderRight(RX_channels_out[5]);
    }
  }
}