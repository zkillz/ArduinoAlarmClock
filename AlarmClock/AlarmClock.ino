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

//pins
int speakerPin = A0;

//variables
bool alarm = false;
int toneTime;
int buttonTime;
int alarmMode = 0;
int alarmHour = 7;
int alarmMinute = 0;
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
  pinMode(LED_BUILTIN, OUTPUT);

  rtc.begin();
  //rtc.autoTime();
  //rtc.setTime(30,16,13,1,8,1,17);
}

void loop() {
  static int8_t lastSecond = -1;

  rtc.update();
  digitalWrite(LED_BUILTIN, LOW);
  displayNumber(clockTime(0).toInt());
  alarmFunction();

  if (rtc.second() != lastSecond)
  {
    if (alarmTime() == clockTime(1)) {
      alarm = true;
    }

    if (alarm) {
      alarmSound();
    }

    //serialTime();
    lastSecond = rtc.second();
  }

  while (alarmMode > 0) {
    alarmConfig();
    displayNumber(alarmTime().toInt());
    //digitalWrite(LED_BUILTIN, HIGH);
    displayPoint(alarmMode + 1);
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

String alarmTime() {
  String timeString = "";

  if (alarmHour < 10)
    timeString = timeString + "0";
  timeString = timeString + alarmHour;
  if (alarmMinute < 10)
    timeString = timeString + "0";
  timeString = timeString + alarmMinute;
  if (alarmSecond < 10)
    timeString = timeString + "0";
  timeString = timeString + alarmSecond;

  return timeString;
}

