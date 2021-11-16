/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * BB_changeRoll.c
 *
 * Code generation for function 'BB_changeRoll'
 *
 */

/* Include files */
#include "BB_changeRoll.h"
#include "BB_changeRoll_data.h"
#include "BB_changeRoll_initialize.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

static double rt_roundd_snf(double u);

/* Function Definitions */
static double rt_powd_snf(double u0, double u1)
{
  double d;
  double d1;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

void BB_changeRoll(double angle, double *Throttle1, double *Throttle2,
                   double *Throttle3, double *Throttle4)
{
  static const char obj1Value[36] = {
      'T', 'h', 'e', ' ', 'd', 'r', 'o', 'n', 'e', ' ', 'w', 'i',
      'l', 'l', ' ', 't', 'r', 'a', 'v', 'e', 'l', ' ', 'a', 't',
      ' ', 'a', ' ', 'R', 'o', 'l', 'l', ' ', 'o', 'f', ':', ' '};
  static const char obj2Value[9] = {' ', 'd', 'e', 'g', 'r',
                                    'e', 'e', 's', '.'};
  double HorizAcc;
  double Motor2_tmp;
  double Roll;
  int formatSpec_size_idx_1;
  int i;
  int resCount;
  char varargin_1_data[69];
  char formatSpec_data[68];
  char st[24];
  char obj2Value_data[23];
  if (!isInitialized_BB_changeRoll) {
    BB_changeRoll_initialize();
  }
  /* Here we are trying to find the individual thrust values for each motor */
  /* using concepts of torque and sum of forces. */
  /* These will be using arbitrary values until drone dimensions and motor data
   */
  /* is provided. */
  /*    This function should be used to indirectly change the throttle values */
  /*    of each motor by outputting how much the individual throttles should */
  /*    change by */
  /* in kg */
  /*  MaxAcc = 0.9; m/s^2 */
  /* degrees (change to radians) */
  /* meters */
  /* meters */
  /* m/s^2 */
  Roll = angle;
  if ((angle <= 5.0) && (angle >= -5.0)) {
    resCount = (int)rt_roundd_snf(angle);
    if (resCount == 0) {
      resCount = 1;
      obj2Value_data[0] = '0';
    } else {
      resCount = sprintf(&st[0], "%.16g", (double)resCount);
      if (0 <= resCount - 1) {
        memcpy(&obj2Value_data[0], &st[0], resCount * sizeof(char));
      }
    }
    formatSpec_size_idx_1 = resCount + 45;
    for (i = 0; i < 36; i++) {
      formatSpec_data[i] = obj1Value[i];
    }
    if (0 <= resCount - 1) {
      memcpy(&formatSpec_data[36], &obj2Value_data[0], resCount * sizeof(char));
    }
    for (i = 0; i < 9; i++) {
      formatSpec_data[(i + resCount) + 36] = obj2Value[i];
    }
    if (0 <= formatSpec_size_idx_1 - 1) {
      memcpy(&varargin_1_data[0], &formatSpec_data[0],
             formatSpec_size_idx_1 * sizeof(char));
    }
    varargin_1_data[resCount + 45] = '\x00';
    printf("%s\n", &varargin_1_data[0]);
    fflush(stdout);
  } else if (angle < -5.0) {
    printf("%s\n", "You have inputted a value exceeding negative Max Roll, "
                   "please try again.");
    fflush(stdout);
    Roll = 0.0;
  } else if (angle > 5.0) {
    printf("%s\n", "You have inputted a value exceeding positive Max Roll, "
                   "please try again.");
    fflush(stdout);
    Roll = 0.0;
  } else {
    printf("%s\n",
           "You have inputted an invalid value, please enter a number.");
    fflush(stdout);
    Roll = 0.0;
  }
  Roll = (90.0 - Roll) * 3.1415926535897931 / 180.0;
  HorizAcc = 9.807 / tan(Roll);
  /* This if/then statement is just figuring out what motors to calculate */
  /* specific values for. */
  /* The Matrix of Thrust values follows with the positions of each motor */
  Motor2_tmp = cos(Roll);
  Roll = 15.0 * HorizAcc / 4.0 * (1.0 / Motor2_tmp + 0.05 * sin(Roll) / 0.5);
  /* Converting thrust (N) to throttle uses the following relation: */
  /* (Throttle %) = 0.0837*(Thrust (N))^0.629 */
  /*    Outputs the CHANGE in throttle */
  *Throttle1 =
      0.0837 * rt_powd_snf((15.0 * HorizAcc / Motor2_tmp - (Roll + Roll)) / 2.0,
                           0.629) -
      0.80810422922416436;
  *Throttle2 = 0.0837 * rt_powd_snf(Roll, 0.629) - 0.80810422922416436;
  *Throttle3 = *Throttle1;
  *Throttle4 = *Throttle2;
}

/* End of code generation (BB_changeRoll.c) */
