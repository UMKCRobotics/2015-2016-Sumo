#include <QTRSensors.h>

const char MotorL1 = 10;
const char MotorL2 = 11;
const char MotorR1 = 9;
const char MotorR2 = 8;

// Analog Inputs
const char DistFL = 2;
const char DistF = 1;
const char DistFR = 0;
const char DistL = 3;
const char DistR = 7;
const char LineBR = 3;
const char LineBL = 2;
const char LineFR = 5;
const char LineFL = 4;

//Line Sensors
QTRSensorsRC qtrline((unsigned char[]) {LineBR, LineBL, LineFR, LineFL}, 4);
unsigned int sensor_values[4];

void setup() 
{
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);

  Serial.begin(9600);
  
  digitalWrite(MotorL1,LOW);
  digitalWrite(MotorL2,LOW);
  digitalWrite(MotorR1,LOW);
  digitalWrite(MotorR2,LOW);

  delay(1000);

  Serial.println("Starting Sumo Reporting...");
}

void loop() 
{
//  Serial.println("Left        FLeft         Front           FRight        Right");
//  Serial.print(analogRead(DistL));
//  Serial.print("\t\t");
//  Serial.print(analogRead(DistFL));
//  Serial.print("\t\t");
//  Serial.print(analogRead(DistF));
//  Serial.print("\t\t");
//  Serial.print(analogRead(DistFR));
//  Serial.print("\t\t");
//  Serial.println(analogRead(DistR));
qtrline.read(sensor_values);
  Serial.println("FLeft         FRight");
  Serial.print(sensor_values[3]);
  Serial.print("\t\t");
  Serial.println(sensor_values[2]);
  Serial.println("BLeft         BRight");
  Serial.print(sensor_values[1]);
  Serial.print("\t\t");
  Serial.println(sensor_values[0]);
  Serial.println();
  
  delay(1000);
}
