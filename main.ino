#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;

SoftwareSerial Bluetooth(3, 4); // Arduino(RX, TX)

int servo1Pos, servo2Pos, servo3Pos, servo4Pos; // current position
int servo1PPos, servo2PPos, servo3PPos, servo4PPos; // previous position

int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50]; // storing steps

int speedDelay = 20;
int index = 0;
String dataIn = "";

void setup() {
  servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  servo04.attach(8);

  Bluetooth.begin(38400);
  Bluetooth.setTimeout(1);
  delay(20);

  // Initial position
  servo1PPos = 90;
  servo01.write(servo1PPos);

  servo2PPos = 150;
  servo02.write(servo2PPos);

  servo3PPos = 35;
  servo03.write(servo3PPos);

  servo4PPos = 140;
  servo04.write(servo4PPos);
}

void loop() {
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();

    // Servo 1 (Waist)
    if (dataIn.startsWith("s1")) {
      String dataInS = dataIn.substring(2);
      servo1Pos = dataInS.toInt();

      if (servo1PPos > servo1Pos) {
        for (int j = servo1PPos; j >= servo1Pos; j--) {
          servo01.write(j);
          delay(20);
        }
      }
      if (servo1PPos < servo1Pos) {
        for (int j = servo1PPos; j <= servo1Pos; j++) {
          servo01.write(j);
          delay(20);
        }
      }
      servo1PPos = servo1Pos;
    }

    // Servo 2 (Shoulder)
    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2);
      servo2Pos = dataInS.toInt();

      if (servo2PPos > servo2Pos) {
        for (int j = servo2PPos; j >= servo2Pos; j--) {
          servo02.write(j);
          delay(50);
        }
      }
      if (servo2PPos < servo2Pos) {
        for (int j = servo2PPos; j <= servo2Pos; j++) {
          servo02.write(j);
          delay(50);
        }
      }
      servo2PPos = servo2Pos;
    }

    // Servo 3 (Elbow)
    if (dataIn.startsWith("s3")) {
      String dataInS = dataIn.substring(2);
      servo3Pos = dataInS.toInt();

      if (servo3PPos > servo3Pos) {
        for (int j = servo3PPos; j >= servo3Pos; j--) {
          servo03.write(j);
          delay(30);
        }
      }
      if (servo3PPos < servo3Pos) {
        for (int j = servo3PPos; j <= servo3Pos; j++) {
          servo03.write(j);
          delay(30);
        }
      }
      servo3PPos = servo3Pos;
    }

    // Servo 4 (Gripper)
    if (dataIn.startsWith("s4")) {
      String dataInS = dataIn.substring(2);
      servo4Pos = dataInS.toInt();

      if (servo4PPos > servo4Pos) {
        for (int j = servo4PPos; j >= servo4Pos; j--) {
          servo04.write(j);
          delay(30);
        }
      }
      if (servo4PPos < servo4Pos) {
        for (int j = servo4PPos; j <= servo4Pos; j++) {
          servo04.write(j);
          delay(30);
        }
      }
      servo4PPos = servo4Pos;
    }

    // SAVE
    if (dataIn.startsWith("SAVE")) {
      servo01SP[index] = servo1PPos;
      servo02SP[index] = servo2PPos;
      servo03SP[index] = servo3PPos;
      servo04SP[index] = servo4PPos;
      index++;
    }

    // RUN
    if (dataIn.startsWith("RUN")) {
      runservo();
    }

    // RESET
    if (dataIn == "RESET") {
      memset(servo01SP, 0, sizeof(servo01SP));
      memset(servo02SP, 0, sizeof(servo02SP));
      memset(servo03SP, 0, sizeof(servo03SP));
      memset(servo04SP, 0, sizeof(servo04SP));
      index = 0;
    }
  }
}

// RUN FUNCTION
void runservo() {
  while (dataIn != "RESET") {
    for (int i = 0; i <= index - 2; i++) {

      if (Bluetooth.available() > 0) {
        dataIn = Bluetooth.readString();

        if (dataIn == "PAUSE") {
          while (dataIn != "RUN") {
            if (Bluetooth.available() > 0) {
              dataIn = Bluetooth.readString();
              if (dataIn == "RESET") break;
            }
          }
        }

        if (dataIn.startsWith("ss")) {
          speedDelay = dataIn.substring(2).toInt();
        }
      }

      // Servo 1
      if (servo01SP[i] > servo01SP[i + 1]) {
        for (int j = servo01SP[i]; j >= servo01SP[i + 1]; j--) {
          servo01.write(j);
          delay(speedDelay);
        }
      }
      if (servo01SP[i] < servo01SP[i + 1]) {
        for (int j = servo01SP[i]; j <= servo01SP[i + 1]; j++) {
          servo01.write(j);
          delay(speedDelay);
        }
      }

      // Servo 2
      if (servo02SP[i] > servo02SP[i + 1]) {
        for (int j = servo02SP[i]; j >= servo02SP[i + 1]; j--) {
          servo02.write(j);
          delay(speedDelay);
        }
      }
      if (servo02SP[i] < servo02SP[i + 1]) {
        for (int j = servo02SP[i]; j <= servo02SP[i + 1]; j++) {
          servo02.write(j);
          delay(speedDelay);
        }
      }

      // Servo 3
      if (servo03SP[i] > servo03SP[i + 1]) {
        for (int j = servo03SP[i]; j >= servo03SP[i + 1]; j--) {
          servo03.write(j);
          delay(speedDelay);
        }
      }
      if (servo03SP[i] < servo03SP[i + 1]) {
        for (int j = servo03SP[i]; j <= servo03SP[i + 1]; j++) {
          servo03.write(j);
          delay(speedDelay);
        }
      }

      // Servo 4
      if (servo04SP[i] > servo04SP[i + 1]) {
        for (int j = servo04SP[i]; j >= servo04SP[i + 1]; j--) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
      if (servo04SP[i] < servo04SP[i + 1]) {
        for (int j = servo04SP[i]; j <= servo04SP[i + 1]; j++) {
          servo04.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}