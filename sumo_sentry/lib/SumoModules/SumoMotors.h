#ifndef SUMOMOTORS_H
#define SUMOMOTORS_H

#include <Arduino.h>

class SumoMotors
{
public:
	SumoMotors(const char ML1, const char ML2, const char MR1, const char MR2);
	void move(int left_s, int right_s); //move each side at desired speeds
	void drive(int speed); //move both sides at desired speed
	void brake(); //stop wheels

private:
	char MotorL1,MotorL2,MotorR1,MotorR2; //motors

};

#endif