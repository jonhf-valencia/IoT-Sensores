#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DHT.h>
#include "HtmlModule.h"
#include "WiFiSetup.h"
#include "Globals.h"  // Incluir el archivo con las variables globales
#include "WebHandlers.h" // Incluir las funciones del servidor web

// Definir las credenciales del WiFi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

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
    digitalWrite(GREEN_LED_PIN, LOW); // Apagar el LED verde al inicio
    digitalWrite(BLUE_LED_PIN, LOW);  // Apagar el LED azul al inicio
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

// Namespace para la configuración de WiFi
namespace WiFiConfig {
  // Conectar al WiFi utilizando la configuración predefinida
  void connect() {
    setupWiFi();  // Función definida en WiFiSetup.h
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

  // Definir las rutas del servidor
  server.on("/", sendHtml);               // Ruta principal para enviar HTML
  server.on("/increaseTemp", increaseTemperatureHandler);  // Handler para aumentar la temperatura
  server.on("/triggerGas", triggerGasHandler);  // Handler para simular detección de gas
  server.begin();  // Iniciar el servidor web
  Serial.println("HTTP server started");
}

// Bucle principal del programa
void loop(void) {
  // Leer los datos del sensor solo si no estamos en modo de incremento de temperatura
  if (!increaseTemperature) {
    SensorData::readSensors();
  }

  // Verificar si los datos del sensor son válidos
  if (!SensorData::isValid()) {
    Serial.println("Error leyendo el sensor DHT!");
  } else {
    // Mostrar los datos de temperatura y humedad en el monitor serial
    Serial.print("Temperature: ");
    Serial.print(SensorData::temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(SensorData::humidity);
    Serial.println(" %");
  }

  // Modo de incremento de temperatura (si está habilitado)
  if (increaseTemperature) {
    SensorData::temperature += 2.0; // Aumentar la temperatura en 2 grados
    if (SensorData::temperature >= 42.0) {
      increaseTemperature = false; // Detener el incremento al alcanzar los 42 grados
    }
    delay(2000); // Espera de 2 segundos entre incrementos
  }

  // Enciende el LED verde si la temperatura es mayor o igual a 38 grados
  LEDControl::setGreenLED(SensorData::temperature >= 38.0);

  server.handleClient();  // Manejar las solicitudes del servidor web

  // Simulación de detección de gas (si está activada)
  if (simulateGasDetection) {
    GasDetection::readGasLevel();  // Leer el nivel de gas
    Serial.print("Gas Level: ");
    Serial.println(GasDetection::gasLevel);

    // Controlar el LED azul según si se detecta gas
    LEDControl::setBlueLED(GasDetection::isGasDetected());

    delay(2000); // Ajusta el tiempo de muestreo de gas
  } else {
    LEDControl::setBlueLED(false);  // Apagar el LED azul si no se simula la detección de gas
  }

  // Restablecer la simulación de gas después de 5 segundos
  if (simulateGasDetection) {
    delay(5000);  // Espera 5 segundos antes de desactivar la simulación
    simulateGasDetection = false;
  }

  delay(2000); // Actualizar cada 2 segundos
}
