/*
 *  TITLE: ESP32 Configured with Arduino IoT Cloud & Alexa to Control 4 Relays with Real Time DHT11 Feedback
 *  Preferences--> Aditional boards Manager URLs : 
 
 *  Development Board Used : DOIT ESP32 DEVKIT V1
 *  Libraries Used:
 *  ArduinoIoTCloud Library (with all the dependencies)
 *  DHT Library from Adafruit
 *  Adafruit Unified Sensor Library
*/

//including all the necessary libraries
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <DHT.h>

const char thingID[]          = "65936024-6827-4009-a074-e0309dcda42e"; //THING ID; Thing - Deluminator
const char deviceLoginName[]  = "3826ca89-1d48-4b4c-b26b-5c09ab01bc31"; //DEVICE ID; Device - ESP32 DEV MODULE

const char SSID[] = "ZTE_2.4G_DYJk9Y";              //Wi-Fi SSID
const char password[] = "albatil@1#3";              //Wi-Fi Password
const char deviceKey[] = "YND1LUR4QAUWPN0JXFLQ";    //DEVICE Password; Secret Key

//RX2  pin connected to DHT sensor, GPIO16
#define DHTPIN 16 

//define the GPIO pins connected with relays and switches
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19

#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D12
#define SwitchPin3 14  //D14
#define SwitchPin4 27  //D27

#define wifiLED    2   //D2

#define DHTTYPE DHT11  // DHT 11

//initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

int toggleState_1 = 0; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 0; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 0; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 0; //Define integer to remember the toggle state for relay 4

float temperature1 = 0;
float humidity1   = 0;
int   reconnectFlag = 0;

//function prototypes
void onSwitch1Change();
void onSwitch2Change();
void onSwitch3Change();
void onSwitch4Change();

/*Arduino IoT Cloud variables
The following variables are automatically generated and updated when changes are made to the Deluminator*/
CloudSwitch switch1;
CloudSwitch switch2;
CloudSwitch switch3;
CloudSwitch switch4;
CloudTemperatureSensor temperature;
/*The first 4 variables are marked as READ/WRITE in the Cloud Thing and also have functions
  which are called when their values are changed from the dashboard.
  These functions are generated with the Thing and added at the end of this sketch.*/

void initProperties(){

  ArduinoCloud.setBoardId(deviceLoginName);
  ArduinoCloud.setSecretDeviceKey(deviceKey);
  ArduinoCloud.setThingId(thingID);
  ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);
  ArduinoCloud.addProperty(switch2, READWRITE, ON_CHANGE, onSwitch2Change);
  ArduinoCloud.addProperty(switch3, READWRITE, ON_CHANGE, onSwitch3Change);
  ArduinoCloud.addProperty(switch4, READWRITE, ON_CHANGE, onSwitch4Change);
  ArduinoCloud.addProperty(temperature, READ, 8 * SECONDS, NULL); //Update temperature value after every 8 seconds
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, password);

void readSensor(){

  // Reading temperature or humidity takes about 250 milliseconds
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again)
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else {
    humidity1 = h;
    temperature = t;
   // Serial.println(tempareture);
  }  
}

void relayOnOff(int relay) {

  switch (relay) {
    case 1:
      if (toggleState_1 == 0) {
        digitalWrite(RelayPin1, LOW); //turn on relay 1
        toggleState_1 = 1;
        Serial.println("Bulb 1 ON!");
      }
      else {
        digitalWrite(RelayPin1, HIGH); //turn off relay 1
        toggleState_1 = 0;
        Serial.println("Bulb 1 OFF!");
      }
      delay(100);
      break;
    
    case 2:
      if (toggleState_2 == 0) {
        digitalWrite(RelayPin2, LOW); //turn on relay 2
        toggleState_2 = 1;
        Serial.println("Bulb 2 ON!");
      }
      else {
        digitalWrite(RelayPin2, HIGH); //turn off relay 2
        toggleState_2 = 0;
        Serial.println("Bulb 2 OFF!");
      }
      delay(100);
      break;
    
    case 3:
      if (toggleState_3 == 0) {
        digitalWrite(RelayPin3, LOW); // turn on relay 3
        toggleState_3 = 1;
        Serial.println("Bulb 3 ON!");
      } else {
        digitalWrite(RelayPin3, HIGH); // turn off relay 3
        toggleState_3 = 0;
        Serial.println("Bulb 3 OFF!");
      }
      delay(100);
      break;
    
    case 4:
      if (toggleState_4 == 0) {
        digitalWrite(RelayPin4, LOW); // turn on relay 4
        toggleState_4 = 1;
        Serial.println("Bulb 4 ON!");
      }
      else {
        digitalWrite(RelayPin4, HIGH); // turn off relay 4
        toggleState_4 = 0;
        Serial.println("Bulb 4 OFF!");
      }
      delay(100);
      break;
    
    default : break;
  }
}

