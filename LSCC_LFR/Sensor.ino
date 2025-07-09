void reading() {
  sensor = 0;
  sum = 0;
  for (byte i = 0; i < 6; i++) {
    (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    (s[i] > mid[i]) ? s[i] = 1 ^ i_mode : s[i] = 0 ^ i_mode;
    sensor += s[i] * base[i];
    sum += s[i];
  }
}

//pid sensor reading
void PID_reading() {
  sensor = 0;
  sum = 0;
  for (byte i = 0; i < 6; i++) {
    (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    (s[i] > mid[i]) ? s[i] = 1 ^ i_mode : s[i] = 0 ^ i_mode;  //this line converts analog value into digital
    sensor += s[i] * position[i];
    sum += s[i];
  }
  if (sum) avg = sensor / sum;  //average value
}

void analog_value() {
  while (1) {
    for (int i = 0; i < 6; i++)
      (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
    u8g.setFont(u8g_font_7x14B);  // Set the font
    u8g.firstPage();
    do {
      for (byte i = 0; i < 6; i++) {
        if (i == 2) u8g.setPrintPos(5, 42);
        else if (i == 3) u8g.setPrintPos(5, 57);
        else if (i == 1) u8g.setPrintPos(50, 42);
        else if (i == 4) u8g.setPrintPos(50, 57);
        else if (i == 0) u8g.setPrintPos(95, 42);
        else if (i == 5) u8g.setPrintPos(95, 57);
        u8g.print(s[i]);
      }
    } while (u8g.nextPage());
    while (button(scroll) == 1) return;
  }
}

void digital_value() {
  while (1) {
    for (int i = 0; i < 6; i++) {
      if (i < 4) s[i] = analogRead(i);
      else s[i] = analogRead(i + 2);
      if (s[i] > mid[i]) s[i] = s[i] = 1 ^ i_mode;
      else s[i] = s[i] = 0 ^ i_mode;;
    }
    u8g.setFont(u8g_font_7x14B);
    u8g.firstPage();
    do {
      for (byte i = 0; i < 6; i++) {
        if (i == 5) u8g.setPrintPos(10, 50);
        else if (i == 4) u8g.setPrintPos(30, 50);
        else if (i == 3) u8g.setPrintPos(50, 50);
        else if (i == 2) u8g.setPrintPos(70, 50);
        else if (i == 1) u8g.setPrintPos(90, 50);
        else if (i == 0) u8g.setPrintPos(110, 50);
        u8g.print(s[i]);
      }
    } while (u8g.nextPage());
    while (button(scroll) == 1) return;
  }
}

void recording() {
  for (byte i = 0;; i++) {
    EEPROM.write(i + 30, path[i]);
    delay(10);
    if (path[i] == 5) return;
  }
}

void calibration() {
  u8g.setFont(u8g_font_7x14B);
  u8g.firstPage();
  do {
    u8g.drawStr(5, 35, "Started...");
  } while (u8g.nextPage());
  //Started
  while (1) {
    delay(500);
    for (int i = 0; i < 6; i++) {
      maximum[i] = 0;
      minimum[i] = 1023;
    }
    motor(250, 250);
    for (int i = 0; i < 500; i++) {
      for (int i = 0; i < 6; i++) {
        (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
        maximum[i] = max(maximum[i], s[i]);
        minimum[i] = min(minimum[i], s[i]);
      }
    }
    motor(-250, -250);
    for (int i = 0; i < 500; i++) {
      for (int i = 0; i < 6; i++) {
        (i < 4) ? s[i] = analogRead(i) : s[i] = analogRead(i + 2);
        maximum[i] = max(maximum[i], s[i]);
        minimum[i] = min(minimum[i], s[i]);
      }
    }
    motor(0, 0);
    for (int i = 0; i < 6; i++) {
      mid[i] = (maximum[i] + minimum[i]) / 2;
      EEPROM.write(i, mid[i] / 4);
      delay(10);
      EEPROM.write(i + 6, maximum[i] / 4);
      delay(10);
      EEPROM.write(i + 12, minimum[i] / 4);
      delay(10);
    }
    while (1) show_calibration();
  }
}

void show_calibration() {
  int m;
  int max;
  int min;
  while (1) {
    for (int i = 0; i < 6; i++) {
      m = mid[i] = EEPROM.read(i) * 4;
      max = maximum[i] = EEPROM.read(i + 6) * 4;
      min = minimum[i] = EEPROM.read(i + 12) * 4;
    }
    // Set the font
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(10, 12, "Done Calibration");
      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(15, 35, "MIN");
      u8g.drawStr(55, 35, "MID");
      u8g.drawStr(95, 35, "MAX");
      u8g.setFont(u8g_font_profont12);
      u8g.setPrintPos(15, 50);
      u8g.print(min);
      u8g.setPrintPos(55, 50);
      u8g.print(m);
      u8g.setPrintPos(95, 50);
      u8g.print(max);
    } while (u8g.nextPage());
    while (button(scroll) == 1) return menu();
  }
}
