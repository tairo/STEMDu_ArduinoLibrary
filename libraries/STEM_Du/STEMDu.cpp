#include <Arduino.h> 

#include "STEMDu.h"
#include "STEMDu.h"

#if defined(NANOBOARD_AG) || defined(CHIBIDUINO)
#define P_M1IN1 7
#define P_M1IN2 8
#define P_M1PWM 9
#define P_M2IN1 5
#define P_M2IN2 6
#define P_M2PWM 10
#else
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

STEMDu::STEMDu(){
	this->_board_type = 3; // Default: Type III
  	this->_has_i2c_lcd = false;
	this->_has_phref = false;
  	this->_has_wireless = false;

	for(int i=0;i<MAX_ANALOG_PORTS;i++){
		this->_analog_hwconf[i] = 0; // Default : no connected
	}
	for(int i=0;i<MAX_DIGITAL_PORTS;i++){
		this->_digital_hwconf[i] = 0; // Default : no connected
	}
	this->init();
}

STEMDu::STEMDu(int type){
	this->_board_type = type;
  	this->_has_i2c_lcd = false;
	this->_has_phref = false;
  	this->_has_wireless = false;

	for(int i=0;i<MAX_ANALOG_PORTS;i++){
		this->_analog_hwconf[i] = 0; // Default : no connected
	}
	for(int i=0;i<MAX_DIGITAL_PORTS;i++){
		this->_digital_hwconf[i] = 0; // Default : no connected
	}
	this->init();
}

STEMDu::STEMDu(int type, int* analogHWCfg, int* digitalHWConfig){
	this->_board_type = type;

	for(int i=0;i<MAX_ANALOG_PORTS;i++){
		this->_analog_hwconf[i] = analogHWCfg[i];
	}
	for(int i=0;i<MAX_DIGITAL_PORTS;i++){
		this->_digital_hwconf[i] = digitalHWConfig[i];
	}
	this->init();
}

void STEMDu::enableI2CLCD(){
	this->_has_i2c_lcd = true;
}

void STEMDu::enablePHREF(){
	this->_has_phref = true;
	pinMode(P_MPX_PHREF1,OUTPUT);
	pinMode(P_MPX_PHREF2,OUTPUT);
	pinMode(P_MPX_PHREF3,OUTPUT);
	pinMode(P_MPX_PHREF4,OUTPUT);
	digitalWrite(P_MPX_PHREF1,HIGH);
	digitalWrite(P_MPX_PHREF2,LOW);
	digitalWrite(P_MPX_PHREF3,LOW);
	digitalWrite(P_MPX_PHREF4,LOW);
}

void STEMDu::enableWireless(){
	this->_has_wireless = true;
}

void STEMDu::init(){
	pinMode(P_LED,OUTPUT);
	pinMode(P_PUSH,INPUT_PULLUP);

	for(int i=0;i<MAX_DIGITAL_PORTS;i++){
	}

	// Motor
	pinMode(P_M1IN1,OUTPUT);
	pinMode(P_M1IN2,OUTPUT);
	pinMode(P_M2IN1,OUTPUT);
	pinMode(P_M2IN2,OUTPUT);
	if(this->_board_type > 2){ //Type III or upper
		pinMode(P_M3IN1,OUTPUT);
		pinMode(P_M3IN2,OUTPUT);
		pinMode(P_M4IN1,OUTPUT);
		pinMode(P_M4IN2,OUTPUT);
	}

	// I2CLCD
	if(this->_board_type == 2) this->enableI2CLCD();

	// Photo Reflector
	if(this->_board_type == 2) this->enablePHREF();

	// Wireless
	if(this->_board_type == 4) this->enableWireless();
}

void STEMDu::motor(int n, int speed){
	int in1 = HIGH;
	int in2 = LOW;

	if(speed<0){
		in1 = LOW;
		in2 = HIGH;
		speed = -speed;
	}
	else if(speed == MOTOR_STOP){
		in1 = LOW;
		in2 = LOW;
	}
	else if(speed == MOTOR_BRAKE){
		in1 = HIGH;
		in2 = HIGH;
	}
	
	switch(n){
		case 1:
    		digitalWrite(P_M1IN1, in1);
  			digitalWrite(P_M1IN2, in2);
			analogWrite(P_M1PWM, speed);
			break;
		case 2:
    		digitalWrite(P_M2IN1, in1);
		    digitalWrite(P_M2IN2, in2);
			analogWrite(P_M2PWM, speed);
			break;
		case 3:
		    digitalWrite(P_M3IN1, in1);
		    digitalWrite(P_M3IN2, in2);
			analogWrite(P_M3PWM, speed);
			break;
		case 4:
		    digitalWrite(P_M4IN1, in1);
		    digitalWrite(P_M4IN2, in2);
			analogWrite(P_M4PWM, speed);
			break;
		default:
			/* error */
			break;
	}
}

