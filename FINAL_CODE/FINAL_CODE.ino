// Coded by Daman Sharma

int echoPin = 2; // Echo Pin
int trigPin = 3; // Trigger Pin
 
int ltPowerOne = 9;
int ltFwdOne = 5;
int ltBwdOne = 6;

int ltPowerTwo = 4;
int ltFwdTwo = 7;
int ltBwdTwo = 8;

int speaker = 9;
const int button = 4;
int buttonState = 0;  
int LEDFront1 = 14;
int LEDFront2 = 15;
int LEDBack1 = 16;
int LEDBack2 = 17;


int maximumRange = 10; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

#include <SoftwareSerial.h>

SoftwareSerial BT(11, 12); //TX, RX respetively
String readdata;

void setup() {
   BT.begin(9600);
   Serial.begin(9600);  
   
   pinMode(ltPowerOne, OUTPUT); 
   pinMode(ltFwdOne, OUTPUT); 
   pinMode(ltBwdOne, OUTPUT); 

   pinMode(ltPowerTwo, OUTPUT); 
   pinMode(ltFwdTwo, OUTPUT); 
   pinMode(ltBwdTwo, OUTPUT); 

   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT); // Use LED indicator (if required)
   pinMode(button, INPUT);

   pinMode(LEDFront1, OUTPUT);
   pinMode(LEDFront2, OUTPUT);
   pinMode(LEDBack1, OUTPUT);
   pinMode(LEDBack2, OUTPUT);
}

void loop() {
  buttonState = digitalRead(button);
  
 if (buttonState == LOW) { 
  
  
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  }  
  if (readdata.length() > 0) {
    Serial.println(readdata); // print data to serial monitor
// if data received as forward move robot forward
  if(readdata == "forward") 
  {
    digitalWrite(LEDFront1, HIGH);
    digitalWrite(LEDFront2, HIGH);
    digitalWrite(LEDBack1, LOW);
    digitalWrite(LEDBack2, LOW);
    digitalWrite(ltFwdOne, HIGH);
    digitalWrite(ltFwdTwo, HIGH);
    delay(100);
  }
  // if data received as reverse move robot reverse

  else if(readdata == "reverse")
  {
    digitalWrite(LEDFront1, HIGH);
    digitalWrite(LEDFront2, HIGH);
    digitalWrite(LEDBack1, HIGH);
    digitalWrite(LEDBack2, HIGH);
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, LOW);
    delay(100);
  }
// if data received as right turn robot to right direction.
  else if (readdata == "right")
  {
    digitalWrite(LEDFront1, LOW);
    digitalWrite(LEDFront2, HIGH);
    digitalWrite(LEDBack2, HIGH);
    digitalWrite(LEDBack1, LOW);
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, HIGH);
    delay(100);
   
  }
// if data received as left turn robot to left direction
 else if ( readdata == "left")
 {
    digitalWrite(LEDFront1, HIGH);
    digitalWrite(LEDFront2, LOW);
    digitalWrite(LEDBack1, HIGH);
    digitalWrite(LEDBack2, LOW);
    digitalWrite(ltFwdOne, HIGH);
    digitalWrite(ltFwdTwo, LOW);
    delay(100);
 }
 // if data received as stop, halt the robot

 else if (readdata == "stop")
 {
    digitalWrite(LEDFront1, HIGH);
    digitalWrite(LEDFront2, HIGH);
    digitalWrite(LEDBack1, HIGH);
    digitalWrite(LEDBack2, HIGH);
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, LOW);
   delay (100);
 }
readdata="";}
 } 
 
 if (buttonState == HIGH){
  
   digitalWrite(trigPin, LOW);  
   delayMicroseconds(2); 

   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10); 
   
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
  
   distance = duration/58.2;

   if (distance  >= maximumRange) {
    digitalWrite(LEDFront1, HIGH);
    digitalWrite(LEDFront2, HIGH);
    digitalWrite(LEDBack1, LOW);
    digitalWrite(LEDBack2, LOW);
    digitalWrite(ltFwdOne, HIGH);
    digitalWrite(ltFwdTwo, HIGH);
    noTone(9);
   }
   else {
    digitalWrite(LEDFront1, HIGH);
    digitalWrite(LEDFront2, HIGH);
    digitalWrite(LEDBack1, HIGH);
    digitalWrite(LEDBack2, HIGH);
    tone(9,1000,5000);
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, HIGH);
    delay(2000);
   }
  }


}
