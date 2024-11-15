#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DHT.h>
#include "HtmlModule.h"
#include "WiFiSetup.h"
#include "Globals.h"  // Incluir el archivo con las variables globales
#include "WebHandlers.h" // Incluir las funciones del servidor

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define WIFI_CHANNEL 6

#define DHTPIN 15        // Pin de datos del DHT
#define DHTTYPE DHT22    // Cambia esto a DHT11 si estás usando un DHT11
#define GREEN_LED_PIN 27 // Pin del LED verde
#define MQ9_PIN A0
#define BLUE_LED_PIN 26

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

float temperature = 0.0;
float humidity = 0.0;

void setup(void)
{
  Serial.begin(115200);
  dht.begin();
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(MQ9_PIN, INPUT);
  digitalWrite(GREEN_LED_PIN, LOW); // Apaga el LED Verde inicialmente
  digitalWrite(BLUE_LED_PIN, LOW);  // Apaga el LED Azul inicialmente

  // Conectar al WiFi usando la función modularizada
  setupWiFi();

  // Definir las rutas del servidor
  server.on("/", sendHtml);               // Llamada a la función sendHtml en WebHandlers.cpp
  server.on("/increaseTemp", increaseTemperatureHandler);  // Llamada al handler de incremento de temperatura
  server.on("/triggerGas", triggerGasHandler);  // Llamada al handler de simulación de gas
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  // Lee los datos del sensor si no está en modo de incremento
  if (!increaseTemperature)
  {
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
  }

  // Verifica si el sensor funciona correctamente
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("Error leyendo el sensor DHT!");
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Controla el incremento de temperatura
  if (increaseTemperature)
  {
    temperature += 2.0;
    if (temperature >= 42.0)
    {
      increaseTemperature = false; // Detiene el incremento al llegar a 42 grados
    }
    delay(2000); // Espera 2 segundos para cada incremento
  }

  // Enciende el LED verde si la temperatura es igual o superior a 38 grados
  if (temperature >= 38.0)
  {
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(GREEN_LED_PIN, LOW);
  }

  server.handleClient();  // Maneja las solicitudes del servidor web

  // Simulación de detección de gas (si se activa)
  if (simulateGasDetection)
  {
    int gasLevel = analogRead(MQ9_PIN);
    Serial.print("Gas Level: ");
    Serial.println(gasLevel);

    if (gasLevel > 500)
    {
      digitalWrite(BLUE_LED_PIN, HIGH);  // Enciende el LED azul si se detecta gas
    }
    else
    {
      digitalWrite(BLUE_LED_PIN, LOW);   // Apaga el LED azul si no se detecta gas
    }

    delay(2000); // Ajusta el tiempo de muestreo de gas según sea necesario
  }
  else
  {
    digitalWrite(BLUE_LED_PIN, LOW);  // Apaga el LED azul si no se simula la detección de gas
  }

  // Restablece la simulación después de 5 segundos
  if (simulateGasDetection)
  {
    delay(5000);
    simulateGasDetection = false;
  }
  delay(2000); // Actualiza cada 2 segundos
}
