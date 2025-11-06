#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "config.h"
#include "animations.h"
#include "ota_manager.h"
#include "button_handler.h"

CRGB leds[NUM_LEDS];  // <-- to zostaje tutaj

bool ledState = LOW;
bool lastButton0State = HIGH;
bool lastButton1State = HIGH;
bool lowEnergyMode = false;

void setup() {

  Serial.begin(115200);
  delay(2000);
  Serial.println("=== ESP32 Starting ===");
  
  setupOTA();  // <-- zastępuje cały blok OTA

 // ### LED i przyciski ###
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  //(Organiczanie grzania esp) Startuj z normalnym odświeżaniem - zostanie zmienione po pierwszej animacji
  FastLED.setMaxRefreshRate(100);

setupButtons();
}


void loop() {
  handleOTA();
  handleButtons();
  delay(100); // Proste zabezpieczenie przed drganiami styków (debouncing)
}