void STEMDu::move(int n1, int n2, int angle, int speed){
	int tmpAngle = angle % 360;
	int tmpSpeed = speed;
	
	if(angle>=0 && tmpAngle <= 90){
		tmpSpeed = tmpSpeed*(90.0 - tmpAngle)/90.0;
		this->motor(n1,speed);
		this->motor(n2,tmpSpeed);
	}
	else if(angle>90 && tmpAngle <= 180){
		tmpSpeed = tmpSpeed*(tmpAngle - 90.0)/90.0;
		this->motor(n1,-speed);
		this->motor(n2,-tmpSpeed);
	}
	else if(angle>180 && tmpAngle <= 270){
		tmpSpeed = tmpSpeed*(270.0 - tmpAngle)/90.0;
		this->motor(n1,-tmpSpeed);
		this->motor(n2,-speed);
	}
	else if(angle>270 && tmpAngle <= 360){
		tmpSpeed = tmpSpeed*(tmpAngle - 270.0)/90.0;
		this->motor(n1,tmpSpeed);
		this->motor(n2,speed);
	}
}

void STEMDu::turn(int n1, int n2, int turnSpeed){
	this->motor(n1,turnSpeed);
	this->motor(n2,-turnSpeed);
}

void STEMDu::tank(int n1, int n2, int speed1, int speed2){
	this->motor(n1,speed1);
	this->motor(n2,speed2);
}

#if !defined(STEMDU_REDUCE_LIBRARY_SIZE)
void STEMDu::moveM1M2(int angle, int speed){
	this->move(1,2,angle,speed);
}

void STEMDu::turnM1M2(int turnSpeed){
	this->turn(1,2,turnSpeed);
}

void STEMDu::tankM1M2(int speed1, int speed2){
	this->tank(1,2,speed1,speed2);
}

void STEMDu::moveM3M4(int angle, int speed){
	this->move(3,4,angle,speed);
}

void STEMDu::turnM3M4(int turnSpeed){
	this->turn(3,4,turnSpeed);
}

void STEMDu::tankM3M4(int speed3, int speed4){
	this->tank(3,4,speed3,speed4);
}

void STEMDu::forwardM1(int speed){
	this->motor(1,speed);
}

void STEMDu::forwardM2(int speed){
	this->motor(2,speed);
}

void STEMDu::forwardM3(int speed){
	this->motor(3,speed);
}

void STEMDu::forwardM4(int speed){
	this->motor(4,speed);
}

void STEMDu::backwardM1(int speed){
	this->motor(1,-speed);
}

void STEMDu::backwardM2(int speed){
	this->motor(2,-speed);
}

void STEMDu::backwardM3(int speed){
	this->motor(3,-speed);
}

void STEMDu::backwardM4(int speed){
	this->motor(4,-speed);
}

void STEMDu::stopM1(){
	this->motor(1,MOTOR_STOP);
}

void STEMDu::stopM2(){
	this->motor(2,MOTOR_STOP);
}

void STEMDu::stopM3(){
	this->motor(3,MOTOR_STOP);
}

void STEMDu::stopM4(){
	this->motor(4,MOTOR_STOP);
}

void STEMDu::brakeM1(){
	this->motor(1,MOTOR_BRAKE);
}

void STEMDu::brakeM2(){
	this->motor(2,MOTOR_BRAKE);
}

void STEMDu::brakeM3(){
	this->motor(3,MOTOR_BRAKE);
}

void STEMDu::brakeM4(){
	this->motor(4,MOTOR_BRAKE);
}

void STEMDu::forwardM1M2(int speed){
	this->motor(1,speed);
	this->motor(2,speed);
}

void STEMDu::backwardM1M2(int speed){
	this->motor(1,-speed);
	this->motor(2,-speed);
}

void STEMDu::leftM1M2(int speed){
	this->motor(1,-speed);
	this->motor(2,speed);
}

void STEMDu::rightM1M2(int speed){
	this->motor(1,speed);
	this->motor(2,-speed);
}

void STEMDu::stopM1M2(){
	this->motor(1,MOTOR_STOP);
	this->motor(2,MOTOR_STOP);
}

void STEMDu::brakeM1M2(){
	this->motor(1,MOTOR_BRAKE);
	this->motor(2,MOTOR_BRAKE);
}

void STEMDu::forwardM3M4(int speed){
	this->motor(3,speed);
	this->motor(4,speed);
}

void STEMDu::backwardM3M4(int speed){
	this->motor(3,-speed);
	this->motor(4,-speed);
}

void STEMDu::leftM3M4(int speed){
	this->motor(3,-speed);
	this->motor(4,speed);
}

void STEMDu::rightM3M4(int speed){
	this->motor(3,speed);
	this->motor(4,-speed);
}

void STEMDu::stopM3M4(){
	this->motor(3,MOTOR_STOP);
	this->motor(4,MOTOR_STOP);
}

void STEMDu::brakeM3M4(){
	this->motor(3,MOTOR_BRAKE);
	this->motor(4,MOTOR_BRAKE);
}
#endif

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
	if(this->_board_type > 2){ //Type III or upper
		pinMode(P_PUSH,INPUT_PULLUP);
	}
	return !digitalRead(P_PUSH);
}

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

void STEMDu::led(bool val){
	digitalWrite(P_LED, val);
}

void STEMDu::led(int val){
	analogWrite(P_LED, val);
}
