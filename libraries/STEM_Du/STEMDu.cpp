#include <Arduino.h> 

#include "STEMDu.h"

#define P_M1IN1 4
#define P_M1IN2 5
#define P_M1PWM 6
#define P_M2IN1 7
#define P_M2IN2 8
#define P_M2PWM 9
#if defined(JRTA_1)
// Only JRTA-1
#define P_M3IN1 10
#define P_M3IN2 11
#define P_M3PWM 12
#define P_M4IN1 0
#define P_M4IN2 1
#define P_M4PWM 13
#else
// From RDC-102 No Mark
#define P_M3IN1 0
#define P_M3IN2 1
#define P_M3PWM 10
#define P_M4IN1 11
#define P_M4IN2 12
#define P_M4PWM 13
#endif

#define P_LED    13
#define P_PUSH   12
#define P_SOUND  0
#define P_LIGHT  4
#define P_SLIDER 5
#define P_PHREF  3

#define P_MPX_PHREF1 0
#define P_MPX_PHREF2 1
#define P_MPX_PHREF3 10
#define P_MPX_PHREF4 11

void _M1(bool in1, bool in2, int pwm){
    digitalWrite(P_M1IN1, in1);
    digitalWrite(P_M1IN2, in2);
	analogWrite(P_M1PWM, pwm);
}

void _M2(bool in1, bool in2, int pwm){
    digitalWrite(P_M2IN1, in1);
    digitalWrite(P_M2IN2, in2);
	analogWrite(P_M2PWM, pwm);
}

void _M3(bool in1, bool in2, int pwm){
    digitalWrite(P_M3IN1, in1);
    digitalWrite(P_M3IN2, in2);
	analogWrite(P_M3PWM, pwm);
}

void _M4(bool in1, bool in2, int pwm){
    digitalWrite(P_M4IN1, in1);
    digitalWrite(P_M4IN2, in2);
	analogWrite(P_M4PWM, pwm);
}

STEMDu::STEMDu(){
	this->init();
}

void STEMDu::init(){
	pinMode(P_LED,OUTPUT);
	pinMode(P_PUSH,INPUT_PULLUP);
#if defined(TYPE_II)
	pinMode(P_MPX_PHREF1,OUTPUT);
	pinMode(P_MPX_PHREF2,OUTPUT);
	pinMode(P_MPX_PHREF3,OUTPUT);
	pinMode(P_MPX_PHREF4,OUTPUT);
	digitalWrite(P_MPX_PHREF1,HIGH);
	digitalWrite(P_MPX_PHREF2,LOW);
	digitalWrite(P_MPX_PHREF3,LOW);
	digitalWrite(P_MPX_PHREF4,LOW);
#endif
}

void STEMDu::forwardM1(int speed){
	_M1(HIGH,LOW,speed);
}

void STEMDu::forwardM2(int speed){
	_M2(HIGH,LOW,speed);
}

void STEMDu::forwardM3(int speed){
	_M3(HIGH,LOW,speed);
}

void STEMDu::forwardM4(int speed){
	_M4(HIGH,LOW,speed);
}

void STEMDu::backwardM1(int speed){
	_M1(LOW,HIGH,speed);
}

void STEMDu::backwardM2(int speed){
	_M2(LOW,HIGH,speed);
}

void STEMDu::backwardM3(int speed){
	_M3(LOW,HIGH,speed);
}

void STEMDu::backwardM4(int speed){
	_M4(LOW,HIGH,speed);
}

void STEMDu::stopM1(){
	_M1(LOW,LOW,0);
}

void STEMDu::stopM2(){
	_M2(LOW,LOW,0);
}

void STEMDu::stopM3(){
	_M3(LOW,LOW,0);
}

void STEMDu::stopM4(){
	_M4(LOW,LOW,0);
}

void STEMDu::brakeM1(){
	_M1(HIGH,HIGH,0);
}

void STEMDu::brakeM2(){
	_M2(HIGH,HIGH,0);
}

void STEMDu::brakeM3(){
	_M3(HIGH,HIGH,0);
}

void STEMDu::brakeM4(){
	_M4(HIGH,HIGH,0);
}

void STEMDu::forwardM1M2(int speed){
	this->forwardM1(speed);
	this->forwardM2(speed);
}

void STEMDu::backwardM1M2(int speed){
	this->backwardM1(speed);
	this->backwardM2(speed);
}

void STEMDu::leftM1M2(int speed){
	this->backwardM1(speed);
	this->forwardM2(speed);
}

void STEMDu::rightM1M2(int speed){
	this->forwardM1(speed);
	this->backwardM2(speed);
}

void STEMDu::stopM1M2(){
	this->stopM1();
	this->stopM2();
}

void STEMDu::brakeM1M2(){
	this->brakeM1();
	this->brakeM2();
}

void STEMDu::forwardM3M4(int speed){
	this->forwardM3(speed);
	this->forwardM4(speed);
}

void STEMDu::backwardM3M4(int speed){
	this->backwardM3(speed);
	this->backwardM4(speed);
}

void STEMDu::leftM3M4(int speed){
	this->backwardM3(speed);
	this->forwardM4(speed);
}

void STEMDu::rightM3M4(int speed){
	this->forwardM3(speed);
	this->backwardM4(speed);
}

void STEMDu::stopM3M4(){
	this->stopM3();
	this->stopM4();
}

void STEMDu::brakeM3M4(){
	this->brakeM3();
	this->brakeM4();
}

int STEMDu::readSound(){
	return analogRead(P_SOUND);
}

int STEMDu::readLight(){
	return analogRead(P_LIGHT);
}

int STEMDu::readSlider(){
	return analogRead(P_SLIDER);
}

bool STEMDu::readPush(){
	return !digitalRead(P_PUSH);
}

#if defined(TYPE_II) || defined(USE_PHREF)
int STEMDu::readPhRef(int num){
	if(num>0 && num<5){
		digitalWrite(P_MPX_PHREF1,LOW);
		digitalWrite(P_MPX_PHREF2,LOW);
		digitalWrite(P_MPX_PHREF3,LOW);
		digitalWrite(P_MPX_PHREF4,LOW);
		switch(num){
			case 1:
				digitalWrite(P_MPX_PHREF1,HIGH);
				break;
			case 2:
				digitalWrite(P_MPX_PHREF2,HIGH);
				break;
			case 3:
				digitalWrite(P_MPX_PHREF3,HIGH);
				break;
			case 4:
				digitalWrite(P_MPX_PHREF4,HIGH);
				break;
			default:
				digitalWrite(P_MPX_PHREF1,HIGH);
				break;
		}
		return analogRead(P_PHREF);
	}
	else{
		return 0; //num range error
	}
}

int STEMDu::readPhRef1(){
	return this->readPhRef(1);
}

int STEMDu::readPhRef2(){
	return this->readPhRef(2);
}

int STEMDu::readPhRef3(){
	return this->readPhRef(3);
}

int STEMDu::readPhRef4(){
	return this->readPhRef(4);
}
#endif

void STEMDu::led(bool val){
	digitalWrite(P_LED, val);
}

void STEMDu::led(int val){
	analogWrite(P_LED, val);
}
