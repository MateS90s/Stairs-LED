#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <FastLED.h>
#include "config.h"

void lightFromDownstairsSwitch();
void lightFromUpstairsSwitch();
void lowEnerguyModeOn();
void lowEnerguyModeOff();
void turnOffLED();

extern CRGB leds[];
extern bool ledState;

#endif