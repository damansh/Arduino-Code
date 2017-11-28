int val1;
int val2;
int val3;
int seven_seg_digits[10][4] = { { 0,0,0,0 },  // = 0
                                 { 0,0,0,1 },  // = 1
                                 { 0,0,1,0 },  // = 2
                                 { 0,0,1,1 },  // = 3
                                 { 0,1,0,0 },  // = 4
                                 { 0,1,0,1 },  // = 5
                                 { 0,1,1,0 },  // = 6
                                 { 0,1,1,1 },  // = 7
                                 { 1,0,0,0 },  // = 8
                                 { 1,0,0,1 }   // = 9
                                 };


void setup() 
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void disp1(int digit) {
  int pin = 2;
  for (int segCount = 0; segCount < 4; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}
  
void disp2(int digit) {
  int pin = 6;
  for (int segCount = 0; segCount < 4; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

/*void disp3(int digit) {
  int pin = 10;
  for (int segCount = 0; segCount < 4; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}*/

void disp3(int digit)
{
  digitalWrite(10, seven_seg_digits[digit][0]);
  digitalWrite(11, seven_seg_digits[digit][1]);
  digitalWrite(12, seven_seg_digits[digit][2]);
  digitalWrite(13, seven_seg_digits[digit][3]);
}

void loop ()
{
  for(int ioo = 0; ioo<10; ioo++)
  {
    for (int oio = 0; oio<10; oio++)
    {
      for (int ooi = 0; ooi<10; ooi++)
      {
        disp3(ooi);
        delay(1000);
      }
      disp2(oio);
      delay(2000);
    }
    disp1(ioo);
    delay(2000);
  }
}
