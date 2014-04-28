
/*
 * STEM Du Library
 *
 * Blink
 *
 * This example code is in the public domain.
 *
 */

/*** Setup for using Library ***/
//#define TYPE_I
//#define TYPE_II
#define TYPE_III
//#define TYPE_III_R
//#define USE_PHREF
#include <STEMDu.h>
/*** end of setup for using Library ***/

/* Initialize STEM Du board */
STEMDu robot = STEMDu();

void setup(){
  
}

void loop(){
  int delayTime = map(robot.readSlider(),0,1023,20,1000);
  robot.led(255);
  delay(delayTime);
  robot.led(0);
  delay(delayTime);
}
