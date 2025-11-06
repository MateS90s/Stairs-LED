#include "animations.h"
#include <ArduinoOTA.h>



                   //##
              //##
         //##
    //##
//##
void lightFromDownstairsSwitch() {
  FastLED.setMaxRefreshRate(100);



  // Losuj pierwszy kolor (R, G lub B)
  int colorA_pick = random(0, 3);
  CRGB colorA;
  if (colorA_pick == 0) colorA = CRGB(255, 0, 0);      // czerwony
  else if (colorA_pick == 1) colorA = CRGB(0, 255, 0); // zielony
  else colorA = CRGB(0, 0, 255);                       // niebieski

  //  Losuj drugi kolor, inny niż pierwszy
  int colorB_pick;
  do {
    colorB_pick = random(0, 3);
  } while (colorB_pick == colorA_pick);

  CRGB colorB;
  if (colorB_pick == 0) colorB = CRGB(255, 0, 0);
  else if (colorB_pick == 1) colorB = CRGB(0, 255, 0);
  else colorB = CRGB(0, 0, 255);





 
  for (int i = 0; i < NUM_LEDS; i++) {
    // użyj wylosowanego colorA zamiast CRGB::Green
    leds[i] = colorA;




    for (int j = 1; j <= 20; j++) {
      int idx = i - j;
      if (idx >= 0 && idx < NUM_LEDS) {
        if (j <= 10) {
          // stopniowe przygaszanie koloru A
          int fade = (7 - j) * 20; // 10 → pełny kolor, 0 → ciemno
          int r = (colorA.r > 0) ? constrain(fade, 0, colorA.r) : 0;
          int g = (colorA.g > 0) ? constrain(fade, 0, colorA.g) : 0;
          int b = (colorA.b > 0) ? constrain(fade, 0, colorA.b) : 0;
          leds[idx] = CRGB(r, g, b);
        } else {
          // płynne rozpalanie w kierunku koloru B
          int fade = (j - 10) * 20; // tempo narastania
          int r = (colorB.r > 0) ? constrain(fade, 0, colorB.r) : 0;
          int g = (colorB.g > 0) ? constrain(fade, 0, colorB.g) : 0;
          int b = (colorB.b > 0) ? constrain(fade, 0, colorB.b) : 0;
          leds[idx] = CRGB(r, g, b);
        }
      }
    }

  // ogon za czołem fali – końcowy kolor B
  if (i > 21 && i - 20 < NUM_LEDS) {
    leds[i - 20] = colorB;
  }





    FastLED.show();

    for (int d = 0; d < 10; d++) {
      ArduinoOTA.handle();
      delay(1);
    }
  }
  
  FastLED.setMaxRefreshRate(1);
  ledState = HIGH;
}



//##
    //##
        //##
            //##
                //##
void lightFromUpstairsSwitch() {
  FastLED.setMaxRefreshRate(100);

  // Losuj pierwszy kolor (R, G lub B)
  int colorA_pick = random(0, 3);
  CRGB colorA;
  if (colorA_pick == 0) colorA = CRGB(255, 0, 0);      // czerwony
  else if (colorA_pick == 1) colorA = CRGB(0, 255, 0); // zielony
  else colorA = CRGB(0, 0, 255);                       // niebieski

  // Losuj drugi kolor, inny niż pierwszy
  int colorB_pick;
  do {
    colorB_pick = random(0, 3);
  } while (colorB_pick == colorA_pick);

  CRGB colorB;
  if (colorB_pick == 0) colorB = CRGB(255, 0, 0);
  else if (colorB_pick == 1) colorB = CRGB(0, 255, 0);
  else colorB = CRGB(0, 0, 255);

  // Animacja od góry do dołu
  for (int i = NUM_LEDS - 1; i >= -20; i--) {
    // Zapal bieżącą diodę na colorA
    if (i >= 0 && i < NUM_LEDS) {
      leds[i] = colorA;
    }

    // Ogon animacji
    for (int j = 1; j <= 20; j++) {
      int idx = i + j;
      if (idx >= 0 && idx < NUM_LEDS) {
        if (j <= 10) {
          // stopniowe przygaszanie koloru A
          int fade = (9 - j) * 20;
          int r = (colorA.r > 0) ? constrain(fade, 0, colorA.r) : 0;
          int g = (colorA.g > 0) ? constrain(fade, 0, colorA.g) : 0;
          int b = (colorA.b > 0) ? constrain(fade, 0, colorA.b) : 0;
          leds[idx] = CRGB(r, g, b);
        } else {
          // płynne rozpalanie w kierunku koloru B
          int fade = (j - 9) * 20;
          int r = (colorB.r > 0) ? constrain(fade, 0, colorB.r) : 0;
          int g = (colorB.g > 0) ? constrain(fade, 0, colorB.g) : 0;
          int b = (colorB.b > 0) ? constrain(fade, 0, colorB.b) : 0;
          leds[idx] = CRGB(r, g, b);
        }
      }
    }

    // Ogon za czołem fali – końcowy kolor B
    if (i + 20 >= 0 && i + 20 < NUM_LEDS) {
      leds[i + 20] = colorB;
    }

    FastLED.show();

    for (int d = 0; d < 10; d++) {
      ArduinoOTA.handle();
      delay(1);
    }
  }

  FastLED.setMaxRefreshRate(1);
  ledState = HIGH;
}



          //##
      //##    ##
  //##          ##
