#ifndef STEM_Du_h
#define STEM_Du_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define NANOBOARD_AG     990
#define CHIBIDUINO       991
#define JRTA1            999
#define RDC_102_NO_MARK 1020
#define RDC_102_R0      1021
#define RDC_102_R1      1022
#define RDC_102_R2      1023
#define RDC_102_R3      1024
#define RDC_103         1030
#define RDC_103_R1      1031
#define RDC_103_R2      1032
#define RDC_103_R3      1033
#define RDC_103_R4      1034

// STEM Du Controller RDC-103R4
#define STEMDU 1034

#define HAS_MOTOR12 1
#define HAS_MOTOR34 2
#define HAS_PICOBOARD_SENSOR 3
#if STEMDU <= RDC_102_R3
#define HAS_I2C_LCD 4
#define HAS_PHREF 5
#define HAS_TWL 6
#endif
#define HAS_SPI_LCD 7
//#define HAS_MPU6050  8
#define HAS_ONBBOARD_DISTANCE 9

#if defined(HAS_MPU6050)
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#endif

////////////////////////////////////////////////////////

#define MOTOR_STOP  0
#define MOTOR_BRAKE 1023

#if defined(HAS_ONBBOARD_DISTANCE)
#define BUILTIN_DISTANCE_BUFFER_SIZE 45     // use an odd number
#endif

////////////////////////////////////////////////////////

class STEMDu {
public:
  STEMDu();

  void init();
  
  //Motor
  void motor(int n, int speed);

  //Motor Helper method for robot control
  void move(int n1, int n2, int angle, int speed);
  void turn(int n1, int n2, int turnSpeed);
  void tank(int n1, int n2, int speed1, int speed2);

  void moveM1M2(int angle, int speed);
  void turnM1M2(int turnSpeed);
  void tankM1M2(int speed1, int speed2);

#if defined(HAS_MOTOR34)
  void moveM3M4(int angle, int speed);
  void turnM3M4(int turnSpeed);
  void tankM3M4(int speed3, int speed4);
#endif

  void forwardM1M2(int speed);
  void backwardM1M2(int speed);
  void leftM1M2(int speed);
  void rightM1M2(int speed);
  void stopM1M2();
  void brakeM1M2();

#if defined(HAS_MOTOR34)
  void forwardM3M4(int speed);
  void backwardM3M4(int speed);
  void leftM3M4(int speed);
  void rightM3M4(int speed);
  void stopM3M4();
  void brakeM3M4();
#endif

  void forwardM1(int speed);
  void forwardM2(int speed);

#if defined(HAS_MOTOR34)
  void forwardM3(int speed);
  void forwardM4(int speed);
#endif

  void backwardM1(int speed);
  void backwardM2(int speed);

#if defined(HAS_MOTOR34)
  void backwardM3(int speed);
  void backwardM4(int speed);
#endif

  void stopM1();
  void stopM2();

#if defined(HAS_MOTOR34)
  void stopM3();
  void stopM4();
#endif

  void brakeM1();
  void brakeM2();

#if defined(HAS_MOTOR34)
  void brakeM3();
  void brakeM4();
#endif

  //Sensor
  int readSound();
  int readLight();
  int readSlider();
  void initPush();
  bool readPush();

#if defined(HAS_MPU6050)
  float readTemperature();
  float readAccelX();
  float readAccelY();
  float readAccelZ();
  float readGyroX();
  float readGyroY();
  float readGyroZ();
#endif

#if defined(HAS_ONBBOARD_DISTANCE)
  void initBuiltinDistance();
  void initBuiltinDistanceNoBuffer();
  double readBuiltinDistance();
  double readBuiltinDistanceNoBuffer();
#endif 

#if defined(HAS_PHREF)
  int readPhRef(int num);
  int readPhRef1();
  int readPhRef2();
  int readPhRef3();
  int readPhRef4();
#endif

  //LED
  void led(bool val);
  void led(int val);
  
  //
private:
#if defined(HAS_ONBBOARD_DISTANCE)
  // Global variables.
  double buf[BUILTIN_DISTANCE_BUFFER_SIZE];  // Analog readings at 100khz & stored here
  double out[BUILTIN_DISTANCE_BUFFER_SIZE];  // output of filter stored here.
  int buffer_index;         // Interupt increments buffer
  boolean buffer_full;      // Flag for when complete.

  double a0,a1,a2,b1,b2; // filter kernel poles
  double f,bw;           // frequency cutoff and bandwidth
  double r,k;            // filter coefficients

  double output;

  double doFilter();
#endif

#if defined(HAS_MPU6050)
  MPU6050 accelgyro;
#endif
};

#endif
