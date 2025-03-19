# Gucci Counter

## Parts to buy:
1. **TinyScreen+** (https://tinycircuits.com/products/tinyscreenplus)
2. **TinyAccelerometer** (https://tinycircuits.com/products/accelerometer-tinyshield)
3. **Battery** (https://tinycircuits.com/products/lithium-ion-polymer-battery-3-7v-290mah)
4. **M3 bolt** (35mm)
5. **M3 Locking Nylon Nut**  
6. **Tactical paper clip** To press the buttons on the screen

## Parts to 3D print:  

1. **Main housing** https://github.com/ProfessionalAmateur/GucciCounter/blob/master/TinyScreenMainHousingPicatinny.stl  
2. **Picatinny small arm:** https://github.com/ProfessionalAmateur/GucciCounter/blob/master/MainHousingArmPicatinny.stl  
3. **Back Cover:** https://github.com/ProfessionalAmateur/GucciCounter/blob/master/TinyScreenBackPlate.stl  
(Please rotate objects as needed with your slicer for best printing quality)  

Once printed I drill out the bolt holes because the original design wanted something smaller, but I think an M3 bolt is better/best for a picatinny rail.

**Code to download:**  
https://github.com/ProfessionalAmateur/GucciCounter



**Assembly:** The accelerometer clips right into the back of the TinyScreen+ as well as the battery.
Once assembled, connect the screen to your computer via a micro USB cable (this cable also charges the battery).
Insert the screen, accelerometer and battery into the 3d printed housing and affix the back cover.

Open up Arduino IDE and upload the code program downloaded in step 3. (You may need to research how to connect your arduino to your PC but it is really straight forward.)

After the battery is fully charged attached the unit to the picatinny rail if your desire.

## Button functions:

**Top Left:** Resets to 30 round magazine and will decrement with each round.  
**Top Right:** : Resets to 20 round magazine and will decrement with each round.  
**Bottom Left:** Resets to 0 and will increment with each round.  
**Bottom Right:** Resets to 0 and will increment with each round.  

## Constants/Variables
There are a couple of constant variables in the program you can feel free to change:  
  
**BIG_MAG:** I keep mine at 30 but if folks have 50 or 100 or 256 round magazine you will want to change this number.

**LITTLE_MAG:** Same as above if you have  10, 5 or 1 round magazine you will want to change this number.   

**Z-AXIS-GFORCE_THRESHOLD:** This value is a little tricky.  For my AR (which has almost no recoild because I built it myself and did it perfectly) a shot is just over 2g's but every gun is different, so if a shot is not registering I would lower this number.  If its registering too many, for some reason, raise it up.  This is where all the research and development dollars go into tuning.  

**X-AXIS-GFORCE_THRESHOLD & Y-AXIS-GFORCE_THRESHOLD:** These settings are to help prevent accidental 'round counts' when the firearm is placed down (On the stock or barrel) and registers an high G force across two or three directions.  All shots will come from the z-axis, but if you place your gun down or drop it in a corner it might register acceleration across all 3 axis'.  There is probably a better way to do this but alas, this is how I did it.
