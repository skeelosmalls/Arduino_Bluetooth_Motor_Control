#include <SoftwareSerial.h>
//#include <Servo.h>
#include <AFMotor.h>

int bluetoothTx = 1;
int bluetoothRx = 0;
AF_DCMotor motor(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
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
  motor.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  
  
  motor.run(RELEASE);
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
      motor.run(RELEASE);
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
        motor.run(FORWARD);
      }
    }
    if (toSend == 'B' ) //Moves Motor Backwards
    {
      if (flag1 != 2)
      {
        flag1 = 2;
        motor.run(BACKWARD);
      }
    }
    if (toSend == 'C') // Close Hand Test
    {
      if (flag1 != 1)
      {
        flag2 = 1;
        motor.run(FORWARD);
        delay(500);
        motor.run(RELEASE);
      }
    }
     if (toSend == '3') // Close Hand Test
    {
      if (flag1 != 1)
      {
        flag2 = 1;
        motor3.run(FORWARD);
//        delay(500);
//        motor3.run(RELEASE);
      }
    }

  }
}
