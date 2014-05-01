#ifndef STEM_Du_h
#define STEM_Du_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if !defined(NANOBOARD_AG) && !defined(CHIBIDUINO) && !defined(JRTA1) && !defined(RDC_102_NO_MARK) && !defined(RDC_102_R0) && !defined(RDC_102_R1) && !defined(RDC_102_R2)
//#define NANOBOARD_AG
//#define CHIBIDUINO
//#define JRTA1
//#define RDC_102_NO_MARK
//#define RDC_102_R0
//#define RDC_102_R1
#define RDC_102_R2
#endif

#if !defined(TYPE_I) && !defined(TYPE_II) && !defined(TYPE_III) && !defined(TYPE_III_R)
//#define TYPE_I
//#define TYPE_II
#define TYPE_III
//#define TYPE_III_R
#endif

//#define STEMDU_REDUCE_LIBRARY_SIZE

////////////////////////////////////////////////////////
// STEM Du RDC-102 / ATmega328 based model
#define MAX_DIGITAL_PORTS 16
#define MAX_ANALOG_PORTS  8

#define MOTOR_STOP  0
#define MOTOR_BRAKE 1023

#define MOTOR1 1
#define MOTOR2 2
#define MOTOR3 3
#define MOTOR4 4
////////////////////////////////////////////////////////


class STEMDu {
public:
  STEMDu();
  STEMDu(int type);
  STEMDu(int type, int* analogHWCfg, int* digitalHWConfig);

  void init();
  void enableI2CLCD();
  void enablePHREF();
  void enableWireless();
  
  //Motor
  void motor(int n, int speed);

  //Motor Helper method for robot control
  void move(int n1, int n2, int angle, int speed);
  void turn(int n1, int n2, int turnSpeed);
  void tank(int n1, int n2, int speed1, int speed2);

#if !defined(STEMDU_REDUCE_LIBRARY_SIZE)
  void moveM1M2(int angle, int speed);
  void turnM1M2(int turnSpeed);
  void tankM1M2(int speed1, int speed2);
  
  void moveM3M4(int angle, int speed);
  void turnM3M4(int turnSpeed);
  void tankM3M4(int speed3, int speed4);

  void forwardM1M2(int speed);
  void backwardM1M2(int speed);
  void leftM1M2(int speed);
  void rightM1M2(int speed);
  void stopM1M2();
  void brakeM1M2();

  void forwardM3M4(int speed);
  void backwardM3M4(int speed);
  void leftM3M4(int speed);
  void rightM3M4(int speed);
  void stopM3M4();
  void brakeM3M4();

  void forwardM1(int speed);
  void forwardM2(int speed);
  void forwardM3(int speed);
  void forwardM4(int speed);
  void backwardM1(int speed);
  void backwardM2(int speed);
  void backwardM3(int speed);
  void backwardM4(int speed);
  void stopM1();
  void stopM2();
  void stopM3();
  void stopM4();
  void brakeM1();
  void brakeM2();
  void brakeM3();
  void brakeM4();
#endif

  //Sensor
  int readSound();
  int readLight();
  int readSlider();
  void initPush();
  bool readPush();
  
  int readPhRef(int num);
  int readPhRef1();
  int readPhRef2();
  int readPhRef3();
  int readPhRef4();

  //LED
  void led(bool val);
  void led(int val);
  
  //
private:
  int _board_type;
  // 0 : no type (use 2 motor drivers)
  // 1  : Type I
  // 2  : Type II
  // 3  : Type III
  // 4  : Type III-R
  int _analog_hwconf[MAX_ANALOG_PORTS];
  // [0] : A0
  // [1] : A1
  // [2] : A2
  // ...
  int _digital_hwconf[MAX_DIGITAL_PORTS];
  // [0] : P0
  // [1] : P1
  // [2] : P2
  // ...
  bool _has_i2c_lcd;
  bool _has_phref;
  bool _has_wireless;
};

#endif
