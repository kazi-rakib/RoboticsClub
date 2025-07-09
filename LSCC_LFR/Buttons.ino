byte button(byte button_no) {
  uint32_t t = 0;
  if (!digitalRead(button_no)) {  //if button is pressed
    delay(50);                        //debounce delay;
    while (!digitalRead(button_no)) {
      delay(50);
      t += 50;
      if (t > 500) digitalWrite(led, 1);
    }
    digitalWrite(led, 0);
    if (t > 0) return 1;    //long press
  }
  return 0;
}