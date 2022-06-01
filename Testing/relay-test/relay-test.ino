/*
 4 Channel SPDT 5V Relay:
 By means of a relay, we cna control higher voltages (120 - 240V), and drive devices like fans, lights, heaters, and other household appliances.
 Since the ESP32 operates at 5V it can’t control these higher voltage devices directly, we can use a 5V relay to switch the 120-240V current 
 and use the ESP32 to control the relay.

 The ESP32 can be programmed to turn on the 4 channel relay module when a certain event occurs, for example when the temperature of 
 a thermistor gets higher than 30° C. Or when the resistance of a photoresistor drops below 400 Ohms.
 */

 /*
 How Does the Relay Work?
 The 4 channel  relay module has three high voltage terminals (NC, C, and NO) which connect to the device you want to control. 
 The other side has three low voltage pins (Ground, VCC, and Signal) which connect to the ESP32.

  NC: Normally closed 120-240V terminal
  NO: Normally open 120-240V terminal
  C: Common terminal
  Ground: Connects to the GND pin on the ESP32
  VCC: Connects the ESP’s 5V pin
  Signal: Carries the trigger signal from the ESP that activates the relay

  Inside the relay is a 120-240V switch that’s connected to an electromagnet. When the relay receives a HIGH signal at the signal pin, the electromagnet 
  becomes charged and moves the contacts of the switch open or closed.
 */

//integer number of relays
int relays = 4;  
//pin numbers that drive the signals to the relay stored in an array
relay[]={23,22,21,19}; 

int wait = 2000;
int count = 0;

void setup() {
  
  for(int count = 0; count < relays; count++){
    //set all the relay pins as OUTPUT
    pinMode(relay[count],OUTPUT); 
    digitalWrite(relay[count],HIGH); //turns the relay inputs off (the relay is active low enabled)
  }
}

void loop() {
  //this loop turns on all the relay outputs one by one after an interval of 2000 milliseconds
  for(int count = 0; count < relays; count++){
    //send a LOW signal to the relay input 'count'
    digitalWrite(relay[count],LOW);
    //wait for 2 seconds 
    delay(wait);
  }

  for(int count = 0; count < relays; count++){
    digitalWrite(relay[count],HIGH); //turn the relay outputs OFF
    delay(wait);
  }
}
