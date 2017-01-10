#include <Button.h>
#include <Wire.h>
#include <SparkFunDS1307RTC.h>

//objects
Button alarmButton(A5);

//pins
int speakerPin = A0;

//variables
bool alarm = false;
int toneTime;
String alarmTime;
String timeString;

//lcd variables
int digit1 = 5; //PWM Display pin 1
int digit2 = 6; //PWM Display pin 2
int digit3 = 9; //PWM Display pin 6
int digit4 = 10; //PWM Display pin 8

int segA = 2; //Display pin 14
int segB = 3; //Display pin 16
int segC = 4; //Display pin 13
int segD = 7; //Display pin 3
int segE = 8; //Display pin 5
int segF = 11; //Display pin 11
int segG = 12; //Display pin 15

void setup() {
  Serial.begin(9600);
  alarmSetup();
  displaySetup();
  alarmButton.begin();

  rtc.begin();
  //rtc.autoTime();
  //rtc.setTime(30,16,13,1,8,1,17);
}

void loop() {
  static int8_t lastSecond = -1;

  rtc.update();
  displayNumber(clockTime(0).toInt());
  alarmSleep();

  if (rtc.second() != lastSecond)
  {
    if (alarmTime == clockTime(1)) {
      alarm = true;
    }
    
    if (alarm) {
      alarmSound2();
    }

    //serialTime();
    lastSecond = rtc.second();
  }
}

String clockTime(bool seconds) {
  timeString = "";

  if (rtc.hour() < 10)
    timeString = timeString + "0";
  timeString = timeString + String(rtc.hour());
  if (rtc.minute() < 10)
    timeString = timeString + "0";
  timeString = timeString + String(rtc.minute());
  if (seconds) {
    if (rtc.second() < 10)
      timeString = timeString + "0";
    timeString = timeString + String(rtc.second());
  }

  return timeString;
}

