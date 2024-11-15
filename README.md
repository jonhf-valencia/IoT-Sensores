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
- **Arduino IDE**
- **DHT Sensor Library** de Adafruit (para el sensor DHT22)

## Instalación

### 1. Configuración de Hardware
Conecta los componentes de acuerdo con el esquema del circuito:

- **DHT22**: Conéctalo al pin 2 de tu Arduino.
- **MQ-135**: Conéctalo al pin analógico A0 de tu Arduino.
- **Relé**: Conéctalo al pin 9 de tu Arduino para controlar el ventilador o humidificador.

### 2. Configuración del Software
#### Librerías necesarias:
- **DHT Sensor Library**: Instálala desde el Administrador de Bibliotecas de Arduino:
  1. Ve a *Sketch > Incluir Librería > Administrar Bibliotecas...*
  2. Busca "DHT Sensor Library" y haz clic en "Instalar".

#### Código:
Copia el código del proyecto en el IDE de Arduino. Se incluyen varios archivos:
- **main.cpp**: Archivo principal donde se gestionan los sensores y actuadores.
- **sensors.h y sensors.cpp**: Definen las funciones para la lectura de los sensores.
- **actuators.h y actuators.cpp**: Controlan el actuador (relé).
- **config.h**: Define los pines de conexión y parámetros de funcionamiento.

#### Subir el código:
1. Abre Arduino IDE.
2. Copia el código en los archivos correspondientes.
3. Selecciona la placa (Arduino Uno) y el puerto COM adecuado.
4. Haz clic en *Verificar* para compilar el código y en *Cargar* para subirlo al Arduino.

### 3. Simulación en Tinkercad (opcional)
Si deseas simular el circuito antes de implementarlo físicamente, puedes usar **Tinkercad**:
1. Crea una cuenta en [Tinkercad](https://www.tinkercad.com/).
2. Crea un nuevo circuito y agrega los componentes mencionados.
3. Conecta los sensores y el relé según el esquema.
4. Agrega el código al editor de Tinkercad y haz clic en *Iniciar simulación*.

## Estructura del Código

El código está dividido en varios archivos para mejorar la organización y mantenimiento:

- **main.cpp**: Archivo principal que gestiona la lectura de los sensores y el control del actuador.
- **sensors.h y sensors.cpp**: Funciones para configurar y leer los valores de los sensores.
- **actuators.h y actuators.cpp**: Funciones para controlar el relé basado en los datos de los sensores.
- **config.h**: Archivo de configuración que define los pines y parámetros de operación.

## Diagrama de Circuito

El diagrama esquemático muestra cómo conectar los sensores y el actuador al microcontrolador. Asegúrate de incluir la conexión de los sensores y el relé, así como las protecciones necesarias, como fusibles o diodos de protección.

## Funcionalidad

1. **Lectura de Sensores**: El dispositivo lee la temperatura, la humedad y la calidad del aire en intervalos de 2 segundos.
2. **Control de Actuador**: Si la temperatura supera los 30°C, la humedad es mayor del 70%, o la calidad del aire es baja (por debajo de un umbral definido), el relé se activa para encender el ventilador o humidificador.
3. **Comunicación Serial**: Los datos de los sensores se muestran en el monitor serial para su monitoreo.

## Futuras Mejoras

- **Integración con la Nube**: Enviar los datos a una plataforma en la nube para monitoreo remoto.
- **Interfaz Web**: Crear una interfaz web para visualizar los datos y controlar el actuador desde un navegador.
- **Optimización de Algoritmos**: Mejorar los umbrales y algoritmos de control basados en pruebas reales.

## Conclusión

Este proyecto proporciona una solución sencilla pero eficaz para mejorar las condiciones del ambiente interior mediante la monitorización de temperatura, humedad y calidad del aire. Puede extenderse fácilmente para integrar más sensores y actuadores, así como para conectarse a plataformas de IoT más complejas.

---

¡Disfruta trabajando en tu proyecto IoT y mantén un ambiente saludable y cómodo! 😊

