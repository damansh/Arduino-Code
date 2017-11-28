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
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}


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
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
  if (devStatus == 0) {
      // turn on the DMP, now that it's ready
      Serial.println(F("Enabling DMP..."));
      mpu.setDMPEnabled(true);

      // enable Arduino interrupt detection
      Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
      attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();

      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      Serial.println(F("DMP ready! Waiting for first interrupt..."));
      dmpReady = true;

      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
  }
  pinMode(LED_PIN, OUTPUT); 
}

char c = BT.read(); //Conduct a serial read

void loop() {
    bluetooth();
    motor();
    if (!dmpReady) return;
    while (!mpuInterrupt && fifoCount < packetSize) {
    }
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));
    } else if (mpuIntStatus & 0x02) {
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;

        #ifdef OUTPUT_READABLE_QUATERNION
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            Serial.print("quat\t");
            Serial.print(q.w);
            Serial.print("\t");
            Serial.print(q.x);
            Serial.print("\t");
            Serial.print(q.y);
            Serial.print("\t");
            Serial.println(q.z);
        #endif

        #ifdef OUTPUT_READABLE_EULER
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetEuler(euler, &q);
            Serial.print("euler\t");
            Serial.print(euler[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(euler[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(euler[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_READABLE_REALACCEL
            // display real acceleration, adjusted to remove gravity
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            Serial.print("areal\t");
            Serial.print(aaReal.x);
            Serial.print("\t");
            Serial.print(aaReal.y);
            Serial.print("\t");
            Serial.println(aaReal.z);
        #endif

        #ifdef OUTPUT_READABLE_WORLDACCEL
            // display initial world-frame acceleration, adjusted to remove gravity
            // and rotated based on known orientation from quaternion
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            Serial.print("aworld\t");
            Serial.print(aaWorld.x);
            Serial.print("\t");
            Serial.print(aaWorld.y);
            Serial.print("\t");
            Serial.println(aaWorld.z);
        #endif
    
        #ifdef OUTPUT_TEAPOT
            // display quaternion values in InvenSense Teapot demo format:
            teapotPacket[2] = fifoBuffer[0];
            teapotPacket[3] = fifoBuffer[1];
            teapotPacket[4] = fifoBuffer[4];
            teapotPacket[5] = fifoBuffer[5];
            teapotPacket[6] = fifoBuffer[8];
            teapotPacket[7] = fifoBuffer[9];
            teapotPacket[8] = fifoBuffer[12];
            teapotPacket[9] = fifoBuffer[13];
            Serial.write(teapotPacket, 14);
            teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
        #endif

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
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


