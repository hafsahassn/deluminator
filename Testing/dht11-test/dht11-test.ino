/* This tutorial shows how to use the DHT11 and DHT22 temperature and humidity sensors with the ESP32.

   DHT Sensor:
   The DHT11 and DHT22 sensors are used to measure temperature and relative humidity. For my project, I have used the DHT11.
   These sensors contain a chip that does analog to digital conversion and spit out a digital signal with the temperature and humidity.
   The DHT11 measures temperature in the range of 0 to 50ºC (accuracy +/-2ºC), and humidity in the range of 20 to 90% (accuracy +/-5%). 
   Operating voltage: 3 to 5V
 */

//include the Adafruit DHT library
#include <DHT.h>

#define DHTPIN 4     // digital pin connected to the DHT sensor - GPIO4

#define DHTTYPE DHT11

// Pin 1 of the sensor connected to +5V
// Pin 2 of the sensor connected to DHTPIN
// Pin 3 connected to GND

//initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // wait a few seconds between measurements.
  delay(2000);

  // reading temperature or humidity takes about 250 milliseconds
  // sensor readings may also be up to 2 seconds 'old'
  float h = dht.readHumidity();
  // read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
