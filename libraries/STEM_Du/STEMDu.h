#ifndef STEM_Du_h
#define STEM_Du_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class STEMDu {
public:
  STEMDu();
  STEMDu(int version);

  void init();
  
  //Motor
  void forwardM1M2(int speed);
  
private:
  int _version;
};

#endif
