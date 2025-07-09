void normal_line() {
  while (1) {
    reading();
    if (sum == 0) {  //All Sensor in white
      if (flag != 's') {
        brake();
        (flag == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);  //Solved the turning problem
        delay(turn_brake);
        flag = 's';
        cross = 's';
        pos = 0;
      }
      
      else if (pos > -3 && pos < 3) {
        m2 = millis();
        while (sum == 0) {
          reading();
          if (millis() - m2 > u_turn_timer) {
            brake();
            (rule == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
            while (s[2] == 0 && s[3] == 0) reading();
            (rule == 'r') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);  //Solved the turning problem
            delay(turn_brake);
            delay(50);
            pos = 0;
            break;
          }
        }
      }
    }

    else if (sum == 1 || sum == 2) {  // straight line er jonne
      if (cross != 's') {
        brake();
        (cross == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
        while (s[2] + s[3] > 0) delay(5), reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (cross == 'r') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);  //Solved the turning problem
        delay(turn_brake);
        cross = 's';
        flag = 's';
        pos = 0;
      }

      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-7 * spl, 7 * spr) : motor(7 * spl, -7 * spr);
          delay(abs(pos) * 6);
        }
        motor(10 * spl, 10 * spr);
      }

      //right rule portion,curve
      else if (sensor == 0b000100)
        motor(10 * spl, 9 * spr);
      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1;
        motor(10 * spl, 6 * spr);
      } else if (sensor == 0b000010) {
        if (pos < 2) pos = 2;
        motor(10 * spl, 3 * spr);
      } else if (sensor == 0b000011) {
        if (pos < 3) pos = 3;
        motor(10 * spl, 0 * spr);
      } else if (sensor == 0b000001) {
        if (pos < 4) pos = 4;
        motor(10 * spl, -3 * spr);
      }
      //left rule portion,curve
      else if (sensor == 0b001000)
        motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1;
        motor(6 * spl, 10 * spr);
      } else if (sensor == 0b010000) {
        if (pos > -2) pos = -2;
        motor(3 * spl, 10 * spr);
      } else if (sensor == 0b110000) {
        if (pos > -3) pos = -3;
        motor(0 * spl, 10 * spr);
      } else if (sensor == 0b100000) {
        if (pos > -4) pos = -4;
        motor(-3 * spl, 10 * spr);
      }
    }

    else if (sum == 3 || sum == 4 || sum == 5) {               //Turns
      if (s[5] == 1 && s[0] == 0 && s[2] + s[3] + s[4] > 0) {  //Left turns
        flag = 'l';
        while (s[5] == 1 && s[0] == 0) reading();
        if (s[0] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) {
            flag = 's';
            if (rule == 'l') cross = 'l';
          }
        }
      } else if (s[0] == 1 && s[5] == 0 && s[1] + s[2] + s[3] > 0) {  //right turns
        flag = 'r';
        while (s[5] == 0 && s[0] == 1) reading();
        if (s[5] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) {
            flag = 's';
            if (rule == 'r') cross = 'r';
          }
        }
      } else if ((s[5] == 1 && s[0] == 1) && sum < 6) {
        if (s[5] && s[0]) {
          uint32_t timer = millis();
          while ((s[5] || s[0]) && sum < 6) {
            reading();
            if (millis() - timer > i_timer) {
              i_mode = !i_mode;
              digitalWrite(led, i_mode);
              cross = 's';
              normal_line();
            }
            flag = rule;
          }
        }
      }
      m1 = millis();
    }

    else if (sum == 6) {  //Cross, T and End Section
      flag = rule;
      m2 = millis();
      while (s[5] == 1 || s[0] == 1) {
        reading();
        if (millis() - m2 > stop_timer) {
          motor(0, 0);
          while (sum == 6) reading();
        }
      }
      delay(node_delay);
      reading();
      if (sum != 0) cross = rule;  //instruction for cross section. when cross = 's'; then the robot will
      //go to forward in cross secton and make comment 139 number line when you're using cross = 's';
      //but when cross = rule; then robot will turn according to rule in cross section
      m1 = millis();
    }

    
    if (millis() - m1 > 1000) flag = 's';
  }
}