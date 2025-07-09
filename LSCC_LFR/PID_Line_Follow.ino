//PID_FOLLOW function
void PID_FOLLOW() {
  while (1) {
    PID_reading();
    if (sum == 0) {
      delay(pid_node);
      if (flag != 's') {
        (flag == 'r') ? motor(tsp, -tsp) : motor(-tsp, tsp);
        while (!s[2] && !s[3]) reading();
        (flag == 'r') ? motor(-tsp, tsp) : motor(tsp, -tsp);
        delay(turn_brake);  //turn brake
      }
    }

    PID_reading();
    pid_error = 3.5 - avg;
    PID = pid_error * kp + kd * (pid_error - last_error);
    last_error = pid_error;

    rmotor = rbase - PID;
    lmotor = lbase + PID;
    motor(lmotor, rmotor);

    if (s[0] == 1 && s[5] == 0) flag = 'r';
    if (s[0] == 0 && s[5] == 1) flag = 'l';

    else if (sum == 6) {
      delay(50);
      PID_reading();
      if (sum == 6) {
        brake();
        motor(0, 0);
        while (sum == 6) PID_reading();
      } else if (sum == 0) flag = 'r';
    } else if ((s[5] == 1 && s[0] == 1) && sum < 6) {
      if (s[5] && s[0]) {
        uint32_t timer = millis();
        while ((s[5] || s[0]) && sum < 6) {
          reading();
          if (millis() - timer > i_timer) {
            i_mode = !i_mode;
            digitalWrite(led, i_mode);
            PID_FOLLOW();
          }
          flag = 'r';
        }
      }
    }
  }
}