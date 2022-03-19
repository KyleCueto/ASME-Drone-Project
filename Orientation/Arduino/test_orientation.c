# include "orientation.h"
#include <stdio.h>

float angle = 5;
float Throttle1;
float Throttle2;
float Throttle3;
float Throttle4;
int main(){
    Throttle1, Throttle2, Throttle3, Throttle4 = pitch(angle);
    printf("Motor 1: %.3f\n", Throttle1);
    printf("Motor 2: %.3f\n", Throttle2);
    printf("Motor 3: %.3f\n", Throttle3);
    printf("Motor 4: %.3f\n", Throttle4);
    return 0;
}
