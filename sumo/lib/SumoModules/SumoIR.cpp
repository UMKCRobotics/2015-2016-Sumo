#include "SumoIR.h"

SumoIR::SumoIR()
{
	count = 0;
}

void SumoIR::addIR(const char sensor, int trigger)
{
	if (count < 5)
	{
		ir_ports[count] = sensor;
		ir_triggers[count] = trigger;
		count++;
	}
}

String SumoIR::getTriggered()
{
	String triggered = "";
	for (int i = 0; i < 5; i++)
	{
		if (analogRead(ir_ports[i]) > ir_triggers[i])
			triggered += '1';
		else
			triggered += '0';
	}
	return triggered;
}