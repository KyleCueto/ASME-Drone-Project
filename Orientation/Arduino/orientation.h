#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

float pitch(float angle)
{
    /*  This function should be used to change the pitch of the drone
        by calculating each motor throttle value
        param angle: pitch angle from remote control

        TODO: Find the correct mass of drone
              Find what type of angle numeric come from remote control
              since it will most likely not be an exact angle in degrees
    */

    float Mass = 15.0;              // kg
    float MaxPitch = 5.0;           // degrees 
    float MotorToRotDist = 0.5;     // meters
    float MassToRotDist = 0.05;     // meters
    float Gravity = 9.807;          // m/s^2
    float TotalThrust = Mass*Gravity;
    float NeutralThrust = TotalThrust/4;
    float NeutralThrottle = 0.0837 * pow(NeutralThrust,0.629);
    float pi = 3.14159;
    float Pitch = (angle*pi)/180;   // convert to radians

    // Check pitch angle threshold
    if (Pitch >= -MaxPitch && Pitch <= MaxPitch){
        printf("The drone will travel at a pitch of: %.6f\n", Pitch); //degrees
    }
    else if(Pitch < -MaxPitch){
        printf("You have inputted a value exceeding the negative Max Pitch \n");
        Pitch = -MaxPitch;
    }
    else if(Pitch > MaxPitch){
        printf("You have inputted a value exceeding the Max Pitch \n");
        Pitch = MaxPitch;
    }
    
    float TiltAngle = (90-Pitch)*pi/180;
    float HorizAcc = Gravity/tan(TiltAngle);

    float Motor3 = (Mass*HorizAcc/4)*(1/cos(TiltAngle) + MassToRotDist*sin(TiltAngle)/MotorToRotDist);
    float Motor4 = Motor3;
    float Motor1 = ((Mass*HorizAcc)/cos(TiltAngle) - (Motor3 + Motor4))/2;
    float Motor2 = Motor1;
    // We'll need to know the mapping of Motor 1-4 to match code

    /*  Converting thrust (N) to throttle uses the following relation:
        (Throttle %) = 0.0837*(Thrust (N))^0.629
        Outputs the CHANGE in throttle
    */

    float Throttle1 = 0.0837*pow(Motor1,0.629) - NeutralThrottle;
    float Throttle2 = 0.0837*pow(Motor2,0.629) - NeutralThrottle;
    float Throttle3 = 0.0837*pow(Motor3,0.629) - NeutralThrottle;
    float Throttle4 = 0.0837*pow(Motor4,0.629) - NeutralThrottle;

    return Throttle1, Throttle2, Throttle3, Throttle4;
}