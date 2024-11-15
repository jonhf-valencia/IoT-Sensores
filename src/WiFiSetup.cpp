// WiFiSetup.cpp
#include "WiFiSetup.h"

// Función para configurar la conexión WiFi
void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);

  Serial.print("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println(" Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
