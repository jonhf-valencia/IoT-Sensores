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

### 1. Entorno de Desarrollo (VS Code con Platformio):
- Instalar Visual Studio Code: Si aún no tienes Visual Studio Code, descárgalo e instálalo desde la página oficial de Visual Studio Code.
- Instalar Platformio en VS Code:
  - Abre Visual Studio Code.
  - Ve a la sección de extensiones (Ctrl+Shift+X).
  - Busca "Platformio" y haz clic en "Instalar".
  - Platformio añadirá soporte para plataformas de microcontroladores como Arduino, incluyendo el ESP32.
  
### Instalar Librerías Necesarias:

- DHT Sensor Library de Adafruit:
    1. Abre tu proyecto en Visual Studio Code.
    2. Ve a la sección de Platformio en la barra lateral izquierda.
    3. Haz clic en Lib Manager.
    4. En la barra de búsqueda, escribe DHT sensor library y selecciona "adafruit/DHT sensor library @ ^1.4.3".
    5. Haz clic en Install para añadir la librería a tu proyecto.
       
- Adafruit Unified Sensor:
    1. En el Lib Manager, busca Adafruit Unified Sensor @ ^1.1.6.
    2. Selecciónalo y haz clic en Install.
  
### Configuración del Proyecto:

- Archivos de Configuración:
1. En tu archivo platformio.ini, asegúrate de que está configurado para trabajar con el ESP32. El archivo platformio.ini ya contiene configuraciones necesarias, pero asegúrate de revisar que las dependencias de librerías están correctamente instaladas.
       
````
[env:esp32]
platform = espressif32
framework = arduino
board = esp32dev
lib_deps = 
    adafruit/DHT sensor library @ ^1.4.3
    adafruit/Adafruit Unified Sensor @ ^1.1.6
````

### Simulación en Wokwi:

- Instalar Wokwi Simulator: Accede a Wokwi Simulator y regístrate si aún no lo has hecho.

## Ejecución del código 

Para ejecutar el código, primero es necesario compilarlo utilizando el comando build de Platformio. Una vez que el código haya sido compilado correctamente, accede al archivo diagram.json y ejecuta el proyecto haciendo clic en el botón verde de Play.
![image](https://github.com/user-attachments/assets/e4e393c6-0a7d-4e94-b672-67dc24758c3a)


## Control de Sensores

Para interactuar con los sensores del circuito, abre la siguiente página local en tu navegador:

```
http://localhost:8180/
```

En la terminal, podrás observar cómo responden los sensores al presionar los botones disponibles en la interfaz web.
![image](https://github.com/user-attachments/assets/c2135c47-35c1-42e6-8743-12d65e12003f)


