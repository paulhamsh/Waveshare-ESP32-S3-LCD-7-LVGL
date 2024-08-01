#include <lvgl.h>
#include <demos/lv_demos.h>

#include <Arduino.h>


#include <ESP_IOExpander_Library.h>
#include "Wire.h"

ESP_IOExpander *expander;


// Extender Pin define
#define TP_RST 1
#define LCD_BL 2
#define LCD_RST 3
#define SD_CS 4
#define USB_SEL 5

// Extender pin mask define
#define TP_RST_MASK   1
#define LCD_BL_MASK   2
#define LCD_RST_MASK  4
#define SD_CS_MASK    8
#define USB_SEL_MASK 16

// I2C Pin define
#define I2C_MASTER_NUM      0
#define I2C_MASTER_SDA_IO   8
#define I2C_MASTER_SCL_IO   9

#define GPIO_INPUT_IO_4     4


#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

#define TFT_HOR_RES   800
#define TFT_VER_RES   480

#define TOUCH_SDA 8
#define TOUCH_SCL 9
#define TOUCH_INT 4
#define TOUCH_RST -1

class LGFX : public lgfx::LGFX_Device {
public:
  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_RGB _panel_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_GT911 _touch_instance;

  LGFX(void) {
    {
      auto cfg = _panel_instance.config();
      cfg.memory_width = TFT_HOR_RES;
      cfg.memory_height = TFT_VER_RES;
      cfg.panel_width = TFT_HOR_RES;
      cfg.panel_height = TFT_VER_RES;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      _panel_instance.config(cfg);
    }

    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;

      cfg.pin_d0 = 14;   // B0
      cfg.pin_d1 = 38;   // B1
      cfg.pin_d2 = 18;   // B2
      cfg.pin_d3 = 17;   // B3
      cfg.pin_d4 = 10;   // B4

      cfg.pin_d5 = 39;   // G0
      cfg.pin_d6 = 0;    // G1
      cfg.pin_d7 = 45;   // G2
      cfg.pin_d8 = 48;   // G3
      cfg.pin_d9 = 47;   // G4
      cfg.pin_d10 = 21;  // G5

      cfg.pin_d11 = 1;  // R0
      cfg.pin_d12 = 2;  // R1
      cfg.pin_d13 = 42;  // R2
      cfg.pin_d14 = 41;  // R3
      cfg.pin_d15 = 40;  // R4

      cfg.pin_henable = 5;
      cfg.pin_vsync = 3;
      cfg.pin_hsync = 46;
      cfg.pin_pclk = 7;
      cfg.freq_write = 14000000;

      cfg.hsync_polarity = 0;
      cfg.hsync_front_porch = 8;
      cfg.hsync_pulse_width = 4;
      cfg.hsync_back_porch = 8;

      cfg.vsync_polarity = 0;
      cfg.vsync_front_porch = 8;
      cfg.vsync_pulse_width = 4;
      cfg.vsync_back_porch = 8;

      cfg.pclk_active_neg = 1;
      cfg.de_idle_high = 0;
      cfg.pclk_idle_high = 0;

      _bus_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);

    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = TFT_HOR_RES-1;
      cfg.y_min = 0;
      cfg.y_max = TFT_VER_RES-1;
      cfg.pin_int = TOUCH_INT;
      cfg.pin_rst = TOUCH_RST;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;
      cfg.i2c_port = I2C_NUM_1;
      cfg.pin_sda = TOUCH_SDA;
      cfg.pin_scl = TOUCH_SCL;
      cfg.freq = 400000;
      cfg.i2c_addr = 0x14;
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }
    setPanel(&_panel_instance);
  }
};

LGFX gfx;

static uint32_t my_tick_function(void) {
  return millis();
}

static const uint32_t screenWidth = 800;
static const uint32_t screenHeight = 480;

static const int buf_size_in_bytes = screenWidth * screenHeight * sizeof(lv_color_t) / 10;
static lv_color_t *disp_draw_buf, *disp_draw_buf2;
// Use below if not dynamically allocating memory
//static uint16_t disp_draw_buf[buf_size_in_bytes / sizeof(lv_color_t)];

// Display flushing 
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  lv_draw_sw_rgb565_swap(px_map, w * h);
  gfx.pushImage(area->x1, area->y1, w, h, (uint16_t *)px_map);

  lv_disp_flush_ready(disp);
}

void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data )
{
  uint16_t touchX, touchY;

  data->state = LV_INDEV_STATE_RELEASED;

  if(gfx.getTouch(&touchX, &touchY))
  {
    data->state = LV_INDEV_STATE_PRESSED;
    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
  else
    data->state = LV_INDEV_STATE_RELEASED;
}


lv_display_t *disp;
lv_indev_t   *indev;

void setup()
{
  Serial.begin(115200);
  pinMode(GPIO_INPUT_IO_4, OUTPUT);

/*
  Serial.println("IO expander init...");
  Wire.begin(I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
  expander = new ESP_IOExpander_CH422G((i2c_port_t)I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000);
  expander->init();
  expander->begin();
  expander->multiPinMode(TP_RST_MASK | LCD_BL_MASK | LCD_RST_MASK | SD_CS_MASK | USB_SEL_MASK, OUTPUT);

  expander->digitalWrite(TP_RST, LOW);
  delay(100);
  digitalWrite(GPIO_INPUT_IO_4, LOW);
  delay(100);
  expander->digitalWrite(TP_RST, HIGH);
  delay(200);
*/

  gfx.begin();
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

  if (disp_draw_buf2 == nullptr)
  {
    Serial.println("LVGL disp_draw_buf2 allocate failed - carry on anyway we can live without it");
  }

  // set up LVGL
  lv_tick_set_cb(my_tick_function);

  disp = lv_display_create(screenWidth, screenHeight);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, disp_draw_buf, disp_draw_buf2, buf_size_in_bytes, LV_DISPLAY_RENDER_MODE_PARTIAL);

  indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, my_touchpad_read);

  lv_demo_widgets();

  // do my setup
  //lv_my_setup();

  Serial.println("Setup complete");
}

void loop()
{
  lv_timer_handler(); 
  delay(5);
}
