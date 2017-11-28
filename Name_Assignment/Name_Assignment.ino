/* Daman Sharma
 * TEJ4MR - A 
 * April 5, 2017
 * Arduino Name Assignment
 */

void setup() {                
  pinMode(2, OUTPUT); // Segment A  
  pinMode(3, OUTPUT); // Segment B
  pinMode(4, OUTPUT); // Segment C
  pinMode(5, OUTPUT); // Segment D
  pinMode(6, OUTPUT); // Segment E
  pinMode(7, OUTPUT); // Segment F
  pinMode(8, OUTPUT); // Segment G
  pinMode(9, OUTPUT); // Dot
}

byte damanSharma[47][8] = { { 1,0,0,0,0,1,0,1 }, //  D
                           { 0,0,0,0,0,1,0,1 }, //  A
                           { 0,1,0,1,0,1,1,1 }, //  M
                           { 0,0,0,0,0,1,0,1 }, //  A
                           { 1,1,0,1,0,1,0,1 }, //  N
                           { 1,1,1,1,1,1,1,1 }, //  Space
                           { 0,1,0,0,1,0,0,1 }, //  S
                           { 1,1,0,1,0,0,0,1 }, //  H
                           { 0,0,0,0,0,1,0,1 }, //  A
                           { 1,1,1,1,0,1,0,1 }, //  R
                           { 0,1,0,1,0,1,1,1 }, //  M
                           { 0,0,0,0,0,1,0,0 }, //  A
                           // Turns 180 degrees
                           { 1,0,0,0,0,1,0,0 },
                           { 1,1,0,0,0,1,0,0 },
                           { 1,1,1,0,0,1,0,0 },
                           { 1,1,1,1,0,1,0,0 },
                           { 1,1,1,1,1,1,0,0 },
                           { 1,1,1,1,1,1,1,0 },
                           { 1,1,1,1,1,1,1,1 },
                           { 1,1,1,1,0,1,1,1 },
                           { 1,1,1,1,0,0,1,1 },
                           { 0,1,1,1,0,0,1,1 },
                           { 0,0,1,1,0,0,1,1 },
                           // Backwards
                           { 0,0,1,1,0,0,0,1 }, // Backwards D
                           { 0,0,1,0,0,0,0,1 }, // Backwards A
                           { 1,0,1,0,1,0,1,1 }, // Backwards M
                           { 0,0,1,0,0,0,0,1 }, // Backwards A
                           { 1,0,1,1,1,0,0,1 }, // Backwards N
                           { 1,1,1,1,1,1,1,1 }, // = Space
                           { 0,1,0,0,1,0,0,1 }, // Backwards S
                           { 1,0,0,1,1,0,0,1 }, // Backwards H
                           { 0,0,1,0,0,0,0,1 }, // Backwards A
                           { 1,0,1,1,1,1,0,1 }, // Backwards R
                           { 1,0,1,0,1,0,1,1 }, // Backwards M
                           { 0,0,1,0,0,0,0,0 }, // Backwards A
                           // Turns 180 degrees
                           { 1,0,1,0,0,0,0,0 },
                           { 1,1,1,0,0,0,0,0 },
                           { 1,1,1,1,0,0,0,0 },
                           { 1,1,1,1,1,0,0,0 },
                           { 1,1,1,1,1,1,0,0 },
                           { 1,1,1,1,1,1,1,0 },
                           { 1,1,1,1,1,1,1,1 },
                           { 1,0,1,1,1,1,1,1 },
                           { 1,0,0,1,1,1,1,1 },
                           { 1,0,0,0,1,1,1,1 },
                           { 1,0,0,0,0,1,1,1 },
                           { 1,0,0,0,0,1,0,1 }, 
                           };

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 8; ++segCount) {
    digitalWrite(pin, damanSharma[digit][segCount]);
    ++pin;
  }
}

void loop() {
  for (byte count = 1; count < 48; ++count) {
   delay(500);
   sevenSegWrite(count - 1); 
  }
  delay(250);
}
