#include <SoftwareSerial.h>
//#include <Servo.h>
#include <AFMotor.h>

int bluetoothTx = 1;
int bluetoothRx = 0;
AF_DCMotor motor(1);
AF_DCMotor motor3(3);

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
  motor3.setSpeed(255);
  
  motor3.run(RELEASE);
  motor.run(RELEASE);
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
      motor3.run(RELEASE);
    }
    if (toSend == 'F' || toSend == 'G' || toSend == 'I') // Moves Motor Forward
    {
      if (flag1 != 1)
      {
        flag1 = 1;
        //          digitalWrite( Motor1A, HIGH );
        //          analogWrite( Motor1B, 50 );
        motor.run(FORWARD);
      }
    }
    if (toSend == 'B' || toSend == 'H' || toSend == 'J') //Moves Motor Backwards
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
