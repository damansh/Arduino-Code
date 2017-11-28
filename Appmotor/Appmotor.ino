int ltPowerOne = 6;
int ltFwdOne = 7;
int ltBwdOne = 8;

int ltPowerTwo = 1;
int ltFwdTwo = 2;
int ltBwdTwo = 3;
int LEDpin = 13;

int estado ;

void setup() { 
   Serial.begin(9600);  
   pinMode(ltPowerOne, OUTPUT); 
   pinMode(ltFwdOne, OUTPUT); 
   pinMode(ltBwdOne, OUTPUT); 

   pinMode(ltPowerTwo, OUTPUT); 
   pinMode(ltFwdTwo, OUTPUT); 
   pinMode(ltBwdTwo, OUTPUT); 
} 

void loop() { 

estado = Serial.read();

if(Serial.available()>0){ // lee el bluetooth y almacena en estado
  

}
else if(estado=='a'){ // Boton desplazar al Frente
    digitalWrite (LEDpin, HIGH);
    digitalWrite(ltFwdOne, HIGH);
    digitalWrite(ltFwdTwo, LOW);
    delay(100);
}
else if(estado=='b'){ // Boton IZQ 
    digitalWrite (LEDpin, LOW);
    digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, LOW);
    digitalWrite(ltBwdOne, HIGH);
    digitalWrite(ltBwdTwo, HIGH);
    delay(100);
}
else if(estado=='c'){ // Boton Parar
    digitalWrite (LEDpin, HIGH);
    digitalWrite (ltFwdOne, HIGH);
    digitalWrite (ltFwdTwo, LOW);
    digitalWrite (ltBwdOne, LOW);
    digitalWrite (ltBwdTwo, LOW);
    delay (100);
}
else if(estado=='d'){ // Boton DER
   digitalWrite (LEDpin, LOW);
   digitalWrite (ltFwdOne, LOW);
   digitalWrite (ltFwdTwo, HIGH);
   digitalWrite (ltBwdOne, LOW);
   digitalWrite (ltBwdTwo, LOW);
   delay (100);
} 

else if(estado=='e'){ // Boton Reversa
  digitalWrite(ltFwdOne, LOW);
    digitalWrite(ltFwdTwo, HIGH);
   delay (100);
}
}
