#include "QTRSensors.h"
#include "SumoIR.h"
#include "SumoMotors.h"

const char MotorL1 = 11;
const char MotorL2 = 10;
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

bool was_left = false;


void setup() 
{
    motors.brake(); //motors constructor already sets pins to OUTPUT
    
    dist.addIR(DistL,220); //add all five distance sensors
    dist.addIR(DistFL,150);
    dist.addIR(DistF,150);
    dist.addIR(DistFR,150);
    dist.addIR(DistR,220);

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
        if (lineLoc[3] == '1' || lineLoc[2] == '1') //line in front
        {
            //motors.brake();
            motors.drive(-normal_speed);
            delay(400);
            if (lineLoc[3] == '1' && lineLoc[2] == '1') //both or on left only
                motors.move(attack_speed,-attack_speed);

            else if (lineLoc[2] == '1') //front right only
                motors.move(-attack_speed,attack_speed);

            else //front left only
                motors.move(attack_speed,-attack_speed);
            
            delay(300);
        }
        else if (lineLoc[1] == '1' || lineLoc[0] == '1') //line in back
        {
            if (lineLoc[1] == '1' && lineLoc[2] == '1') //line in back BOTH
            {
                motors.drive(attack_speed);
                delay(100);
            }
            else if (lineLoc[1] == '1') //line in back LEFT
            {
                motors.move(attack_speed,normal_speed);
                delay(100);
            }
            else //line in back RIGHT
            {
                motors.move(normal_speed,attack_speed);
                delay(100);
            }
        }
    }

    else
    {
        //check for opposing bot
        String botLoc = dist.getTriggered();
        if (botLoc[0] == '1') //left
            mode = 4;
        else if (botLoc[4] == '1') //right
            mode = 5;
        else if (botLoc[1] == '1' && botLoc[2] == '1') //front left AND front
            mode = 6;
        else if (botLoc[1] == '1') //front left
            mode = 2;
        else if (botLoc[3] == '1' && botLoc[2] == '1') //front right AND front
            mode = 7;
        else if (botLoc[3] == '1') //front right
            mode = 3;
        else if (botLoc[2] == '1') //front
            mode = 1;
        else
            mode = 0;

    }

    //do what mode requires
    if (mode == 0) //sees nothing
    {
        motors.move(attack_speed,-attack_speed/4);
    }
    else if (mode == 1) // target acquired, tactical nuke incoming
    {
        motors.drive(attack_speed);
    }
    else if (mode == 2) // target spotted in front left
    {   motors.move(-normal_speed,attack_speed);

    }
    else if (mode == 3) // target spotted in front right
    {
        motors.move(attack_speed,-normal_speed);
    }
    else if (mode == 4) // target spotted in far left
    {
        motors.move(-attack_speed,attack_speed);
    }
    else if (mode == 5) // target spotted in far right
    {
        motors.move(attack_speed,-attack_speed);
    }
    else if (mode == 6) //target spotted in front left AND front
    {
        motors.move(normal_speed,attack_speed);
    }
    else if (mode == 7) //target spotted in front right AND front
    {
        motors.move(attack_speed,normal_speed);
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
