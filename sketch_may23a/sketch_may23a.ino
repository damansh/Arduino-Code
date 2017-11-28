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
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(motorOne, OUTPUT);
 pinMode(motorTwo, OUTPUT);
 pinMode(motorThree, OUTPUT);
 pinMode(motorFour, OUTPUT);
}

void loop() {
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
  } else if (distance < 50) {
    digitalWrite(motorOne, HIGH);
    digitalWrite(motorTwo, HIGH);
    digitalWrite(motorThree, HIGH);
    digitalWrite(motorFour, HIGH);
  }
}
