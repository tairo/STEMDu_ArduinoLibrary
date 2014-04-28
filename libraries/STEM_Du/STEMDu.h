#ifndef STEM_Du_h
#define STEM_Du_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if !defined(JRTA1) && !defined(RDC_102_NO_MARK) && !defined(RDC_102_R0) && !defined(RDC_102_R1) && !defined(RDC_102_R2)
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

#define USE_PHREF

class STEMDu {
public:
  STEMDu();
  
  void init();
  
  //Motor
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

  //Sensor
  int readSound();
  int readLight();
  int readSlider();
  bool readPush();
  
#if defined(TYPE_II) || defined(USE_PHREF)
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
};

#endif
