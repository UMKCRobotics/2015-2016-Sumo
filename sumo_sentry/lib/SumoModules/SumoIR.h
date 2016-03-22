#ifndef SUMOIR_H
#define SUMOIR_H

#include <Arduino.h>

class SumoIR
{
public:
	SumoIR();
	void addIR(const char sensor, int trigger);
	String getTriggered();
private:
	char ir_ports[5] = {-1,-1,-1,-1,-1};
	int ir_triggers[5] = {-1,-1,-1,-1,-1};
	int count;

};

#endif