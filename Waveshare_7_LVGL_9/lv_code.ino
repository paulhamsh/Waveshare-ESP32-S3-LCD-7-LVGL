// LVGL display elements and callbacks

static lv_obj_t *label1;
lv_obj_t *slider1;
lv_obj_t *btn1;

static void btn_event_cb(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *btn = (lv_obj_t *) lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    static uint8_t cnt = 0;
    cnt++;
    /*Get the first child of the button which is the label and change its text*/
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "Button: %d", cnt);
  }
}

static void slider_event_cb(lv_event_t *e)
{
  lv_obj_t *slider = (lv_obj_t *) lv_event_get_target(e);
  //lv_obj_t *label = lv_obj_get_child(slider, 0);
  lv_label_set_text_fmt(label1, "%"LV_PRId32, lv_slider_get_value(slider));
  lv_obj_align_to(label1, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

void lv_my_setup() {
  slider1 = lv_slider_create(lv_screen_active());
  lv_slider_set_value(slider1, 0, LV_ANIM_ON);
  lv_obj_set_pos(slider1, 40, 60);                            /*Set its position*/
  lv_obj_set_size(slider1, 200, 20);                          /*Set its size*/
  lv_obj_add_event_cb(slider1, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  
  label1 = lv_label_create(lv_screen_active());
  lv_label_set_text(label1, "0");
  lv_obj_align_to(label1, slider1, LV_ALIGN_OUT_TOP_MID, 0, -15);  


  lv_obj_t *label2 = lv_label_create(slider1);                 /*Add a label to the button*/
  lv_label_set_text(label2, "Slider");                         /*Set the labels text*/
  lv_obj_center(label2);

  btn1 = lv_button_create(lv_screen_active());                 /*Add a button the current screen*/
  lv_obj_set_pos(btn1, 40, 120);                               /*Set its position*/
  lv_obj_set_size(btn1, 100, 50);                              /*Set its size*/
  lv_obj_add_event_cb(btn1, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/

  lv_obj_t *label3 = lv_label_create(btn1);                    /*Add a label to the button*/
  lv_label_set_text(label3, "Button");                         /*Set the labels text*/
  lv_obj_center(label3);
}