#include <Arduino.h>
#include "QTRSensors.h"
#include "SumoIR.h"
#include "SumoMotors.h"
void setup();
void loop();
bool seesLine();
String whereSeesLine();
void readLineSensors();
#line 1 "src/sketch.ino"
//#include "QTRSensors.h"
//#include "SumoIR.h"
//#include "SumoMotors.h"

const char MotorL1 = 10;
const char MotorL2 = 11;
const char MotorR1 = 6;
const char MotorR2 = 5;

// Analog Distance Sensors
const char DistFL = 2;
const char DistF = 1;
const char DistFR = 0;
const char DistL = 3;
const char DistR = 7;

// Digital Line Sensors
const char LineBR = 3;
const char LineBL = 2;
const char LineFR = 9;
const char LineFL = 4;

// Line Sensors Initialization
QTRSensorsRC qtrline((unsigned char[]) {LineBR, LineBL, LineFR, LineFL}, 4);
unsigned int sensor_values[4];
unsigned int line_trigger = 1000;

// Distance Sensor Initialization
SumoIR dist;

// Motor Initialization
SumoMotors motors(MotorL1,MotorL2,MotorR1,MotorR2);

// Algorithm Initialization
/*
    modes:
    -2 - sees line in back sensors
    -1 - sees line in front sensors
     0 - sees nothing out of place
     1 - sees bot in front only
     2 - sees bot in front-leftish
     3 - sees bot in front-rightish
     4 - sees bot in far left
     5 - sees bot in far right
    99 - low battery, do nothing!

*/
int mode_prev;
int mode;
int mode_count;
int attack_speed = 255;
int normal_speed = 200;



void setup() 
{
    motors.brake(); //motors constructor already sets pins to OUTPUT
    
    dist.addIR(DistL,300); //add all five distance sensors
    dist.addIR(DistFL,200);
    dist.addIR(DistF,200);
    dist.addIR(DistFR,200);
    dist.addIR(DistR,300);

    Serial.begin(9600);
    Serial.println("Starting Sumo Reporting...");
    mode = 0;
}

void loop() 
{
    //check for line, watch out for outliers
    if (seesLine() && seesLine())
    {
        String lineLoc = whereSeesLine();

    }

    else
    {
        //check for opposing bot
        String botLoc = dist.getTriggered();

    }

    //do what mode requires
    if (mode == 0) //sees nothing
    {
        motors.drive(normal_speed);
    }
    else if (mode == 1) // target acquired, tactical nuke incoming
    {
        motors.drive(attack_speed);
    }
    else if (mode == 2) // target spotted in front left
    {

    }
    else if (mode == 3) // target spotted in front right
    {

    }
    else if (mode == 4) // target spotted in far left
    {

    }
    else if (mode == 5) // target spotted in far right
    {

    }
    else if (mode == 99) // battery low, stop moving!
    {
        motors.brake();
    }

    //iterate mode counter if the same mode as before, reset otherwise
    if (mode == mode_prev)
        mode_count++;
    else
        mode_count = 0;

    //one loop complete, ayyyy
}

bool seesLine()
{
    readLineSensors();
    return (sensor_values[3] < 1000 || sensor_values[2] < 1000 || sensor_values[1] < 1000 || sensor_values[0] < 1000);
}

String whereSeesLine()
{
    readLineSensors();
    String triggered = "";
    for (int i = 0; i < 4; i++)
    {
        if(sensor_values[i] < 1000)
            triggered += '1';
        else
            triggered += '0';
    }
    return triggered;
}

void readLineSensors()
{
    qtrline.read(sensor_values);
}
