
int photocellPin = 1; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the analog resistor divider
int motorPOS = 2;
int speaker = 9;
int light = A4;
float motorValue;
float LEDBrightness;
float temp;  
float photocellReadingRevised;
float percent;

void setup() {
   Serial.begin(9600); 
   pinMode(motorPOS, OUTPUT); 
   pinMode(speaker, OUTPUT);
   pinMode(light, OUTPUT);
}

void loop() {
  photoCell();
  while (photocellReading > 20) {
     photoCell();
     LEDFade();
     noTone(speaker); 
     digitalWrite(motorPOS, HIGH);
     delay(125);
     digitalWrite(motorPOS, LOW);
     delay(400);
  } 
  
  while (photocellReading < 20) {
    photoCell();
    tone(speaker, 1000, 1000);
    tone(speaker, 500, 1000); 
    digitalWrite(motorPOS, HIGH);
    LED();
  } 
}

void photoCell() {
    photocellReading = analogRead(photocellPin);
    temp = 120 - photocellReading;
    percent = temp/160; 
    if (percent < 0.55) {
      motorValue = 125;
    } else {
    motorValue = 255*percent;  
    }  
  Serial.println(photocellReading);
}

void LEDFade() {
   photocellReadingRevised = 150 - photocellReading;
   LEDBrightness = map(photocellReadingRevised, 0, 150, 100, 250);
   analogWrite(light, LEDBrightness);
   //Serial.println(LEDBrightness);
}

void LED() {
  digitalWrite(light, HIGH);
  delay(200);
  digitalWrite(light, LOW);
  delay(200);
}

