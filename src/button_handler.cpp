#include "button_handler.h"
#include "config.h"
#include "animations.h"
#include <Arduino.h>

#define MULTI_CHANGE_TIMEOUT 300
#define CHANGE_COUNT_FOR_SPECIAL 6  // 3 kliknięcia = 6 zmian stanu (góra-dół-góra-dół-góra-dół)

unsigned long lastChangeTime0 = 0;
int changeCount0 = 0;

void setupButtons() {
  pinMode(BUTTON_0_PIN, INPUT_PULLUP);
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
}

void handleButtons() {
  bool button0State = digitalRead(BUTTON_0_PIN);
  bool button1State = digitalRead(BUTTON_1_PIN);
  unsigned long currentTime = millis();
  
  // ===== PRZYCISK 0 (DOLNY) - z detekcją wielokrotnych zmian =====
  if (button0State != lastButton0State) {
    if (currentTime - lastChangeTime0 < MULTI_CHANGE_TIMEOUT) {
      changeCount0++;
      Serial.printf("Button 0 change count: %d\n", changeCount0);
    } else {
      changeCount0 = 1;
      Serial.println("Button 0 change count: 1");
    }
    lastChangeTime0 = currentTime;
  }
  
  // Sprawdź czy timeout minął i wykonaj akcję
  if (changeCount0 > 0 && (currentTime - lastChangeTime0 > MULTI_CHANGE_TIMEOUT)) {
    if (changeCount0 >= CHANGE_COUNT_FOR_SPECIAL) {
      lowEnerguyModeOn();
    } else {
      // 1 lub 2 zmiany = normalna akcja (toggle)
      if (ledState == HIGH) {
        turnOffLED();
      } else {
        lightFromDownstairsSwitch();
      }
    }
    changeCount0 = 0;
  }
  
  // ===== PRZYCISK 1 (GÓRNY) - prosta obsługa =====
  if (button1State != lastButton1State) {
    if (ledState == HIGH) {
      turnOffLED();
    } else {
      lightFromUpstairsSwitch();
    }
  }
  
  lastButton0State = button0State;
  lastButton1State = button1State;
}