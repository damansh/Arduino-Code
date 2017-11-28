/*
  Drive 
  controls one DC motors to drive a small robot
 */

#define echoPin 12 // Echo Pin
#define trigPin 11 // Trigger Pin
#define LEDPin 13
 
int ltPowerOne = 6;
int ltFwdOne = 7;
int ltBwdOne = 8;

int ltPowerTwo = 1;
int ltFwdTwo = 2;
int ltBwdTwo = 3;

int maximumRange = 10; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {                
   Serial.begin(9600);  
   pinMode(ltPowerOne, OUTPUT); 
   pinMode(ltFwdOne, OUTPUT); 
   pinMode(ltBwdOne, OUTPUT); 

   pinMode(ltPowerTwo, OUTPUT); 
   pinMode(ltFwdTwo, OUTPUT); 
   pinMode(ltBwdTwo, OUTPUT); 

   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
  
}

void loop() {  

 digitalWrite(trigPin, LOW);  
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);

 distance = duration/58.2;

}


  if (distance >= maximumRange || distance <= minimumRange) // set to drive forward
  {
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltBwdOne, HIGH);

    digitalWrite(ltFwdTwo, LOW);
    digitalWrite(ltBwdTwo, HIGH);
  }
  else // set to drive in reverse
  {
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltBwdOne, LOW);

    digitalWrite(ltFwdTwo, LOW);
    digitalWrite(ltBwdTwo, LOW);
    
  }
}


