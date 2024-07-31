# Waveshare-ESP32-S3-LCD-7-LVGL
Waveshare ESP32 S3 LCD 7 LVGL



## Useful information

https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-7


https://github.com/Westcott1/Waveshare-ESP32-S3-Touch-LCD-4.3-and-Arduino/blob/main/Examples/Arduino_GFX/GFX.ino

 

<p align="center">
  <img src="https://github.com/paulhamsh/Waveshare-ESP32-S3-LCD-7-LVGL/blob/main/waveshare-7.jpg" width="400" title="Waveshare ESP32 S3 LCD 7">
</p>

## Example code with Lovyan GFX (from  @Wesctott1)

In ```LovyanGFX``` folder.       

Code adapted from @Wesctott1 (there was no license so hopefully ok to edit and republish)    

https://github.com/Westcott1/Waveshare-ESP32-S3-Touch-LCD-4.3-and-Arduino/tree/main    
    
  
## Build LVGL demos with v9.1.0 and GFX Library for Arduino

In ```Waveshare_7_LVGL_9``` folder     

Board manager: ESP32 S3 Dev Module   
esp32 version 2.0.16   
Arduino IDE:   2.3.2   

Install Arduino libraries:
```
  lvgl                                            version 9.1.0
  GFX Library for Arduino by Moon On Our Nation   version 1.4.7
  TAMC-GT911                                      version 1.0.2
```

For Arduino IDE select:
```
Flash Size: 8MB(64Mb)
PSRAM: "OPI PSRAM"
```

Download the code in ```Waveshare_7_LVGL_9``` folder    

Copy ```Arduino\libraries\lvgl\lv_conf_template.h``` to ```src\lv_conf.h```   
Copy folders ```Arduino\libraries\lvgl\demos``` and ```Arduino\libraries\lvgl\examples```  to ```Arduino\libraries\lvgl\src```     

Edit ```lv_conf.h```    
```
#if 1 /*Set it to "1" to enable content*/
#define LV_USE_DEMO_WIDGETS 1
#define LV_FONT_MONTSERRAT_24 1
```

Compile and run.    
