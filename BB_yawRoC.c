/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * BB_yawRoC.c
 *
 * Code generation for function 'BB_yawRoC'
 *
 */

/* Include files */
#include "BB_yawRoC.h"
#include "BB_yawRoC_data.h"
#include "BB_yawRoC_initialize.h"
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

void BB_yawRoC(double percent, double *Throttle1, double *Throttle2,
               double *Throttle3, double *Throttle4)
{
  static const char obj1Value[34] = {
      'T', 'h', 'e', ' ', 'd', 'r', 'o', 'n', 'e', ' ', 'w', 'i',
      'l', 'l', ' ', 'c', 'h', 'a', 'n', 'g', 'e', ' ', 'i', 't',
      's', ' ', 'y', 'a', 'w', ' ', 'a', 't', ':', ' '};
  static const char obj2Value[9] = {' ', 'p', 'e', 'r', 'c',
                                    'e', 'n', 't', '.'};
  double YawRoC;
  int exitg1;
  int formatSpec_size_idx_1;
  int i;
  int resCount;
  char varargin_1_data[67];
  char formatSpec_data[66];
  char st[24];
  char obj2Value_data[23];
  if (!isInitialized_BB_yawRoC) {
    BB_yawRoC_initialize();
  }
  /* Here we are trying to find the individual thrust values for each motor */
  /* using concepts of torque and sum of forces, as well as angular momentum. */
  /* These will be using arbitrary values until drone dimensions and motor data
   */
  /* is provided. */
  /*    This function should be used to indirectly change the throttle values */
  /*    of each motor by outputting how much the individual throttles should */
  /*    change by */
  /* in kg */
  /* m/s^2 */
  /* A positive yaw Rate of Change (RoC) value will have the drone rotate */
  /* counterclockwise, while a negative YawRoC value will have the drone rotate
   */
  /* clockwise */
  do {
    exitg1 = 0;
    YawRoC = percent;
    if ((-100.0 <= percent) && (percent <= 100.0)) {
      resCount = (int)rt_roundd_snf(percent);
      if (resCount == 0) {
        resCount = 1;
        obj2Value_data[0] = '0';
      } else {
        resCount = sprintf(&st[0], "%.16g", (double)resCount);
        if (0 <= resCount - 1) {
          memcpy(&obj2Value_data[0], &st[0], resCount * sizeof(char));
        }
      }
      formatSpec_size_idx_1 = resCount + 43;
      for (i = 0; i < 34; i++) {
        formatSpec_data[i] = obj1Value[i];
      }
      if (0 <= resCount - 1) {
        memcpy(&formatSpec_data[34], &obj2Value_data[0],
               resCount * sizeof(char));
      }
      for (i = 0; i < 9; i++) {
        formatSpec_data[(i + resCount) + 34] = obj2Value[i];
      }
      if (0 <= formatSpec_size_idx_1 - 1) {
        memcpy(&varargin_1_data[0], &formatSpec_data[0],
               formatSpec_size_idx_1 * sizeof(char));
      }
      varargin_1_data[resCount + 43] = '\x00';
      printf("%s\n", &varargin_1_data[0]);
      fflush(stdout);
      exitg1 = 1;
    } else if (percent < -100.0) {
      printf("%s\n",
             "You have inputted a value exceeding -100%, please try again");
      fflush(stdout);
      YawRoC = 0.0;
      exitg1 = 1;
    } else if (percent > 100.0) {
      printf("%s\n",
             "You have inputted a value exceeding 100%, please try again.");
      fflush(stdout);
      YawRoC = 0.0;
      exitg1 = 1;
    } else {
      printf("%s\n",
             "You have inputted an invalid value, please enter a number.");
      fflush(stdout);
    }
  } while (exitg1 == 0);
  /* Newtons */
  /* The Matrix of Thrust values follows with the positions of each motor */
  YawRoC = 0.2 * (YawRoC / 100.0);
  /* Converting thrust (N) to throttle uses the following relation: */
  /* (Throttle %) = 0.0837*(Thrust (N))^0.629 */
  /*    Outputs the CHANGE in throttle */
  *Throttle1 = 0.0837 * rt_powd_snf(YawRoC + 36.776250000000005, 0.629) -
               0.80810422922416436;
  *Throttle2 = 0.0837 * rt_powd_snf(36.776250000000005 - YawRoC, 0.629) -
               0.80810422922416436;
  *Throttle3 = *Throttle2;
  *Throttle4 = *Throttle1;
}

/* End of code generation (BB_yawRoC.c) */
