int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the sensor divider
int LEDpin = 11; // connect Red LED to pin 11 (PWM pin)
int LEDbrightness; // 

void setup() {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600); 
  
}

void loop() {
  photocellReading = analogRead(photocellPin); 
  
  Serial.print("Analog reading = ");
  Serial.println(photocellReading); // the raw analog reading
  
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  analogWrite(LEDpin, LEDbrightness);
  
  delay(100);
}



OR 


int photocellPin = 0; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the analog resistor divider

void setup(void) {
// We'll send debugging information via the Serial monitor
Serial.begin(9600); 
}

void loop(void) {
photocellReading = analogRead(photocellPin); 

Serial.print("Analog reading = ");
Serial.print(photocellReading); // the raw analog reading

// We'll have a few threshholds, qualitatively determined
if (photocellReading < 10) {
Serial.println(" - Dark");
} else if (photocellReading < 200) {
Serial.println(" - Dim");
} else if (photocellReading < 500) {
Serial.println(" - Light");
} else if (photocellReading < 800) {
Serial.println(" - Bright");
} else {
Serial.println(" - Very bright");
}
delay(1000);
}

