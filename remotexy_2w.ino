/*
   -- New project --

   This source code of graphical user interface
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.3.5 or later version
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/
     - for ANDROID 4.3.1 or later version;
     - for iOS 1.3.5 or later version;

   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate
#pragma pack(push, 1)
/* RemoteXY configurate  */
unsigned char RemoteXY_CONF[] =
{ 3, 0, 23, 0, 1, 5, 5, 15, 41, 11
  , 43, 43, 1, 2, 0, 6, 5, 27, 11, 5
  , 79, 78, 0, 79, 70, 70, 0
};

/* this structure defines all the variables of your control interface */
struct {

  /* input variable */
  signed char joystick_1_x; /* =-100..100 x-coordinate joystick position */
  signed char joystick_1_y; /* =-100..100 y-coordinate joystick position */
  unsigned char switch_1; /* =1 if switch ON and =0 if OFF */

  /* other variable */
  unsigned char connect_flag;  /* =1 if wire connected, else =0 */

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

/* defined the right motor control pins */
#define PIN_MOTOR_RIGHT_UP 7
#define PIN_MOTOR_RIGHT_DN 6
#define PIN_MOTOR_RIGHT_REVERSE 0
#define PIN_MOTOR_RIGHT_SPEED 5

/* defined the left motor control pins */
#define PIN_MOTOR_LEFT_UP 5
#define PIN_MOTOR_LEFT_DN 4
#define PIN_MOTOR_LEFT_REVERSE 2
#define PIN_MOTOR_LEFT_SPEED 4

//int PWMA=5;//Right side
//int PWMB=4;//Left side
//int DA=0;//Right reverse
//int DB=2;//Left reverse

/* defined the LED pin */
#define PIN_LED 13


/* defined two arrays with a list of pins for each motor */
unsigned char RightMotor[2] =
{PIN_MOTOR_RIGHT_REVERSE, PIN_MOTOR_RIGHT_SPEED};
unsigned char LeftMotor[2] =
{PIN_MOTOR_LEFT_REVERSE, PIN_MOTOR_LEFT_SPEED};

/*
   speed control of the motor
   motor - pointer to an array of pins
   v - motor speed can be set from -100 to 100
*/
void Wheel (unsigned char * motor, int v)
{
  if (v > 100) v = 100;
  if (v < -100) v = -100;
  if (v > -40 && v < 40) v = 0;
  if (v > 0) {
    //digitalWrite(motor[0], HIGH);
    //digitalWrite(motor[1], LOW);
    digitalWrite(motor[0], LOW);
    analogWrite(motor[1], v * (PWMRANGE / 125));
  }
  else if (v < 0) {
    //digitalWrite(motor[0], LOW);
    //digitalWrite(motor[1], HIGH);
    digitalWrite(motor[0], HIGH);
    analogWrite(motor[1], (-v) * (PWMRANGE / 125));
  }
  else {
    //digitalWrite(motor[0], LOW);
    //digitalWrite(motor[1], LOW);
    digitalWrite(motor[0], LOW);
    analogWrite(motor[1], 0);
  }
}

void setup()
{
  /* initialization pins */
  //  pinMode (PIN_MOTOR_RIGHT_UP, OUTPUT);
  //  pinMode (PIN_MOTOR_RIGHT_DN, OUTPUT);
  //  pinMode (PIN_MOTOR_LEFT_UP, OUTPUT);
  //  pinMode (PIN_MOTOR_LEFT_DN, OUTPUT);
  pinMode (PIN_MOTOR_RIGHT_REVERSE, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_REVERSE, OUTPUT);
  pinMode (PIN_MOTOR_RIGHT_SPEED, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_SPEED, OUTPUT);
  pinMode (PIN_LED, OUTPUT);

  /* initialization module RemoteXY */
  RemoteXY_Init ();

}

void loop()
{
  /* event handler module RemoteXY */
  RemoteXY_Handler ();

  /* manage LED pin */
  digitalWrite (PIN_LED, (RemoteXY.switch_1 == 0) ? LOW : HIGH);

  /* manage the right motor */
  Wheel (RightMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x);
  /* manage the left motor */
  Wheel (LeftMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x);
}
