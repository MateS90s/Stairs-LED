#include "ota_manager.h"
#include <ArduinoOTA.h>
#include <WiFi.h>

void setupOTA() {
  Serial.println("Creating AP...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP_OTA", "haslo1234");
  
  Serial.print("AP created! IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.softAPmacAddress());
  
  Serial.println("Starting OTA...");
  ArduinoOTA.setPort(3232);
  
  ArduinoOTA.onStart([]() {
    Serial.println("OTA Start");
    if (ArduinoOTA.getCommand() == U_FLASH) {
      Serial.println("Start updating sketch");
    } else {
      Serial.println("Start updating filesystem");
    }
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("OTA End");  
  });
  
  ArduinoOTA.setTimeout(60000);
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  
  ArduinoOTA.begin();
  Serial.println("OTA Ready - waiting for connections");
  Serial.println("========================");
}

void handleOTA() {
  ArduinoOTA.handle();
  
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 30000) {
    Serial.printf("AP Status - Connected clients: %d\n", WiFi.softAPgetStationNum());
    lastCheck = millis();
  }
}