# Waveshare-ESP32-S3-LCD-7-LVGL
Waveshare ESP32 S3 LCD 7 LVGL



## Useful information

https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-7


https://github.com/Westcott1/Waveshare-ESP32-S3-Touch-LCD-4.3-and-Arduino/blob/main/Examples/Arduino_GFX/GFX.ino

 

<p align="center">
  <img src="https://github.com/paulhamsh/Waveshare-ESP32-S3-LCD-7-LVGL/blob/main/waveshare-7.jpg" width="400" title="Waveshare ESP32 S3 LCD 7">
</p>

## Common Arduino IDE setup

```
Board manager: ESP32 S3 Dev Module   
esp32 version 2.0.16   
Arduino IDE:   2.3.2   
```

For Arduino IDE select:
```
Flash Size: 8MB(64Mb)
PSRAM: "OPI PSRAM"
```

## Example code with Lovyan GFX (from  @Wesctott1)

In ```LovyanGFX``` folder.       

Code adapted from @Wesctott1 (there was no license so hopefully ok to edit and republish)    

https://github.com/Westcott1/Waveshare-ESP32-S3-Touch-LCD-4.3-and-Arduino/tree/main    

```
  LovyanGFX                version 1.1.16
```

## Build LVGL demos with v9.1.0 and Lovyan GFX

In ```Waveshare_7_LVGL_9_LGFX``` folder     

Install Arduino libraries:
```
  lvgl                                            version 9.1.0
  LovyanGFX                                       version 1.1.16
```

Download the code in ```Waveshare_7_LVGL_9_LGFX``` folder    

Copy ```Arduino\libraries\lvgl\lv_conf_template.h``` to ```src\lv_conf.h```   
Copy folders ```Arduino\libraries\lvgl\demos``` and ```Arduino\libraries\lvgl\examples```  to ```Arduino\libraries\lvgl\src```     

Edit ```lv_conf.h```    
```
#if 1 /*Set it to "1" to enable content*/
#define LV_USE_DEMO_WIDGETS 1
#define LV_FONT_MONTSERRAT_24 1
```

Compile and run.    
  
## Build LVGL demos with v9.1.0 and GFX Library for Arduino

In ```Waveshare_7_LVGL_9``` folder     

Install Arduino libraries:
```
  lvgl                                            version 9.1.0
  GFX Library for Arduino by Moon On Our Nation   version 1.4.7
  TAMC-GT911                                      version 1.0.2
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

## Confusion over pin numbers in Waveshare documentation   

Pin  | Waveshare      | Arduino_ESP32RGB | LoyanGFX 
-----|----------------|------------------|-------------
  0  |     G3         |    G1            |    G1   
  1  |     R3         |    R0            |    R0   
  2  |     R4         |    R1            |    R1      
  3  |     VSYNC      |    VSYNC         |    VSYNC       
  5  |     DE         |    DE            |    HENABLE      
  7  |     PCLK       |    PCLK          |    PCLK       
 10  |     B7         |    B4            |    B4       
 14  |     B3         |    B0            |    B0       
 17  |     B6         |    B3            |    B3     
 18  |     B5         |    B2            |    B2    
 21  |     G7         |    G5            |    G5       
 38  |     B4         |    B1            |    B1   
 39  |     G2         |    G0            |    G0
 40  |     R7         |    R4            |    R4       
 41  |     R6         |    R3            |    R3      
 42  |     R5         |    R2            |    R2       
 45  |     G4         |    G2            |    G2       
 46  |     HSYNC      |    HSYNC         |    HSYNC     
 47  |     G6         |    G4            |    G4    
 48  |     G5         |    G3            |    G3       
      
