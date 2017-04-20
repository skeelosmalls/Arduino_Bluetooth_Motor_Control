#include <SoftwareSerial.h>
#include <Servo.h>
#include <AFMotor.h>

int bluetoothTx = 1;
int bluetoothRx = 0;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Servo myservo;

int pos = 0;    // variable to store the servo position
int motor_speed = 255; //0- 255
//
//int Motor1A = 8;
//int Motor1B = 9;
//int Motor2A = 10;
//int Motor2B = 11;

void setup()
{
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);
  // turn on motor
  motor1.setSpeed(motor_speed);
  motor2.setSpeed(motor_speed);
  motor3.setSpeed(motor_speed);
  motor4.setSpeed(motor_speed);
  
//  myservo.attach(10);
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
int flag1 = -1;
int flag2 = -1;

void loop()
{
  if (bluetooth.available())
  { 
    char toSend = (char)bluetooth.read();

    //    Serial.print(toSend);
    if (toSend == 'S') //Stops Motors
    {
      flag1 = 0;
      flag2 = 0;
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
    }
    if (toSend == 'F' ) // Moves Motor Forward
    {
      if (flag1 != 1)
      {
        flag1 = 1;
        //          digitalWrite( Motor1A, HIGH );
        //          analogWrite( Motor1B, 50 );
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
      }
    }
    if (toSend == 'B' ) //Moves Motor Backwards
    {
      if (flag1 != 2)
      {
        flag1 = 2;
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
      }
    }
    if (toSend == 'C') // Close Hand Test
    {
      if (flag1 != 1)
      {
        flag2 = 1;
        motor1.run(FORWARD);
        delay(500);
        motor1.run(RELEASE);
      }
    }
     if (toSend == 'L') // Close Hand Test
    {
//      if (flag1 != 1)
//      {
        flag2 = 1;
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        motor3.run(BACKWARD);
        motor4.run(BACKWARD);
//      }
    }
    if (toSend == 'R') // Close Hand Test
    {
//      if (flag1 != 1)
//      {
        flag2 = 1;
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        motor3.run(FORWARD);
        motor4.run(FORWARD);
//      }
    }
     if (toSend == 'W') // Close Hand Test
    {
//      if (flag1 != 1)
//      {
//        flag2 = 1;  
        motor1.run(FORWARD);
//        motor2.run(BACKWARD);
//        motor3.run(FORWARD);
        motor4.run(FORWARD);

//      }
    }
    if (toSend == 'M')
    {
      
      for (pos = 180; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(180);              // tell servo to go to position in variable 'pos'
        delay(5);                       // waits 15ms for the servo to reach the position
      }
    }
  }
}
