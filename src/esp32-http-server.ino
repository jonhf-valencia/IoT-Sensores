#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include "DHT.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

#define DHTPIN 15  // Pin al que conectaremos el DHT22
#define DHTTYPE DHT22
#define BUTTON_PIN 13

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

const int LED1 = 26;
const int LED2 = 27;
bool led1State = false;
bool led2State = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", sendHtml);
  server.on(UriBraces("/toggle/{}"), toggleLed);
  server.on("/activateSensor", activateSensor);

  server.begin();
  Serial.println("HTTP server started (http://localhost:8180)");
}

void loop() {
  server.handleClient();

  if (digitalRead(BUTTON_PIN) == LOW) {
    activateSensor();
  }
}

void sendHtml() {
  String response = R"(
    <!DOCTYPE html><html>
      <head><title>ESP32 Web Server Demo</title><meta name="viewport" content="width=device-width, initial-scale=1"></head>
      <body><h1>ESP32 Web Server</h1>
        <div>
          <h2>LED 1</h2><a href="/toggle/1" class="btn LED1_TEXT">LED1_TEXT</a>
          <h2>LED 2</h2><a href="/toggle/2" class="btn LED2_TEXT">LED2_TEXT</a>
        </div>
        <div><a href="/activateSensor" class="btn">Activate Sensor</a></div>
      </body>
    </html>
  )";
  response.replace("LED1_TEXT", led1State ? "ON" : "OFF");
  response.replace("LED2_TEXT", led2State ? "ON" : "OFF");
  server.send(200, "text/html", response);
}

void toggleLed() {
  String led = server.pathArg(0);
  switch (led.toInt()) {
    case 1: led1State = !led1State; digitalWrite(LED1, led1State); break;
    case 2: led2State = !led2State; digitalWrite(LED2, led2State); break;
  }
  sendHtml();
}

void activateSensor() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.printf("Sensor activado: Temp=%.2f C, Humedad=%.2f%%\n", temperature, humidity);
  sendHtml();
}
