
#include "sumosense.h"
#include "Arduino.h"

int _count;
int _ports[10];
int _range[10];
bool _isAbove[10];
int _numberOfSensors;

SumoSense::SumoSense(int numberOfSensors) {
	_count = 0;
	_numberOfSensors = numberOfSensors;
}

void SumoSense::addSensor(int port, int range, bool isAbove) {
	_ports[_count] = port;
	_range[_count] = range;
	_isAbove[_count] = isAbove;
	_count += 1;
}

String SumoSense::returnWhere() {
	bool detected = false;
	String location = "1";
	for (int i = 0; i < _numberOfSensors; i++)
	{
		if ((_isAbove[i]))
		{
			if (analogRead(_ports[i]) > _range[i])
			{
				location += '1';
				detected = true;
			}
			else
			{
				location += '0';
			}
		}
		else
		{
			if (analogRead(_ports[i]) <= _range[i])
			{
				location += '1';
				detected = true;
			}
			else
			{
				location += '0';
			}
		}
	}
	if (!(detected))
	{
		location = "0";
	}
	return location;
}

bool SumoSense::returnIfAny() {
	bool found = false;
	for (int i = 0; i < _numberOfSensors; i++)
	{
		if ((_isAbove[i]))
		{
			if (analogRead(_ports[i]) > _range[i])
			{
				found = true;
				break;
			}
		}
		else
		{
			if (analogRead(_ports[i]) <= _range[i])
			{
				found = true;
				break;
			}
		}
	}
	return found;
}