void manualControl() {
  //manual switch control
  if (digitalRead(SwitchPin1) == LOW) {
    delay(200);
    relayOnOff(1);
    switch1 = toggleState_1;
  }
  else if (digitalRead(SwitchPin2) == LOW) {
    delay(200);
    relayOnOff(2);
    switch2 = toggleState_2;
  }
  else if (digitalRead(SwitchPin3) == LOW) {
    delay(200);
    relayOnOff(3);
    switch3 = toggleState_3;
  }
  else if (digitalRead(SwitchPin4) == LOW) {
    delay(200);
    relayOnOff(4);
    switch4 = toggleState_4;
  }
}

void doThisOnConnect(){
  //success message upon connection to cloud
  Serial.println("Board successfully connected to Arduino IoT Cloud");
  digitalWrite(wifiLED, HIGH); //Turn off Wi-Fi LED
}

void doThisOnSync(){
  Serial.println("Thing Properties synchronised");
}

void doThisOnDisconnect(){
  Serial.println("Board disconnected from Arduino IoT Cloud");
  digitalWrite(wifiLED, LOW); //Turn off WiFi LED
}

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();
  dht.begin();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, doThisOnConnect);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::SYNC, doThisOnSync);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::DISCONNECT, doThisOnDisconnect);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  /*
   The pins on the Arduino can be configured as either inputs or outputs.
   The pinMode() function configures the specified pin to behave either as an input or an output.
   */

  //relay pins declared as outputs
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  //built-in led connected to pin GPIO2 set for output mode when Wi-Fi is enabled
  pinMode(wifiLED, OUTPUT);

  //the INPUT-PULLUP pin mode accesses one of the 45K Ohm pullup resistors built on the chip
  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  /*
   The digitalWrite() function is used to write a HIGH or a LOW value to a digital pin. 
   If the pin has been configured as an OUTPUT with pinMode(), its voltage will be set to the 
   corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.
   */
  //During startup, all relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);
}

void loop() {

  //this call sends data to the cloud and receives updates
  ArduinoCloud.update();
  
  manualControl();     //manual switch control
  readSensor();        //read sensor data
}

/*
  Since each switch is READ/WRITE variable, onSwitch[x]Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onSwitch1Change() {
  //control the device
  if (switch1 == 1)
  {
    digitalWrite(RelayPin1, LOW);
    Serial.println("Device1 ON");
    toggleState_1 = 1;
  }
  else
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");
    toggleState_1 = 0;
  }
}

void onSwitch2Change() {
  if (switch2 == 1)
  {
    digitalWrite(RelayPin2, LOW);
    Serial.println("Device2 ON");
    toggleState_2 = 1;
  }
  else
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("Device2 OFF");
    toggleState_2 = 0;
  }
}

void onSwitch3Change() {
  if (switch3 == 1)
  {
    digitalWrite(RelayPin3, LOW);
    Serial.println("Device3 ON");
    toggleState_3 = 1;
  }
  else
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("Device3 OFF");
    toggleState_3 = 0;
  }
}

void onSwitch4Change() {
  if (switch4 == 1)
  {
    digitalWrite(RelayPin4, LOW);
    Serial.println("Device4 ON");
    toggleState_4 = 1;
  }
  else
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("Device4 OFF");
    toggleState_4 = 0;
  }
}
