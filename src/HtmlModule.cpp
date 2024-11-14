#include "HtmlModule.h"
#include <WebServer.h>

String getHtmlResponse()
{
  String response = R"(
<!DOCTYPE html>
<html lang="es">
  <head>
    <meta charset="UTF-8">
    <title>ESP32 Web Server Demo</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    
    <!-- Agregar la CDN de Tailwind CSS -->
    <script src="https://cdn.tailwindcss.com"></script>

    <!-- Agregar la CDN de Flowbite -->
    <link href="https://cdn.jsdelivr.net/npm/flowbite@1.5.2/dist/flowbite.min.css" rel="stylesheet">

  </head>
  
  <body class="bg-gray-100 font-sans antialiased text-gray-900">

    <!-- Contenedor principal -->
    <div class="max-w-4xl mx-auto px-4 py-8">

      <!-- Título principal -->
      <h1 class="text-4xl font-semibold text-center text-blue-600 mb-4">Internet de las cosas - IoT</h1>

      <!-- Línea divisoria -->
      <hr class="my-6">

      <!-- Información de autor -->
      <h2 class="text-xl text-center text-gray-700 mb-6">Elaborado por: <span class="font-bold text-blue-500">John Fredy Valencia Valencia</span></h2>

      <!-- Botón para aumentar la temperatura -->
      <div class="text-center">
        <a href="/increaseTemp">
          <button class="btn btn-primary py-3 px-6 rounded-md text-white font-semibold bg-green-600 hover:bg-green-700 transition duration-200 ease-in-out">
            Aumentar Temperatura
          </button>
        </a>
      </div>

    </div>

    <!-- Scripts de Flowbite -->
    <script src="https://cdn.jsdelivr.net/npm/flowbite@1.5.2/dist/flowbite.min.js"></script>
    
  </body>
</html>

  )";

  return response;
}
