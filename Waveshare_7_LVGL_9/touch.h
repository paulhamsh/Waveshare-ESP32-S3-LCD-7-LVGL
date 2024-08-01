/*******************************************************************************
 * Touch libraries:
  * GT911: https://github.com/TAMCTec/gt911-arduino.git
 ******************************************************************************/

/* uncomment for GT911 */
#define TOUCH_GT911
#define TOUCH_GT911_SCL 9
#define TOUCH_GT911_SDA 8
#define TOUCH_GT911_INT 4
#define TOUCH_GT911_RST -1
#define TOUCH_GT911_ROTATION ROTATION_NORMAL // ROTATION_LEFT
#define TOUCH_MAP_X1 800
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 480
#define TOUCH_MAP_Y2 0

int touch_last_x = 0, touch_last_y = 0;

#include <Wire.h>
#include <TAMC_GT911.h>
TAMC_GT911 ts = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

void touch_init()
{

  // Find the GT911 at either 0x5D or 0x14 - given we aren't using the IO expander to reset the GT911
  
  // Comment this out if using the IO Expander code
  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);

  byte error;
  bool done;
  done = false;
  int gt_addr[]{GT911_ADDR1, GT911_ADDR2};
  int addr;

  for (int i = 0; (i < 2) && !done; i++) {
    int addr = gt_addr[i];  
    Wire.beginTransmission(addr);
    error =  Wire.endTransmission();
    if (error == 0) {
      Serial.print("GT911 found at 0x");
      Serial.println(addr, HEX);
      ts.begin(addr);
      done = true;
    }
  }

  if (!done) {
    Serial.println("NO GT911 FOUND!");
  }

  //ts.begin();
  ts.setRotation(TOUCH_GT911_ROTATION);
}

bool touch_touched()
{
  ts.read();
  if (ts.isTouched) {
#if defined(TOUCH_SWAP_XY)
    touch_last_x = map(ts.points[0].y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y = map(ts.points[0].x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#else
    touch_last_x = map(ts.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y = map(ts.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#endif
    return true;
  }
  else {
    return false;
  }
}
