#include <SoftwareSerial.h>
SoftwareSerial BT(11, 12); //TX, RX respetively
String readdata;

#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int motorOne = 9;
int motorTwo = 10;
int motorThree = 11;
int motorFour = 12;

void setup() {
 BT.begin(9600);
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(motorOne, OUTPUT);
 pinMode(motorTwo, OUTPUT);
 pinMode(motorThree, OUTPUT);
 pinMode(motorFour, OUTPUT);
}

void loop() {
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make Bluetooth module stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  }  
  if (readdata.length() > 0) {
    Serial.println(readdata); // print data to serial monitor

  if (readdata == "ON") { 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
  
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10); 
   
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   
   distance = duration/58.2;

  if (distance > 50) {
     digitalWrite(motorOne, LOW);
     digitalWrite(motorTwo, LOW);
     digitalWrite(motorThree, LOW);
     digitalWrite(motorFour, LOW);
  } 
  if (distance < 50) {
    digitalWrite(motorOne, HIGH);
    digitalWrite(motorTwo, HIGH);
    digitalWrite(motorThree, HIGH);
    digitalWrite(motorFour, HIGH);
  }
  }
  else if (readdata == "OFF") {
    digitalWrite(motorOne, LOW);
    digitalWrite(motorTwo, LOW);
    digitalWrite(motorThree, LOW);
    digitalWrite(motorFour, LOW);
  } 
  readdata="";}
}
