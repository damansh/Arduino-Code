#include <SoftwareSerial.h>
SoftwareSerial BT(9, 10); //TX, RX respetively
int motorTRP = 12; 
int motorTRN = 11; 
int motorBRP = 4; 
int motorBRN = 2; 

int motorTLP = 13; 
int motorTLN = A1; 
int motorBLP = A3;
int motorBLN = A6; 
String CONTROL; 

void setup() {
 BT.begin(9600);
 Serial.begin (9600); 
 pinMode(motorTRP, OUTPUT); 
 pinMode(motorTRN, OUTPUT);
 pinMode(motorBRP, OUTPUT);
 pinMode(motorBRN, OUTPUT);
 pinMode(motorTLP, OUTPUT);
 pinMode(motorTLN, OUTPUT);
 pinMode(motorBLP, OUTPUT);
 pinMode(motorBLN, OUTPUT); 
}

char c = BT.read(); //Conduct a serial read

void loop() {
    bluetooth();
    motor();
 }

void bluetooth() {
  while (BT.available()){  //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read

    CONTROL += c; //build the string- "forward", "reverse", "left" and "right"
    }

    if (CONTROL.length() > 0) {
      Serial.println(CONTROL); // print data to serial monitor
      motor();
      CONTROL = "";
  }    
}

void bluetoothOne() {
    delay(10); //Delay added to make thing stable
    char c = BT.read(); //Conduct a serial read
    CONTROL += c; //build the string- "forward", "reverse", "left" and "right"
}


void motor() {
 while (CONTROL == "up") {  // up
  bluetoothOne();  
  digitalWrite(motorTRP, HIGH); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, HIGH); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, HIGH); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, HIGH); 
  digitalWrite(motorBLN, LOW); 
 }
 
 while (CONTROL == "down") { //down
  bluetoothOne();
  digitalWrite(motorTRP, LOW); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, LOW); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, LOW); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, LOW); 
  digitalWrite(motorBLN, LOW); 
 } 
 
 while (CONTROL == "left") {
  bluetoothOne();
  digitalWrite(motorTRP, HIGH); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, HIGH); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, HIGH); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, HIGH); 
  digitalWrite(motorBLN, LOW); 

  delay(750);

  digitalWrite(motorTRP, HIGH); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, HIGH); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, LOW); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, LOW); 
  digitalWrite(motorBLN, LOW); 

  delay(1000); 
 } while (CONTROL == "right") { 
  bluetoothOne();
  digitalWrite(motorTRP, HIGH); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, HIGH); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, HIGH); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, HIGH); 
  digitalWrite(motorBLN, LOW); 

  delay(250);

  digitalWrite(motorTRP, LOW); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, LOW); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, HIGH); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, HIGH); 
  digitalWrite(motorBLN, LOW); 

  delay(1000);

 }  while (CONTROL == "back") {
  bluetoothOne();
  digitalWrite(motorTRP, HIGH); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, HIGH); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, HIGH); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, HIGH); 
  digitalWrite(motorBLN, LOW); 

  delay(250);

  digitalWrite(motorTRP, LOW); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, HIGH); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, LOW); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, HIGH); 
  digitalWrite(motorBLN, LOW);

  delay(1000);

 } while (CONTROL == "forward") {
  bluetoothOne();
  digitalWrite(motorTRP, HIGH); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, HIGH); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, HIGH); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, HIGH); 
  digitalWrite(motorBLN, LOW); 

  delay(500);

  digitalWrite(motorTRP, HIGH); 
  digitalWrite(motorTRN, LOW);   
  digitalWrite(motorBRP, LOW); 
  digitalWrite(motorBRN, LOW);   

  digitalWrite(motorTLP, HIGH); 
  digitalWrite(motorTLN, LOW);   
  digitalWrite(motorBLP, LOW); 
  digitalWrite(motorBLN, LOW);

  delay(1500);
 }
}


 
