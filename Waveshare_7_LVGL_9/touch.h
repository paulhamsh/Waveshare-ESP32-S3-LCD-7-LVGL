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

  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  ts.begin();
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
