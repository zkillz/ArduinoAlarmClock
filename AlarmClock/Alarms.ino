void alarmSetup() {
  alarmTime = "070000";
}

void buttonSetup() {
  alarmButton.begin();
}

void alarmSleep() {
  if (alarmButton.pressed()) {
    alarm = false;
  }
}

void alarmSound() {
  toneTime = millis();
  
  while (millis() - toneTime < 300) {
    analogWrite(speakerPin, 125);
  }
  analogWrite(speakerPin, 0);
}

void alarmSound2() {
  tone(speakerPin,131,300);
}

