void serialTime()
{
  Serial.print(String(rtc.hour()) + ":");
  if (rtc.minute() < 10)
    Serial.print('0');
  Serial.print(String(rtc.minute()) + ":");
  if (rtc.second() < 10)
    Serial.print('0');
  Serial.print(String(rtc.second()));

  Serial.print(" | ");

  Serial.print(rtc.dayStr()); // Print day string
  //Serial.print(rtc.dayC()); // Print day character
  //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)

  Serial.print(" - ");

  Serial.println(String(rtc.month()) + "/" +   // Print month
                 String(rtc.date()) + "/" +  // Print date
                 String(rtc.year()));        // Print year

}

void serialDebug() {
  Serial.print("alarm state: ");
  Serial.print(alarm, DEC);
  Serial.print(" | ");
  Serial.print("clock mode: ");
  Serial.print(alarmMode, DEC);
  Serial.print(" | ");
  Serial.print("Time : ");
  Serial.print(clockTime(1));
  Serial.print(" | ");
  Serial.print("Alarm Time: ");
  Serial.print(alarmTime(1));
  Serial.print(" | ");
  Serial.print("Snooze Time: ");
  Serial.print(snoozeTime);
  Serial.println("");
  
}

