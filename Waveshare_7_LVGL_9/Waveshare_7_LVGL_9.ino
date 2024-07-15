#include <lvgl.h>
#include <demos/lv_demos.h>
#include <Arduino_GFX_Library.h>


#define GFX_DEV_DEVICE WAVESHARE_ESP32_S3_TFT_7
#define GFX_BL (-1)



Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
     5 /* DE */,3 /* VSYNC */, 46 /* HSYNC */, 7 /* PCLK */,
     1 /* R0 */, 2 /* R1 */, 42 /* R2 */, 41 /* R3 */, 40 /* R4 */,     
     39 /* G0 */, 0 /* G1 */, 45 /* G2 */, 48 /* G3 */, 47 /* G4 */, 21 /* G5 */,
     14 /* B0 */, 38 /* B1 */, 18 /* B2 */, 17 /* B3 */, 10 /* B4 */,
     0 /* hsync_polarity */, 8 /* hsync_front_porch */, 4 /* hsync_pulse_width */, 8 /* hsync_back_porch */,
     0 /* vsync_polarity */, 8 /* vsync_front_porch */, 4 /* vsync_pulse_width */, 8 /* vsync_back_porch */,
     1 /* pclk_active_neg */, 16000000 /* prefer_speed */);
 
 Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
     800 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */);

/*******************************************************************************
 * Please config the touch panel in touch.h
 ******************************************************************************/
#include "touch.h"

static uint32_t my_tick_function(void) {
  return millis();
}

static const uint32_t screenWidth = 800;
static const uint32_t screenHeight = 480;
//int buf_size_in_bytes;
static const int buf_size_in_bytes = screenWidth * screenHeight * sizeof(lv_color_t) / 10;
static lv_color_t *disp_draw_buf, *disp_draw_buf2;
// Use below if not dynamically allocating memory
//static uint16_t disp_draw_buf[buf_size_in_bytes / sizeof(lv_color_t)];

// Display flushing 
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
  lv_disp_flush_ready(disp);
}



void my_touchpad_read(lv_indev_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_touched()) {
    data->state = LV_INDEV_STATE_PR;

    //Set the coordinates
    data->point.x = touch_last_x;
    data->point.y = touch_last_y;
  }
  else 
    data->state = LV_INDEV_STATE_REL;
}

lv_display_t *disp;
lv_indev_t   *indev;

void setup()
{
  Serial.begin(115200);
  Serial.println("LVGL Widgets Demo");

  gfx->begin();
  gfx->fillScreen(RED);


#ifdef GFX_BL
  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);
#endif

  touch_init();
  lv_init();

#ifdef ESP32
  Serial.println("ESP32 capability draw buffer malloc()");
  disp_draw_buf = (lv_color_t *) heap_caps_malloc(buf_size_in_bytes, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  disp_draw_buf2 = (lv_color_t *) heap_caps_malloc(buf_size_in_bytes, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
  Serial.println("Normal draw buffer malloc()");
  disp_draw_buf = (lv_color_t *) malloc(buf_size_in_bytes);
  disp_draw_buf2 = (lv_color_t *) malloc(buf_size_in_bytes);
#endif

  if (disp_draw_buf == nullptr)
  {
    Serial.println("LVGL disp_draw_buf allocate failed!");
    while (1);
  }

  lv_tick_set_cb(my_tick_function);

  disp = lv_display_create(screenWidth, screenHeight);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, disp_draw_buf, disp_draw_buf2, buf_size_in_bytes, LV_DISPLAY_RENDER_MODE_PARTIAL);


  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, my_touchpad_read);

  lv_demo_widgets();


  Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
