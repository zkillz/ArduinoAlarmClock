void alarmSleep() {
  if (alarmButton.pressed()) {
    buttonTime = millis();
    if (alarm)
      snoozeTime = snoozeTime + 500;
    alarm = !alarm;
  }

  if (alarmButton.released() && buttonTime + 3000 <= millis()) {
    alarm = false;
    snoozeTime = 0;
  }
}

void switchMode() {
  if (modeButton.pressed()) {
    alarmMode = alarmMode + 1;
  }
}

void alarmSet() {
  if (valueButton.pressed()) {
    switch (alarmMode) {
      case 1:
        alarmHour = alarmHour + 1;
        if (alarmHour > 23)
          alarmHour = 0;
        break;
      case 2:
        alarmMinute = alarmMinute + 1;
        if (alarmMinute > 59)
          alarmMinute = 0;
        break;
    }
  }
}


void alarmSound() {
  tone(speakerPin, 115, 300);
}

