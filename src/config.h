#ifndef CONFIG_H        // jeśli NIE zdefiniowano CONFIG_H
#define CONFIG_H        // to zdefiniuj CONFIG_H

#include <FastLED.h>

// LED parametry
#define LED_PIN     9
#define NUM_LEDS    340
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB

// Przyciski
#define BUTTON_0_PIN 8
#define BUTTON_1_PIN 7

// WiFi/OTA
#define WIFI_SSID "ESP_OTA"
#define WIFI_PASS "haslo1234"
#define OTA_PORT 3232

// Debug
#define DEBUG_ENABLED true

#endif                  // koniec warunku