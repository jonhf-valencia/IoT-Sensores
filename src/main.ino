#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DHT.h>
#include "HtmlModule.h"
#include "WiFiSetup.h"
#include "Globals.h"  // Incluir el archivo con las variables globales
#include "WebHandlers.h" // Incluir las funciones del servidor web
#include <HTTPClient.h> // Librería para enviar peticiones HTTP

// Definir las credenciales del WiFi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

// Credenciales de Ubidots
#define UBIDOTS_API_KEY Agrega tu propia API Key"
#define UBIDOTS_TOKEN "Agrega tu propio token"
#define UBIDOTS_URL "Agrega tu propia url"

// Etiqueta del dispositivo en Ubidots
#define DEVICE_LABEL "tracking_sensors_code"

// Configuración de los pines del DHT y LEDs
#define DHTPIN 15        // Pin del sensor DHT
#define DHTTYPE DHT22    // Tipo de sensor DHT
#define GREEN_LED_PIN 27 // Pin para el LED verde
#define MQ9_PIN A0       // Pin para el sensor de gas MQ9
#define BLUE_LED_PIN 26  // Pin para el LED azul

// Namespace para manejar los datos del sensor DHT (temperatura y humedad)
namespace SensorData {
  DHT dht(DHTPIN, DHTTYPE); // Crear objeto DHT
  float temperature = 0.0;
  float humidity = 0.0;

  // Función para leer los valores de los sensores DHT
  void readSensors() {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
  }

  // Verificar si los datos leídos son válidos
  bool isValid() {
    return !isnan(temperature) && !isnan(humidity);
  }
}

// Namespace para controlar los LEDs (verde y azul)
namespace LEDControl {
  // Configuración de pines de los LEDs
  void setup() {
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
  }

  // Función para encender o apagar el LED verde
  void setGreenLED(bool state) {
    digitalWrite(GREEN_LED_PIN, state ? HIGH : LOW);
  }

  // Función para encender o apagar el LED azul
  void setBlueLED(bool state) {
    digitalWrite(BLUE_LED_PIN, state ? HIGH : LOW);
  }
}

// Namespace para manejar la detección de gas con el sensor MQ9
namespace GasDetection {
  int gasLevel = 0;

  // Leer el nivel de gas desde el sensor MQ9
  void readGasLevel() {
    gasLevel = analogRead(MQ9_PIN);
  }

  // Verificar si el nivel de gas es alto
  bool isGasDetected() {
    return gasLevel > 500; // Ajusta el umbral según tus necesidades
  }
}

// Configurar conexión WiFi
void connectWiFi() {
  Serial.println("Conectando al WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Intentando conectar...");
  }
  Serial.println("Conectado al WiFi.");
}

// Namespace para la configuración de WiFi
namespace WiFiConfig {
  // Conectar al WiFi utilizando la configuración predefinida
  void connect() {
    setupWiFi();  // Función definida en WiFiSetup.h
  }
}

// Enviar datos a Ubidots
void sendToUbidots(float temperature, float humidity, int gasLevel) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = UBIDOTS_URL + String(DEVICE_LABEL) + "/";
    String payload = "{";
    payload += "\"temperature\": " + String(temperature) + ",";
    payload += "\"humidity\": " + String(humidity) + ",";
    payload += "\"gas_level\": " + String(gasLevel);
    payload += "}";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Auth-Token", UBIDOTS_TOKEN);

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.println("Datos enviados a Ubidots.");
      Serial.println("Código de respuesta: " + String(httpResponseCode));
    } else {
      Serial.println("Error enviando datos: " + http.errorToString(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("No hay conexión WiFi.");
  }
}

// Crear una instancia del servidor web en el puerto 80
WebServer server(80);

// Configuración inicial del dispositivo
void setup(void) {
  Serial.begin(115200);      // Iniciar comunicación serial
  SensorData::dht.begin();   // Iniciar el sensor DHT
  LEDControl::setup();       // Configurar los pines de los LEDs

  WiFiConfig::connect();     // Conectar al WiFi

  server.on("/", sendHtml);
  server.on("/increaseTemp", increaseTemperatureHandler);
  server.on("/triggerGas", triggerGasHandler);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  if (!increaseTemperature) {
    SensorData::readSensors();
  }

  if (!SensorData::isValid()) {
    Serial.println("Error leyendo el sensor DHT!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(SensorData::temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(SensorData::humidity);
    Serial.println(" %");
  }

  if (increaseTemperature) {
    SensorData::temperature += 2.0;
    if (SensorData::temperature >= 42.0) {
      increaseTemperature = false;
    }
    delay(2000);
  }

  LEDControl::setGreenLED(SensorData::temperature >= 38.0);
  server.handleClient();

  if (simulateGasDetection) {
    GasDetection::readGasLevel();
    Serial.print("Gas Level: ");
    Serial.println(GasDetection::gasLevel);
    LEDControl::setBlueLED(GasDetection::isGasDetected());
    delay(2000);
  } else {
    LEDControl::setBlueLED(false);
  }

  if (simulateGasDetection) {
    delay(5000);
    simulateGasDetection = false;
  }

  // Enviar datos a Ubidots cada 5 segundos
  sendToUbidots(SensorData::temperature, SensorData::humidity, GasDetection::gasLevel);

  delay(5000); // Actualizar cada 5 segundos
}
