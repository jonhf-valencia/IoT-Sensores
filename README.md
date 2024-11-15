# Proyecto de Monitorización del Ambiente Interior

## Descripción del Proyecto

Este proyecto consiste en un dispositivo IoT diseñado para monitorizar las condiciones ambientales de interiores, como la temperatura, la humedad y la calidad del aire. Utilizando sensores como el DHT22 para temperatura y humedad, y el MQ-135 para la calidad del aire, el dispositivo recopila datos en tiempo real. Además, tiene la capacidad de activar un actuador (como un ventilador o un humidificador) cuando los valores de temperatura, humedad o calidad del aire superan los límites establecidos.

## Objetivo

El objetivo de este proyecto es ofrecer una solución que permita mejorar la calidad del aire y las condiciones de confort en espacios cerrados (hogares, oficinas, escuelas, etc.). Esto se logra mediante la monitorización continua de estos parámetros y la activación de dispositivos cuando se detectan condiciones desfavorables.

## Componentes

- **Sensor de Temperatura y Humedad**: DHT22
  - Detecta la temperatura y la humedad relativa del ambiente.
- **Sensor de Calidad del Aire**: MQ-135
  - Mide la concentración de contaminantes en el aire, como CO2, amoníaco, humo, etc.
- **Actuador**: Relé
  - Controla dispositivos como ventiladores o humidificadores para mejorar las condiciones del ambiente.
- **Microcontrolador**: Arduino o compatible
  - Controla los sensores y actuadores, procesa los datos y comunica los resultados.

## Requisitos

### Hardware:
- **Arduino Uno** (u otro microcontrolador compatible)
- **Sensor DHT22** para medir temperatura y humedad
- **Sensor MQ-135** para medir la calidad del aire
- **Relé** para controlar el ventilador/humidificador
- **Cables y protoboard**

### Software:
- **VS code**
- **Platformio**
- **Wokwi Simulator**
  
## Instalación
