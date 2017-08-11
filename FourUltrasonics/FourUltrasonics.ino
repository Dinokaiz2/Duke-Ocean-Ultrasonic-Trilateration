/*
	Distances between Three Transmitter HC-SR04s and One Receiver HC-SR04
	
	Prints the distance between each transmitter HC-SR04 and the receiver HC-SR04
	to Serial.
	
	The circuit:
	* RX HC-SR04 trig pin to digital pin 2
	* RX HC-SR04 echo pin to digital pin 8
	* 1st TX HC-SR04 trig pin to digital pin 4
	* 2nd TX HC-SR04 trig pin to digital pin 5
	* 3rd TX HC-SR04 trig pin to digital pin 6
	
	Created Summer 2017
	By Kaiz Akhtar

*/

// Pin numbers
const int rxTrigPin = 2;
const int rxEchoPin = 8;
const int tx1TrigPin = 4;
const int tx2TrigPin = 5;
const int tx3TrigPin = 6;

// Math helper variables
long tx1Time;
long tx2Time;
long tx3Time;
long rx1Time1;
long rx1Time2;
long rx1Time3;

int distance1;
int distance2;
int distance3;
long duration1;
long duration2;
long duration3;

void setup() {
  pinMode(tx1TrigPin, OUTPUT);
  pinMode(tx2TrigPin, OUTPUT);
  pinMode(tx3TrigPin, OUTPUT);
  pinMode(rxTrigPin, OUTPUT); 
  pinMode(rxEchoPin, INPUT);
  Serial.begin(115200); // Starts the serial communication
}

void loop() {
  // Clears the trigPins
  digitalWrite(tx1TrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(tx1TrigPin, HIGH);
  digitalWrite(rxTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tx1TrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  // Reads the echoPin
  while(digitalRead(rxEchoPin) == LOW) ;
  tx1Time = micros();
  while(digitalRead(rxEchoPin) == HIGH && micros() - tx1Time < 11600) ;
  rx1Time1 = micros();
  duration1 = rx1Time1 - tx1Time;
  distance1 = duration1*0.034;

  // Clears the trigPins
  digitalWrite(tx2TrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(tx2TrigPin, HIGH);
  digitalWrite(rxTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tx2TrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  // Reads the echoPin
  while(digitalRead(rxEchoPin) == LOW) ;
  tx2Time = micros();
  while(digitalRead(rxEchoPin) == HIGH && micros() - tx2Time < 11600) ;
  rx1Time2 = micros();
  duration2 = rx1Time2 - tx2Time;
  distance2 = duration2*0.034;

  // Clears the trigPins
  digitalWrite(tx3TrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(tx3TrigPin, HIGH);
  digitalWrite(rxTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tx3TrigPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  // Reads the echoPin
  while(digitalRead(rxEchoPin) == LOW) ;
  tx3Time = micros();
  while(digitalRead(rxEchoPin) == HIGH && micros() - tx3Time < 11600) ;
  rx1Time3 = micros();
  duration3 = rx1Time3 - tx3Time;
  distance3 = duration3*0.034;

  // Write out the distances to serial
  Serial.print("Distances (1, 2, 3): ");
  Serial.print(distance1);
  Serial.print('\t');
  Serial.print(distance2);
  Serial.print('\t');
  Serial.println(distance3);
}
