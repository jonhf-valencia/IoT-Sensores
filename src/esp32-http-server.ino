#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DHT.h>
#include "HtmlModule.h"

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

#define DHTPIN 15         // Pin de datos del DHT
#define DHTTYPE DHT22     // Cambia esto a DHT11 si estás usando un DHT11
#define GREEN_LED_PIN 27  // Pin del LED verde


DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

float temperature = 0.0;
float humidity = 0.0;
bool increaseTemperature = false;  // Bandera para activar el incremento

void sendHtml() {
  String response = getHtmlResponse();

  server.send(200, "text/html", response);
}

void increaseTemperatureHandler() {
  increaseTemperature = true;  // Activa el incremento de temperatura
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup(void) {
  Serial.begin(115200);
  dht.begin();
  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, LOW);  // Apaga el LED inicialmente

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", sendHtml);
  server.on("/increaseTemp", increaseTemperatureHandler);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  // Lee los datos del sensor si no está en modo de incremento
  if (!increaseTemperature) {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
  }

  // Verifica si el sensor funciona correctamente
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error leyendo el sensor DHT!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  
  // Controla el incremento de temperatura
  if (increaseTemperature) {
    temperature += 2.0;
    if (temperature >= 42.0) {
      increaseTemperature = false;  // Detiene el incremento al llegar a 42 grados
    }
    delay(2000); // Espera 2 segundos para cada incremento
  }

  // Enciende el LED verde si la temperatura es igual o superior a 38 grados
  if (temperature >= 38.0) {
    digitalWrite(GREEN_LED_PIN, HIGH);
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);
  }

  server.handleClient();
  delay(2000);  // Actualiza cada 2 segundos
}