void lowEnergyModeOn() {
  Serial.println("=== SPECIAL FUNCTION - 3x CLICK ===");
  
  FastLED.setMaxRefreshRate(100);
  
  // Wyłącz wszystkie
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(300);
  
  // Faza 1: Płynne rozjaśnianie środka (120–200) przez 1 sekundę
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    for (int i = 120; i <= 200; i++) {
      leds[i] = CRGB(0, 0, brightness);  // rosnąca intensywność niebieskiego
    }
    FastLED.show();
    delay(1000 / (255 / 5));  // ~20 ms na krok → ~1 sekunda łącznie
  }
  
  // Faza 2: Rozszerzenie (80-120 i 200-240)
  for (int i = 80; i < 120; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 201; i <= 240; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  delay(100);
  
  // Faza 3: Dalsze rozszerzenie (40-80 i 240-280)
  for (int i = 40; i < 80; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 241; i <= 280; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  delay(100);
  
  // Faza 4: Wszystkie (0-40 i 280-340)
  for (int i = 0; i < 40; i++) {
    leds[i] = CRGB::Blue;
  }
  for (int i = 281; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  
  FastLED.setMaxRefreshRate(1);
  ledState = HIGH;
   delay(100);

  // Wszystkie zgaszone
  FastLED.clear();
  FastLED.show();
  
  FastLED.setMaxRefreshRate(1);
  ledState = LOW;
}

          

  //##          ##
     //##    ##
        //##
void lowEnergyModeOff() {
  Serial.println("=== SPECIAL FUNCTION OFF - WiFi disable ===");
  
  FastLED.setMaxRefreshRate(100);

  // Faza 0: Płynne rozjaśnianie wszystkich diod (1 sekunda)
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, brightness));
    FastLED.show();
    delay(1000 / (255 / 5));  // ok. 1 sekunda
  }

  // Faza 1: Gaśnie brzeg (0–40 i 280–NUM_LEDS)
  for (int i = 0; i < 40; i++) leds[i] = CRGB::Black;
  for (int i = 281; i < NUM_LEDS; i++) leds[i] = CRGB::Black;
  FastLED.show();
  delay(100);

  // Faza 2: Gaśnie (40–80 i 240–280)
  for (int i = 40; i < 80; i++) leds[i] = CRGB::Black;
  for (int i = 241; i <= 280; i++) leds[i] = CRGB::Black;
  FastLED.show();
  delay(100);
 
  // Faza 3: Gaśnie (80–120 i 200–240)
  for (int i = 80; i < 120; i++) leds[i] = CRGB::Black;
  for (int i = 201; i <= 240; i++) leds[i] = CRGB::Black;
  FastLED.show();
  delay(100);
  
  // Faza 4: Gaśnie środek (120–200)
  for (int i = 120; i <= 200; i++) leds[i] = CRGB::Black;
  FastLED.show();
  delay(100);

  
  // 💡 Wszystkie zgaszone — czyszczenie
  FastLED.clear();
  FastLED.show();

  FastLED.setMaxRefreshRate(1);
  ledState = LOW;
}







//

void turnOffLED() {
  FastLED.setMaxRefreshRate(100);
  FastLED.clear();
  FastLED.show();
  FastLED.setMaxRefreshRate(100);
  ledState = LOW;
}