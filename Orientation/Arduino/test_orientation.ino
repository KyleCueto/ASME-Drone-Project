# include "orientation.h"
#include <stdio.h>

// Motor -> ESC Variables
int m1;
int m2;
int m3;
int m4;

// Control Inputs
int throttle = 1000;
int roll = 0;
int pitch = 0;
int yaw = 0;
int type;

void setup (){
    Serial.begin(9600);
    m1, m2, m3, m4 = mma(throttle, roll, pitch, yaw);
    Serial.print("Motor 1 = ");
    Serial.print(m1);
    Serial.print(" - ");
    Serial.print("Motor 2 = ");
    Serial.print(m2);
    Serial.print(" - ");
    Serial.print("Motor 3 = ");
    Serial.print(m3);
    Serial.print(" - ");
    Serial.print("Motor 4 = ");
    Serial.println(m4);
    return 0;
}

void loop (){}
