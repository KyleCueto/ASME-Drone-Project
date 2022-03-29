//# include "orientation.h"
#include <stdio.h>

// Motor -> ESC Variables
int m1;
int m2;
int m3;
int m4;

// Control Inputs
int throttle = 1000;
int roll = 0;
int pitch = -2000;
int yaw = 3000;
int type;

int main (){
    //int m = mma(throttle, roll, pitch, yaw);
    int motor1 = throttle + roll + pitch + yaw;
    int motor2 = throttle - roll + pitch - yaw;
    int motor3 = throttle - roll - pitch + yaw;
    int motor4 = throttle + roll - pitch - yaw;
    printf("Motor 1: %i\n", motor1);
    printf("Motor 2: %i\n", motor2);
    printf("Motor 3: %i\n", motor3);
    printf("Motor 4: %i\n", motor4);
    return 0;
}
