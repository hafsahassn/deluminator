# Deluminator
The Deluminator, named after the magical device used by Albus Dumbledore to remove light sources, as well as restore them, is my moniker for the ESP Wroom32 which is able to control light bulbs using voice commands channeled through the Amazon Alexa app. A smart home system built using the natural voice experiences of the voice service, this project is an intuitive approach in interacting with the technology we use every day.

## Arduino IoT Cloud

### Introduction
The [ArduinoIoTCloud](https://docs.arduino.cc/cloud/iot-cloud/tutorials/iot-cloud-getting-started) library is the central element of the firmware enabling certain development boards to connect to the Arduino IoT Cloud. This platform allows anyone to create internet connected devices, and all in one solution for **configuration, writing code, uploading and visualization**.
With the Arduino IoT Cloud desktop or mobile platform, you can quickly connect, manage and monitor your devices from anywhere in the world.
Arduino IoT Cloud allows you to automatically create any code to program your device with - just add a couple of lines to customize it how you want.

### How to Connect
1. Create a new logical representation known as a Thing.
2. Register the Arduino IoT Cloud capable board via Arduino IoT Cloud (Devices Section).
3. Add variables for any of the data types available - int, float, boolean, long, char. Special variables include Temperature, Velocity, and Luminance.
4. Connect to a Wi-Fi network by configuring your network credentials in the Network section. 

### Building A Sketch
For the interface, we start with a special sketch file which can be found in the Sketch tab, which includes all of the configurations that we have made. When the sketch has been uploaded, it will work as a regular sketch, but it will also update the Cloud variables that we use.
Every time a variable is triggered from the Cloud, it will execute the code within the associated functions.
When the sketch has been customized, we can incorporate it to our source code, and upload to the development board.

### Creating A Dashboard
Dashboards are visual user interfaces for interacting with the connected boards over the Cloud. We can have many different setups depending upon what the project needs. 
1. Create widgets as visual representations of our variables.
2. Link each widget to the variables in your Thing. Once it is linked, we can either interact with it, for example a button, or we can monitor a value from a sensor.

## Arduino Alexa Amazon Skill
Through the Arduino Alexa Amazon Skill, we can securely connect Alexa to your Arduino IoT Cloud projects with no additional coding required.
A few of the features that are available are:

* **Changing the color and the luminosity of lights**
* **Retrieving temperature and detect motion activity from sensors**
* **Using voice commands to trigger switches and smart plugs**

The launch of the Arduino IoT Cloud and Alexa integration brings easy cross platform communication, customizable user interfaces and reduced complexity when it comes to programming. These features allow many different types of users to benefit from this service, where they can create anything from voice controlled light dimmers to plant waterers. Using Alexa is as simple as asking a question — just ask, and Alexa will respond instantly. 

Integrating Arduino with Alexa can be done in 4 simple steps:
1. Add the Arduino IoT Cloud Smart Home skill.
2. Link your Arduino Create account with Alexa.
3. Once linked, go to the device tab in the Alexa app and start searching for devices.
4. The properties created in the Arduino IoT Cloud will now appear as devices.

For a step-by-step tutorial: [Alexa - IoT Cloud Integration](https://create.arduino.cc/projecthub/303628/arduino-iot-cloud-amazon-alexa-integration-4e6078)

## Materials

* **DOIT ESP32 DevKit V1**
* **4-Channel SPDT 5V Relay Module**
* **DHT11 Sensor**
* **MB102 Breadboard Power Supply Module**
* **LEDs**

### Auxiliaries
* Amazon Alexa App
* 330 Ohm Resistors
* Push Buttons
* LEDs
* Jumper Wires
* Breadboard
* 12V 2.5A Power Adapter
* USB to USB Cable
* Micro USB Connector
* Multimeter

## Libraries Used
* **Arduino IoT Cloud**
* **DHT Sensor Library** by **Adafruit**
* **Adafruit Unified Sensor**
