#include "SumoMotors.h"

SumoMotors::SumoMotors(const char ML1, const char ML2, const char MR1, const char MR2)
{
	MotorL1 = ML1;
	MotorL2 = ML2;
	MotorR1 = MR1;
	MotorR2 = MR2;
	pinMode(MotorL1, OUTPUT);
	pinMode(MotorL2, OUTPUT);
	pinMode(MotorR1, OUTPUT);
	pinMode(MotorR2, OUTPUT);
}

void SumoMotors::brake()
{
	digitalWrite(MotorL1,LOW);
	digitalWrite(MotorL2,LOW);
	digitalWrite(MotorR1,LOW);
	digitalWrite(MotorR2,LOW);
}

void SumoMotors::move(int left_s, int right_s)
{
	constrain(left_s,-255,255);
	constrain(right_s,-255,255);

	if (left_s == 0 && right_s == 0)
		brake();
	else
	{
		if (left_s > 0) //left motors
		{
			analogWrite(MotorL1,left_s);
			digitalWrite(MotorL2,LOW);
		}
		else if (left_s < 0)
		{
			digitalWrite(MotorL1,LOW);
			analogWrite(MotorL2,-left_s);
		}
		if (right_s > 0) //right motors
		{
			analogWrite(MotorR1,right_s);
			digitalWrite(MotorR2,LOW);
		}
		else if (right_s < 0)
		{
			digitalWrite(MotorR1,LOW);
			analogWrite(MotorR2,-right_s);
		}
	}
}

void SumoMotors::drive(int speed)
{
	move(speed,speed);
}