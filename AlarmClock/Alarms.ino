void alarmSleep() {
  if (alarmButton.pressed()) {
    alarm = false;
  }
}

void alarmFunction() {
  if (alarmButton.pressed()) {
    buttonTime = millis();
  }

  if (alarmButton.released() && millis() - buttonTime < 300) {
    alarm = false;
  }

  if (alarmButton.released() && millis() - buttonTime < 3000) {
    alarmMode = alarmMode++;
  }
}

void alarmConfig() {
  if (alarmButton.pressed()) {
    buttonTime = millis();
  }

  if (alarmButton.released() && millis() - buttonTime < 300) {
    switch (alarmMode) {
      case 1:
        alarmHour = alarmHour++;
        if (alarmHour > 23)
          alarmHour = 0;
        break;
      case 2:
        alarmMinute = alarmMinute++;
        if (alarmMinute > 59)
          alarmMinute = 0;
        break;
    }
  }

  if (alarmButton.released() && millis() - buttonTime < 3000) {
    alarmMode = alarmMode++;
    if (alarmMode > 2)
      alarmMode = 0;
  }
}

void alarmSound() {
  tone(speakerPin, 131, 300);
}

