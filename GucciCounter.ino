#include <Wire.h>
#include <SPI.h>
#include <TinyScreen.h>
#include "BMA250.h"
#include <cmath>

//Library must be passed the board type
//TinyScreenPlus for TinyScreen+
TinyScreen display = TinyScreen(TinyScreenPlus);
int ctr = 0;
BMA250 accel_sensor;
int16_t x, y, z;
float max_xg = 0;
float max_yg = 0;
float max_zg = 0;
bool increment = true;
const int BIG_MAG = 30;
const int LITTLE_MAG = 20;
const float Z_AXIS_GFORCE_THRESHOLD = 0.75;
const float X_AXIS_GFORCE_THRESHOLD = 0.75;
const float Y_AXIS_GFORCE_THRESHOLD = 0.75;
const int COUNT_DELAY = 250;  

// Define the update interval (in milliseconds)
#define UPDATE_INTERVAL 16  // 500 ms = 0.5 seconds

void setup(void) {  
  display.begin();
  // Sets main current level, valid levels are 0-15
  display.setBrightness(10);
  flipDisplay(true);
  Wire.begin();
  // Set up the BMA250 acccelerometer sensor
  accel_sensor.begin(BMA250_range_16g, BMA250_update_time_16ms); 
}

void loop() {  
  // If the BMA250 is not found, nor connected correctly, these values will be produced
  // by the sensor 
  if (x == -1 && y == -1 && z == -1) {
    // Print error message to Serial Monitor
    // Should probably error some how, some way....        
  }
  else { // if we have correct sensor readings:     
    writeAccel();
  }
  buttonLoop();
  delay(UPDATE_INTERVAL);  
}

void flipDisplay(bool flipFlag)
{
  display.setFlip(flipFlag);
}

void writeAccel()
{  
  if(!increment && ctr == 0)
  {
    writeGameOver();
    return;
  }

  display.clearScreen();
  display.drawRect(0, 0, 96, 64, TSRectangleNoFill, 255, 0, 0);

  // Fetch accelerometer data and convert as needed.
  accel_sensor.read(); 
  float scaleFactor = 32.0; 
  x = accel_sensor.X;
  y = accel_sensor.Y;
  z = accel_sensor.Z;
  // Optionally, convert to m/s²  
  float x_g = (x / scaleFactor);
  float y_g = (y / scaleFactor);
  float z_g = (z / scaleFactor);
  float x_ms2 = (x / scaleFactor)*9.81;
  float y_ms2 = (y / scaleFactor)*9.81;
  float z_ms2 = (z / scaleFactor)*9.81;  

  // Counter Logic
  // if the current z accel reading is +/- 2g increment counter
  if((fabs(z_g) > Z_AXIS_GFORCE_THRESHOLD) && (fabs(x_g) > X_AXIS_GFORCE_THRESHOLD) && (fabs(y_g) < Y_AXIS_GFORCE_THRESHOLD))
  {
    if(increment)
    {
      ctr++;
    }
    else
    {
      ctr--;
    }    
    delay(COUNT_DELAY); // I hope this is enough to capture the full round cycle but prevents double round counts
  }

  //==========================================================
  // Used for debugging purposes.
  if((accel_sensor.X/scaleFactor) > max_xg)
  {
    max_xg = accel_sensor.X/scaleFactor;
  }
  if((accel_sensor.Y/scaleFactor) > max_yg)
  {
    max_yg = accel_sensor.Y/scaleFactor;
  }
  if((accel_sensor.Z/scaleFactor) > max_zg)
  {
    max_zg = accel_sensor.Z/scaleFactor;
  }
  //==========================================================

  displayData();

  // COMMENT OUT IF NOT DEBUGGING
  displayDebug();

}

void displayData(){
  display.setFont(liberationSans_22ptFontInfo);  
  char txtCount[10];
  itoa(ctr, txtCount, 10);  
  int16_t x = (48 - (display.getPrintWidth(txtCount)/2));
  int16_t y = (32 - (display.getFontHeight()/2));
  display.setCursor(x, y);
  display.fontColor(TS_8b_Red,TS_8b_Black);
  display.print(txtCount); 
}

void displayDebug(){
    //==========================================================
  // Used for debugging purposes.
  display.setFont(liberationSansNarrow_8ptFontInfo);
  display.fontColor(TS_8b_Red,TS_8b_Black);
  display.setCursor(65,5);
  display.print("X" + String(max_xg));
  display.setCursor(65,15);
  display.print("Y" + String(max_yg));
  display.setCursor(5,45);
  display.print("Z(m): " + String(max_zg));
 //==========================================================
}

void buttonLoop(){
  // 30 Round mag, decrement
  if(display.getButtons((TSButtonUpperLeft)))
  {
    ctr = BIG_MAG;
    increment = false;
  }

// 20 Round mag, decrement
  if(display.getButtons((TSButtonUpperRight)))
  {
    ctr = LITTLE_MAG;
    increment = false;
  }

  // Simple counter, increment
  if(display.getButtons((TSButtonLowerLeft)))
  {
    ctr = 0;
    increment = true;
  }

  // reset max z axis g
  if (display.getButtons(TSButtonLowerRight))
  { 
    max_xg = 0;
    max_yg = 0;
    max_zg = 0;
    ctr = 0;
    increment = true;
  }
}

void writeGameOver(){  
  char sInsert[7] = "Insert";
  char sCoin[7] = "Coin";

  display.drawRect(0, 0, 96, 64, TSRectangleFilled, 255, 0, 0);
  //setFont sets a font info header from font.h
  //information for generating new fonts is included in font.h
  display.setFont(liberationSans_16ptFontInfo);  
  display.fontColor(TS_8b_Red,TS_8b_Black);

  int insWidth=display.getPrintWidth(sInsert);  
  int coinWidth=display.getPrintWidth(sCoin);
  
  //fontColor(text color, background color);//sets text and background color
  display.fontColor(TS_8b_Black, TS_8b_Red);
  display.setCursor(38-(insWidth/4),10);
  display.print(sInsert);
  display.setCursor(38-(coinWidth/4),30);
  display.print(sCoin);
  delay(1000);
}
