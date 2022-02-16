#include <math.h>

float pitch(float angle)
{
    // This function should be used to change the pitch of the drone
    // by calculating each motor throttle value

    float Mass = 15.0;              // kg
    float MaxPitch = 5.0;           // degrees (CHANGE TO RADIANS?)
    float MotorToRotDist = 0.5;     // meters
    float MassToRotDist = 0.05;     // meters
    float Gravity = 9.807;          // m/s^2
    float TotalThrust = Mass*Gravity;
    float NeutralThrust = TotalThrust/4;
    float NeutralThrottle = 0.0837 * pow(NeutralThrust,0.629);

    // TODO: Add the rest of the code logic and eqns. 
    //       Make sure to add a way to keep the drone 
    //       from over tilting.
}