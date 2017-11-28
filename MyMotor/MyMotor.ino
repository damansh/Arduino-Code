// Coded by Daman Sharma

int echoPin = 2; // Echo Pin
int trigPin = 3; // Trigger Pin
int LEDPin = 13;
 
int ltPowerOne = 9;
int ltFwdOne = 5;
int ltBwdOne = 6;

int ltPowerTwo = 4;
int ltFwdTwo = 7;
int ltBwdTwo = 8;

int buzzer = 9;
int Speaker = 10;

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

   if (distance  >= maximumRange) {
    digitalWrite(ltFwdOne, HIGH);
    digitalWrite(ltFwdTwo, HIGH);
    digitalWrite(LEDPin, HIGH);
    noTone(9);
   }
   else {
    tone(9,1000,5000);
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, HIGH);
    delay(2000);
   
    
   }
}
