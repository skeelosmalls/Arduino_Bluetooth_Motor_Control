#include <SoftwareSerial.h>

#include <Servo.h>
#include <AFMotor.h>

#define BUFFERSIZE 10
uint8_t inBuffer[BUFFERSIZE];
int inLength; // length of data in the buffer
int numLoop = 0; // number of times we looped
//int ledPin = 13;

String readString;

int bluetoothTx = 1;
int bluetoothRx = 0;

AF_DCMotor motor(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  // put your setup code here, to run once:
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

  motor.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  
//  myservo.attach(10);
  
  motor.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

//void loop() {
//   if (bluetooth.available() > 0){
//    inLength =  0;
//    while (bluetooth.available()) {
//      inBuffer[ inLength] = bluetooth.read();
//      inLength++;
//      char toSend = (char)bluetooth.read();
//      if (toSend == 'E')
//         break;
//    }
////      bluetooth.readBytes(rxdata, 14);
////      Serial.write(inBuffer ,inLength);
//    inBuffer
//      motor.run(FORWARD);
//      
//        delay(500);
//        motor.run(RELEASE);
//   }
//}
void loop() {
while (bluetooth.available()) {
    delay(3);  
    char c = bluetooth.read();
    readString += c; 
  }
  if (readString.length() >0) {
//    Serial.println(readString);
    if (readString == "M1-forward")     
    {
      motor.run(FORWARD);
    }
    if (readString == "M1-stop")
    {
      motor.run(RELEASE);
    }
    readString="";
  } 
//  bluetooth.write("Received: "); // Send the message back to the pc terminal
//  bluetooth.write(input);
}

