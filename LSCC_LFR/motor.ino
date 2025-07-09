//motor function
void motor(int a, int b) {
  if (a > 0) {
    digitalWrite(lmf, 1);
    digitalWrite(lmb, 0);
  } else {
    a = -(a);
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 1);
  }
  if (b > 0) {
    digitalWrite(rmf, 1);
    digitalWrite(rmb, 0);
  } else {
    b = -(b);
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 1);
  }

  if (a > 250) a = 250;
  if (b > 250) b = 250;

  analogWrite(lms, a);
  analogWrite(rms, b);
}

void motor_test() {
  while (1) {
    u8g.setFont(u8g_font_7x14B);  // Set the font
    u8g.firstPage();
    do {
      u8g.drawStr(5, 35, "Motor Testing...");
    } while (u8g.nextPage());
    motor(250, 250);
    digitalWrite(led, HIGH);
    delay(3000);
    motor(0, 0);
    digitalWrite(led, LOW);
    return;
  }
}

void brake() {
  motor(-250, -250);
  delay(brake_time);
  motor(0, 0);
  delay(100);
}
