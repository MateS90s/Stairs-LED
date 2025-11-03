#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

void setupButtons();
void handleButtons();

// Zmienne zewnętrzne (zdefiniowane w main.cpp)
extern bool ledState;
extern bool lastButton0State;
extern bool lastButton1State;

#endif