// Coded by Daman Sharma
 
int ltPowerOne = 6;
int ltFwdOne = 7;
int ltBwdOne = 8;

int ltPowerTwo = 1;
int ltFwdTwo = 2;
int ltBwdTwo = 3;

int buzzer = 9;

#include <SoftwareSerial.h>

SoftwareSerial BT(18, 19); //TX, RX respetively
String readdata;

int maximumRange = 10; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
    BT.begin(9600);
   Serial.begin(9600);  
   pinMode(ltPowerOne, OUTPUT); 
   pinMode(ltFwdOne, OUTPUT); 
   pinMode(ltBwdOne, OUTPUT); 

   pinMode(ltPowerTwo, OUTPUT); 
   pinMode(ltFwdTwo, OUTPUT); 
   pinMode(ltBwdTwo, OUTPUT); 
}

void loop() {
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
    digitalWrite(ltFwdOne, HIGH);
    digitalWrite(ltFwdTwo, LOW);
    delay(100);
  }
  // if data received as reverse move robot reverse

  else if(readdata == "reverse")
  {
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, LOW);
    digitalWrite(ltBwdOne, HIGH);
    digitalWrite(ltBwdTwo, HIGH);
    delay(100);
  }
// if data received as right turn robot to right direction.
  else if (readdata == "right")
  {
    digitalWrite (ltFwdOne, HIGH);
    digitalWrite (ltFwdTwo, LOW);
    digitalWrite (ltBwdOne, LOW);
    digitalWrite (ltBwdTwo, LOW);
    delay (100);
   
  }
// if data received as left turn robot to left direction
 else if ( readdata == "left")
 {
   digitalWrite (ltFwdOne, LOW);
   digitalWrite (ltFwdTwo, HIGH);
   digitalWrite (ltBwdOne, LOW);
   digitalWrite (ltBwdTwo, LOW);
   delay (100);
 }
 // if data received as stop, halt the robot

 else if (readdata == "stop")
 {
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, HIGH);
   delay (100);
 }

readdata="";}} //Reset the variable


