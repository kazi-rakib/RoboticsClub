void menu() {
  int select_clicked = 0;
  int scroll_clicked = 0;
  int item_selected = 0;
  int item_sel_previous;
  int item_sel_next1, item_sel_next2;
  int current_screen = 0;

  while (1) {
    if (current_screen == 0) {
      if ((digitalRead(scroll) == 0) && (scroll_clicked == 0)) {
        item_selected = item_selected + 1;
        scroll_clicked = 1;
        if (item_selected >= NUM_ITEMS) {
          item_selected = 0;
        }
      }
      if ((digitalRead(scroll) == 1) && (scroll_clicked == 1)) scroll_clicked = 0;
    }
    if ((digitalRead(select) == 0) && (select_clicked == 0)) {
      select_clicked = 1;
      if (current_screen == 0) {
        current_screen = 1;
      } else {
        current_screen = 0;
      }
    }
    if ((digitalRead(select) == 1) && (select_clicked == 1)) select_clicked = 0;


    item_sel_previous = item_selected - 1;
    if (item_sel_previous < 0) {
      item_sel_previous = NUM_ITEMS - 1;
    }
    item_sel_next1 = item_selected + 1;
    if (item_sel_next1 >= NUM_ITEMS) {
      item_sel_next1 = 1;
    }
    item_sel_next2 = item_selected + 2;
    if (item_sel_next2 >= NUM_ITEMS) {
      item_sel_next2 = 0;
    }

    if (item_selected == 0 && select_clicked == 1) {
      current_screen = 0;
      normal_line();
    } else if (item_selected == 1 && select_clicked == 1) {
      current_screen = 0;
      PID_FOLLOW();
    } else if (item_selected == 2 && select_clicked == 1) {
      current_screen = 0;
      calibration();
    } else if (item_selected == 3 && select_clicked == 1) {
      current_screen = 0;
      analog_value();
    } else if (item_selected == 4 && select_clicked == 1) {
      current_screen = 0;
      digital_value();
    } else if (item_selected == 5 && select_clicked == 1) {
      current_screen = 0;
      motor_test();
    }

    u8g.firstPage();
    do {
      if (current_screen == 0) {
        u8g.drawBitmapP(0, 30, 128 / 8, 17, epd_bitmap_New_Project__1_);
        u8g.setFont(u8g_font_profont12);
        u8g.drawStr(14, 10, menu_items[item_sel_previous]);
        u8g.setFont(u8g_font_profont12);
        u8g.drawStr(14, 28, menu_items[item_sel_next1]);
        u8g.setFont(u8g_font_7x14B);
        u8g.drawStr(14, 43, menu_items[item_selected]);
        u8g.setFont(u8g_font_profont12);
        u8g.drawStr(14, 58, menu_items[item_sel_next2]);
        // u8g.drawBitmapP(128 - 8, 0, 8 / 8, 64, bitmap_scrollbar_background);
        // u8g.drawBox(125, 64 / NUM_ITEMS * item_selected, 3, 64 / NUM_ITEMS);
      } else if (current_screen == 1) {
      }
    } while (u8g.nextPage());
  }
}