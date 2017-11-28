void setup() {
  pinMode(6, OUTPUT); // A                
  pinMode(1, OUTPUT); // B 
  pinMode(2, OUTPUT); // C
  pinMode(3, OUTPUT); // D
  pinMode(4, OUTPUT); // E
  pinMode(5, OUTPUT); // F
  pinMode(7, OUTPUT); // G
  pinMode(8, OUTPUT); // Ground
  pinMode(9, OUTPUT); // Power
  digitalWrite(9, 0);  // start with the "dot" off
}

void loop() {
 // write '6'
 digitalWrite(6, 0); // A
 digitalWrite(1, 1); // B
 digitalWrite(2, 0); // C
 digitalWrite(3, 0); // D
 digitalWrite(4, 0); // E
 digitalWrite(5, 0); // F
 digitalWrite(7, 0); // G
 digitalWrite(8, 1); // Ground
 digitalWrite(9, 1); // Power
 delay(1000);
/* // write '8'
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // write '7'
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(1000);
 // write '6'
 digitalWrite(2, 1);
 digitalWrite(3, 0);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // write '5'
 digitalWrite(2, 1);
 digitalWrite(3, 0);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 0);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // write '4'
 digitalWrite(2, 0);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(1000);
 // write '3'
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 1);
 delay(1000);
 // write '2'
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 0);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 0);
 digitalWrite(8, 1);
 delay(1000);
 // write '1'
 digitalWrite(2, 0);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(1000);
 // write '0'
 digitalWrite(2, 1);
 digitalWrite(3, 1);
 digitalWrite(4, 1);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 0);
 delay(4000);
 */
}
