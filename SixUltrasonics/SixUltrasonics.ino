/*
	Distances between Three Transmitter HC-SR04s and Three Receivers HC-SR04
	
	Prints the distance between each transmitter HC-SR04 and each receiver HC-SR04
	to Serial. Does NOT do trilateration, only finds all the distances necessary to
	do the math for it.
	
	The circuit:
	* 1st TX HC-SR04 trig pin to digital pin 4
	* 2nd TX HC-SR04 trig pin to digital pin 5
	* 3rd TX HC-SR04 trig pin to digital pin 6
	* 1st RX HC-SR04 echo pin to digital pin 8
	* 2nd RX HC-SR04 echo pin to digital pin 9
	* 3rd RX HC-SR04 echo pin to digital pin 10
	* ALL RX HC-SR04 trig pins to digital pin 2
	
	Created Summer 2017
	By Kaiz Akhtar
*/

// Pin numbers
const int rxTrigPin = 2;
const int tx1TrigPin = 4;
const int tx2TrigPin = 5;
const int tx3TrigPin = 6;
const int rx1EchoPin = 8;
const int rx2EchoPin = 9;
const int rx3EchoPin = 10;

// Math helper variables
long tx1Time;
long tx2Time;
long tx3Time;

long rx1Time1, rx1Time2, rx1Time3;
long rx2Time1, rx2Time2, rx2Time3;
long rx3Time1, rx3Time2, rx3Time3;

long tx1ToRx1Time, tx1ToRx2Time, tx1ToRx3Time;
long tx2ToRx1Time, tx2ToRx2Time, tx2ToRx3Time;
long tx3ToRx1Time, tx3ToRx2Time, tx3ToRx3Time;

int tx1ToRx1Dist, tx1ToRx2Dist, tx1ToRx3Dist;
int tx2ToRx1Dist, tx2ToRx2Dist, tx2ToRx3Dist;
int tx3ToRx1Dist, tx3ToRx2Dist, tx3ToRx3Dist;

void setup() {
  pinMode(rxTrigPin, OUTPUT); 
  
  pinMode(tx1TrigPin, OUTPUT);
  pinMode(tx2TrigPin, OUTPUT);
  pinMode(tx3TrigPin, OUTPUT);
  
  pinMode(rx1EchoPin, INPUT);
  pinMode(rx2EchoPin, INPUT);
  pinMode(rx3EchoPin, INPUT);
  
  Serial.begin(115200); // Starts the serial communication
}

void loop() {

  // Get time and distance from each TX HC-SR04 to each RX HC-SR04 and write them to our global time and distance variables
  sonarPing(tx1TrigPin, tx1ToRx1Time, tx1ToRx2Time, tx1ToRx3Time, tx1ToRx1Dist, tx1ToRx2Dist, tx1ToRx3Dist);
  sonarPing(tx2TrigPin, tx2ToRx1Time, tx2ToRx2Time, tx2ToRx3Time, tx2ToRx1Dist, tx2ToRx2Dist, tx2ToRx3Dist);
  sonarPing(tx3TrigPin, tx3ToRx1Time, tx3ToRx2Time, tx3ToRx3Time, tx3ToRx1Dist, tx3ToRx2Dist, tx3ToRx3Dist);

  // Write all the data to serial
  Serial.print("TX1 to RX1, RX2, RX3: ");
  if(tx1ToRx1Dist == 394) {
    Serial.print("-   ");
  } else {
    Serial.print(tx1ToRx1Dist);
  }
  Serial.print('\t');
  if(tx1ToRx2Dist == 394) {
    Serial.print("-   ");
  } else {
    Serial.print(tx1ToRx2Dist);
  }
  Serial.print('\t');
  if(tx1ToRx3Dist == 394) {
    Serial.println("-   ");
  } else {
    Serial.println(tx1ToRx3Dist);
  }
  Serial.print("TX2 to RX1, RX2, RX3: ");
  if(tx2ToRx1Dist == 394) {
    Serial.print("-   ");
  } else {
    Serial.print(tx2ToRx1Dist);
  }
  Serial.print('\t');
  if(tx2ToRx2Dist == 394) {
    Serial.print("-   ");
  } else {
    Serial.print(tx2ToRx2Dist);
  }
  Serial.print('\t');
  if(tx2ToRx3Dist == 394) {
    Serial.println("-   ");
  } else {
    Serial.println(tx2ToRx3Dist);
  }
  Serial.print("TX3 to RX1, RX2, RX3: ");
  if(tx3ToRx1Dist == 394) {
    Serial.print("-   ");
  } else {
    Serial.print(tx3ToRx1Dist);
  }
  Serial.print('\t');
  if(tx3ToRx2Dist == 394) {
    Serial.print("-   ");
  } else {
    Serial.print(tx3ToRx2Dist);
  }
  Serial.print('\t');
  if(tx3ToRx3Dist == 394) {
    Serial.println("-   ");
  } else {
    Serial.println(tx3ToRx3Dist);
  }
  Serial.print('\n');
}

void sonarPing(int txPin, long &rx1Duration, long &rx2Duration, long &rx3Duration, int &rx1Distance, int &rx2Distance, int &rx3Distance) {
  // Clears the trigPins
  digitalWrite(txPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(txPin, HIGH);
  digitalWrite(rxTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(txPin, LOW);
  digitalWrite(rxTrigPin, LOW);
  
  // Reads the echoPins
  long txTime1 = 0;
  long txTime2 = 0;
  long txTime3 = 0;
  long rx1Time = 0;
  long rx2Time = 0;
  long rx3Time = 0;
  long startTime = micros();
  while(true) {
    if(txTime1 == 0 && digitalRead(rx1EchoPin) == HIGH) {
      txTime1 = micros();
    }
    if(txTime1 != 0 && rx1Time == 0 && digitalRead(rx1EchoPin) == LOW) {
      rx1Time = micros();
    }
    if(txTime2 == 0 && digitalRead(rx2EchoPin) == HIGH) {
      txTime2 = micros();
    }
    if(txTime2 != 0 && rx2Time == 0 && digitalRead(rx2EchoPin) == LOW) {
      rx2Time = micros();
    }
    if(txTime3 == 0 && digitalRead(rx3EchoPin) == HIGH) {
      txTime3 = micros();
    }
    if(txTime3 != 0 && rx3Time == 0 && digitalRead(rx3EchoPin) == LOW) {
      rx3Time = micros();
    }
    if(micros() - startTime > 20000) {
      break;
    }
    if(tx1Time != 0 && txTime2 != 0 && txTime3 != 0 && rx1Time != 0 && rx2Time != 0 && rx3Time != 0) {
      break;
    }
  }

  // Write the data to the call-by-reference parameters
  rx1Duration = rx1Time - txTime1;
  rx2Duration = rx2Time - txTime2;
  rx3Duration = rx3Time - txTime3;
  rx1Distance = rx1Duration * 0.034;
  rx2Distance = rx2Duration * 0.034;
  rx3Distance = rx3Duration * 0.034;
}
