/*
	Single HC-SR04
	
	Finds the distance between a single HC-SR04 and the closest obstruction
	in front of it.
	
	The circuit:
	* HC-SR04 trig pin to digital pin 2
	* HC-SR04 echo pin to digital pin 3
	
	Created July 2015
	By Dejan Nedelkovski
	Modified Summer 2017
	By Kaiz Akhtar
	
	http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
*/

// Pin numbers
const int trigPin = 2;
const int echoPin = 3;

// Math helper variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}
