/*
	Distance between Two HC-SR04s
	
	Prints the distance between the two connected HC-SR04s
	(one for receiving and one for transmitting) to Serial.
	
	The circuit:
	* RX HC-SR04 trig pin to digital pin 2
	* RX HC-SR04 echo pin to digital pin 3
	* TX HC-SR04 trig pin to digital pin 4

	Created Summer 2017
	By Kaiz Akhtar

*/

// Pin numbers
const int rxTrigPin = 2;
const int rxEchoPin = 3;
const int txTrigPin = 4;

// Math helper variables
long duration;
int distance;
long txTime;
long rxTime;


void setup() {
  pinMode(txTrigPin, OUTPUT);
  pinMode(rxTrigPin, OUTPUT); 
  pinMode(rxEchoPin, INPUT);
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // Clears the trigPins
  digitalWrite(txTrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(txTrigPin, HIGH);
  // We have to pulse the trig pin on the RX HC-SR04 because
  // it won't accept echoes until it's been triggered.
  digitalWrite(rxTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(txTrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  // pulseIn is the normal way to do this, but it won't work when the RX and TX ultrasonics/Arduinos are separate.
  // We break down pulseIn into steps that will translate more easily to two separate Arduinos.
  // duration = pulseIn(rxEchoPin, HIGH);
  
  while(digitalRead(rxEchoPin) == LOW) { };
  txTime = micros();
  while(digitalRead(rxEchoPin) == HIGH && micros() - txTime < 11600) { };
  rxTime = micros();
  duration = rxTime - txTime;
  
  // Calculating the distance
  distance = duration*0.034;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  delay(50);
  
}
