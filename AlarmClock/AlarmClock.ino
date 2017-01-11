#include <Button.h>
#include <Wire.h>
#include <SparkFunDS1307RTC.h>

#define DISPLAY_BRIGHTNESS  100

#define DIGIT_ON            LOW
#define DIGIT_OFF           HIGH

#define SEGMENT_ON          HIGH
#define SEGMENT_OFF         LOW

//objects
Button alarmButton(A5);
Button modeButton(A4);
Button valueButton(A3);

//pins
int speakerPin = A0;

//variables
bool alarm = false;
unsigned long toneTime;
unsigned long buttonTime;
unsigned long snoozeTime;
int alarmMode = 0;
int alarmHour = 6;
int alarmMinute = 30;
int alarmSecond = 0;

//lcd variables
//pwm digits
int digit1 = 5;
int digit2 = 6;
int digit3 = 9;
int digit4 = 10;
//segments
int segA = 2;
int segB = 3;
int segC = 4;
int segD = 7;
int segE = 8;
int segF = 11;
int segG = 12;
int segPoint = 13;

void setup() {
  Serial.begin(9600);
  displaySetup();
  alarmButton.begin();
  modeButton.begin();
  valueButton.begin();

  rtc.begin();
  //rtc.autoTime();
  //rtc.setTime(00,35,18,3,10,1,17);
}

void loop() {
  static int8_t lastSecond = -1;

  rtc.update();
  displayNumber(clockTime(0).toInt());
  alarmSleep();
  switchMode();

  if (rtc.second() != lastSecond)
  {
    if (snoozeTime + alarmTime(1).toInt() == clockTime(1).toInt()) {
      alarm = true;
    }

    if (alarm) {
      alarmSound();
    }
    
    //serialTime();
    //serialDebug();
    lastSecond = rtc.second();
  }

  while (alarmMode > 0) {
    if (alarmMode > 2)
      alarmMode = 0;
    switchMode();
    alarmSet();
    displayNumber(alarmTime(0).toInt());
    switch (alarmMode) {
      case 1:
        displayPoint(1);
        break;
      case 2:
        displayPoint(3);
        break;
    }
  }
}

String clockTime(bool seconds) {
  String timeString = "";

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

String alarmTime(bool seconds) {
  String timeString = "";

  if (alarmHour < 10)
    timeString = timeString + "0";
  timeString = timeString + alarmHour;
  if (alarmMinute < 10)
    timeString = timeString + "0";
  timeString = timeString + alarmMinute;
  if (seconds) {
    if (alarmSecond < 10)
      timeString = timeString + "0";
    timeString = timeString + alarmSecond;
  }

  return timeString;
}

