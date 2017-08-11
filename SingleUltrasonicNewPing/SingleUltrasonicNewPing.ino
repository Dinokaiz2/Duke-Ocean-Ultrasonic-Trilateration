/*
	Single HC-SR04 using NewPing
	
	Finds the distance between a single HC-SR04 and the closest obstruction
	in front of it using the NewPing library.
	
	The NewPing library advertises "more accurate distance calculation" and
	increased speed over the native Arduino pulseIn method. However, it does
	not seem to easily support using an HC-SR04 as only a receiver or trasmitter.
	Hence, I don't provide further sketches using the NewPing library for 
	multiple HC-SR04s.
	
	The circuit:
	* HC-SR04 trig pin to digital pin 2
	* HC-SR04 echo pin to digital pin 3
	
	Created May 2012
	By Tim Eckel
	Modified Summer 2017
	By Kaiz Akhtar
	
	http://playground.arduino.cc/Code/NewPing#Example
*/

#include <NewPing.h> // http://playground.arduino.cc/Code/NewPing

// Pin numbers
const int trigPin = 2;
const int echoPin = 3;
const int MAX_DISTANCE = 200;

// NewPing setup of pins and maximum distance
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void setup() {
  Serial.begin(115200); // Starts the serial communication
}

void loop() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS)
  Serial.print("Distance: ");
  // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.print(sonar.convert_cm(uS));
  delay(50);
}
