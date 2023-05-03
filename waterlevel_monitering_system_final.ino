#define echoPin D8 // attach pin D2 NodeMCU to pin Echo of HC-SR04
#define trigPin D7 // attach pin D3 NodeMCU to pin Trig of HC-SR04
#define RELAY_PIN D1 // attach pin D5 NodeMCU to relay pin

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
float a, b, c;


char auth[] = "y3ZsndNm8nMTuA_xeYCx4TlxsYWhFxI-";//Enter your Auth token
char ssid[] = "ABC";//Enter your WIFI name
char pass[] = "123456789";//Enter your WIFI passwor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(RELAY_PIN, OUTPUT); // Sets the relay pin as an OUTPUT
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
 
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm     ");
  a = distance;
  b = (16 - a);
  Serial.print("Water filled in cm: ");
  Serial.print(b);
  c = (b / 16) * 100;
  Serial.print("     Water Level: ");
  Serial.print(c);
  Serial.println("%");
  
  Blynk.virtualWrite(V1, c); // send water level to Blynk app
  
  if ( b>=11) { // If water is present
    digitalWrite(RELAY_PIN, HIGH); // turn off the relay
    Blynk.virtualWrite(V2, HIGH); // send status of relay to Blynk app
    delay(1000);
  } 
  else  {
    digitalWrite(RELAY_PIN, LOW); // turn on the relay
    Blynk.virtualWrite(V2, LOW); // send status of relay to Blynk app
    delay(1000);
  }
  
  Blynk.run(); // run Blynk
}
