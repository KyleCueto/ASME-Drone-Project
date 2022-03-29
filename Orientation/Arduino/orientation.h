
// Motor Mixing Algorithm
int mma(int throttle, int roll, int pitch, int yaw)
{
    /*  This function should be used to change the throttle,
        roll, pitch, and yaw of drone.

        param throttle: throttle pwm signal from remote control
        param roll:     roll pwm signal from remote control
        param pitch:    pitch pwm signal from remote control
        param yaw:      yaw pwm signal from remote control

        TODO: 
    */

    // Motor Mixing Variables 
    int motor1; // Front/Right
    int motor2; // Front/Left
    int motor3; // Back/Right
    int motor4; // Back/Left

    // Motor -> ESC Variables
    int m[0];
    //int m1;
    //int m2;
    //int m3;
    //int m4;
    

    // Motor Mixing Algorithm  TODO: Read what is the maximum pwm value read  from one channel
    motor1 = throttle + roll + pitch + yaw;
    motor2 = throttle - roll + pitch - yaw;
    motor3 = throttle - roll - pitch + yaw;
    motor4 = throttle + roll - pitch - yaw;

    /*// Scale values to write to ESC
    m1 = map(motor1, 1000, 2000, 0, 180);
    m2 = map(motor2, 1000, 2000, 0, 180);
    m3 = map(motor3, 1000, 2000, 0, 180);
    m4 = map(motor4, 1000, 2000, 0, 180);*/

    //test in C
    // Scale values to write to ESC

    m1 = motor1;
    m2 = motor2;
    m3 = motor3;
    m4 = motor4;

    return [m1, m2, m3, m4];
}