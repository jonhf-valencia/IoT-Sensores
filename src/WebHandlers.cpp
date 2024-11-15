// WebHandlers.cpp
#include "WebHandlers.h"
#include "HtmlModule.h"
#include <WebServer.h>
#include "Globals.h"  // Incluir el archivo con las variables globales

// Variable global para el servidor
extern WebServer server;

// Función para enviar la respuesta HTML
void sendHtml() {
  String response = getHtmlResponse(); // Suponemos que tienes una función que genera la respuesta HTML
  server.send(200, "text/html", response);
}

// Función para manejar la solicitud de incremento de temperatura
void increaseTemperatureHandler() {
  increaseTemperature = true;  // Activa el incremento de temperatura
  server.sendHeader("Location", "/");
  server.send(303);  // Redirige a la página principal
}

// Función para manejar la simulación de detección de gas
void triggerGasHandler() {
  simulateGasDetection = true;
  server.sendHeader("Location", "/");
  server.send(303);  // Redirige a la página principal
}
