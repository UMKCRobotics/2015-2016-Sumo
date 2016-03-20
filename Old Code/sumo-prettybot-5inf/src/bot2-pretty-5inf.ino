#include "RedBot.h"
#include "sumosense.h"
//LINE SENSORS
#define LEFTline A2
//#define MIDDLEline A1
#define RIGHTline A0
//INFRARED DISTANCE SENSORS
#define MRIGHTinfra A1
#define RIGHTinfra A6
#define MIDDLEinfra A4
#define LEFTinfra A5
#define MLEFTinfra A3
//VOLTAGE SENSOR
#define BATTERY A7

RedBotMotors motor;
SumoSense infraS = SumoSense(5);
SumoSense lineS = SumoSense(3);

int MAXFORW = 170;
int MAXBACK = -170;

int ATTACK = 230;

int mode = 3;

void setup()
{
  pinMode(LEFTline,INPUT);
  //pinMode(MIDDLEline,INPUT);
  pinMode(RIGHTline,INPUT);

  pinMode(MIDDLEinfra, INPUT);
  pinMode(LEFTinfra, INPUT);
  pinMode(RIGHTinfra, INPUT);

  Serial.begin(9600);

  infraS.addSensor(MLEFTinfra,300,ABOVE);
  infraS.addSensor(LEFTinfra,325,ABOVE);
  infraS.addSensor(MIDDLEinfra,275,ABOVE);
  infraS.addSensor(RIGHTinfra,285,ABOVE);
  infraS.addSensor(MRIGHTinfra,300,ABOVE);

  lineS.addSensor(LEFTline,899,ABOVE);
  //lineS.addSensor(MIDDLEline,899,ABOVE);
  lineS.addSensor(RIGHTline,899,ABOVE);
}


void loopTEST()
{
	String infraString = infraS.returnWhere();
	Serial.println(infraString);
	//bool infraBool = infraS.returnIfAny();
	//Serial.println(infraBool);
	delay(200);
}

void loop()
{
	if (batteryLow()) //#####DETERMINE IF LOW BATTERY#####
	{
		if (batteryLow())
		{
			if (batteryLow())
			{
				mode = 99;
			}
		}
	} 


	if (lineS.returnIfAny()) //#####DETERMINE IF LINE#####
	{
		
		if (lineS.returnIfAny())
		{
			if (lineS.returnIfAny())
			{
		                String whereLine = lineS.returnWhere();
				mode = 3;

				//LINE ON ANY
				if (whereLine.charAt(1) == '1' && whereLine.charAt(2) == '1')
				{
				        driveActually(motor,MAXBACK);
					delay(300);
					driveRotate(motor,MAXFORW,MAXBACK);
					delay(275);
				}
				//LINE ON LEFT-ISH
				else if (whereLine.charAt(1) == '1')
				{
				        driveActually(motor,MAXBACK);
					delay(200);
					driveRotate(motor,MAXBACK,-50);
					delay(250);
					driveRotate(motor,-15,MAXFORW);
					delay(150);
				}
				//LINE ON RIGHT-ISH
				else if (whereLine.charAt(2) == '1')
				{
				        driveActually(motor,MAXBACK);
					delay(200);
					driveRotate(motor,-50,MAXBACK);
					delay(250);
					driveRotate(motor,MAXFORW,-15);
					delay(150);
				}
				//LINE ON ANY
				else
				{
				        driveActually(motor,MAXBACK);
					delay(300);
					driveRotate(motor,MAXFORW,MAXBACK);
					delay(275);
				}
			}
		}
	}
	
	else //#####PERFORM MODE, THEN CHECK INFRA DISTANCE#####
	{	
		//BATTERY LOW
		if (mode == 99)
		{
			motor.stop();
		}
		//NOTHING
		else if (mode == 3)
		{
			driveRotate(motor,MAXFORW,MAXFORW);
		}
		//MOST RIGHT
		else if (mode == 7)
		{
			driveRotate(motor,-20,ATTACK-30);
		}
		//ONLY RIGHT
		else if (mode == 4)
		{
			driveRotate(motor,-10,MAXFORW-30);
		}
		//BOTH MIDDLE AND RIGHT
		else if (mode == 5)
		{
			driveRotate(motor,MAXFORW-40,MAXFORW);
		}
		//MIDDLE ONLY
		else if (mode == 0)
		{
			driveRotate(motor,ATTACK,ATTACK);
		}
		//BOTH MIDDLE AND LEFT
		else if (mode == 2)
		{
			driveRotate(motor,MAXFORW,MAXFORW-40);
		}
		//ONLY LEFT
		else if (mode == 1)
		{
			driveRotate(motor,MAXFORW-30,-10);
		}
		//MOST LEFT
		else if (mode == 6)
		{
			driveRotate(motor,ATTACK-30,-20);
		}

		String botLoc = infraS.returnWhere();
		//Serial.println(botLoc);
		
		bool botOnMLeft = (botLoc.charAt(1) == '1');
		bool botOnLeft = (botLoc.charAt(2) == '1');
		bool botOnMiddle = (botLoc.charAt(3) == '1');
		bool botOnRight = (botLoc.charAt(4) == '1');
		bool botOnMRight = (botLoc.charAt(5) == '1');
		

		if (botOnMLeft)
		{
			mode = 6;
		}

		else if (botOnMRight)
		{
			mode = 7;
		}

		else if (botOnLeft && (!(botOnMiddle)))
		{
			mode = 1;
		}
	
		else if (botOnRight && (!(botOnMiddle)))
		{
			mode = 4;
		}
	
		else if (botOnMiddle && botOnLeft)
		{
			mode = 2;
		}
	
		else if (botOnMiddle && botOnRight)
		{
			mode = 5;
		}
	
		else if (botOnMiddle)
		{
			mode = 0;
		}
	
		else
		{
			mode = 3;
		}
	}			
}

bool batteryLow()
{
  int batteryRaw = analogRead(BATTERY);
  float batteryActual = (batteryRaw*10)/1023;
  return (batteryActual < 6.4);
}

void driveRotate(RedBotMotors& motor,int speedL,int speedR)
{
  motor.leftDrive(speedL);
  motor.rightDrive(speedR);
}

void driveActually(RedBotMotors& motor,int speed){
  motor.drive(speed);
}