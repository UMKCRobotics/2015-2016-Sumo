#ifndef sumosense_h
#define sumosense_h

#include <Arduino.h>

//KEY WORDS START
#define ABOVE true
#define BELOW false
//KEY WORDS END


class SumoSense
{
	public:
		SumoSense(int numberOfSensors);
		void addSensor(int port, int range, bool isAbove);
		String returnWhere();
		bool returnIfAny();
	private:
		int _count;
		int _numberOfSensors;
		int _ports[10];
		int _range[10];
		bool _isAbove[10];

};

#endif