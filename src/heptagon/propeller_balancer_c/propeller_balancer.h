/* --- Generated the 24/3/2025 at 19:45 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. jan. 18 10:20:49 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc -target c -s main -hepts propeller_balancer.ept --- */

#ifndef PROPELLER_BALANCER_H
#define PROPELLER_BALANCER_H

#include "propeller_balancer_types.h"
#include "mc_ext.h"
typedef struct Propeller_balancer__atan2_out {
  float c;
} Propeller_balancer__atan2_out;

void Propeller_balancer__atan2_step(float a, float b,
                                    Propeller_balancer__atan2_out* _out);

typedef struct Propeller_balancer__sin_out {
  float c;
} Propeller_balancer__sin_out;

void Propeller_balancer__sin_step(float a, Propeller_balancer__sin_out* _out);

typedef struct Propeller_balancer__cos_out {
  float c;
} Propeller_balancer__cos_out;

void Propeller_balancer__cos_step(float a, Propeller_balancer__cos_out* _out);

typedef struct Propeller_balancer__exp_out {
  float c;
} Propeller_balancer__exp_out;

void Propeller_balancer__exp_step(float a, Propeller_balancer__exp_out* _out);

typedef struct Propeller_balancer__sqrt_out {
  float c;
} Propeller_balancer__sqrt_out;

void Propeller_balancer__sqrt_step(float a,
                                   Propeller_balancer__sqrt_out* _out);

typedef struct Propeller_balancer__abs_out {
  float c;
} Propeller_balancer__abs_out;

void Propeller_balancer__abs_step(float a, Propeller_balancer__abs_out* _out);

typedef struct Propeller_balancer__sign_out {
  float c;
} Propeller_balancer__sign_out;

void Propeller_balancer__sign_step(float a,
                                   Propeller_balancer__sign_out* _out);

typedef struct Propeller_balancer__traj_mem {
  float v_6;
  int v_5;
  float v_1;
  int v;
} Propeller_balancer__traj_mem;

typedef struct Propeller_balancer__traj_out {
  float theta;
  float d_theta;
  float dd_theta;
} Propeller_balancer__traj_out;

void Propeller_balancer__traj_reset(Propeller_balancer__traj_mem* self);

void Propeller_balancer__traj_step(Propeller_balancer__traj_out* _out,
                                   Propeller_balancer__traj_mem* self);

typedef struct Propeller_balancer__remapped_sensor_values_out {
  int value;
} Propeller_balancer__remapped_sensor_values_out;

void Propeller_balancer__remapped_sensor_values_step(int raw, int sensor_num,
                                                     Propeller_balancer__remapped_sensor_values_out* _out);

typedef struct Propeller_balancer__sense_out {
  float theta;
} Propeller_balancer__sense_out;

void Propeller_balancer__sense_step(float raw_a,
                                    Propeller_balancer__sense_out* _out);

typedef struct Propeller_balancer__pd_mem {
  float v_14;
  int v;
  Propeller_balancer__traj_mem traj;
} Propeller_balancer__pd_mem;

typedef struct Propeller_balancer__pd_out {
  float pidvalue;
} Propeller_balancer__pd_out;

void Propeller_balancer__pd_reset(Propeller_balancer__pd_mem* self);

void Propeller_balancer__pd_step(float theta,
                                 Propeller_balancer__pd_out* _out,
                                 Propeller_balancer__pd_mem* self);

typedef struct Propeller_balancer__error_thrust_mem {
  Propeller_balancer__pd_mem pd;
} Propeller_balancer__error_thrust_mem;

typedef struct Propeller_balancer__error_thrust_out {
  float error_thrust_diff;
} Propeller_balancer__error_thrust_out;

void Propeller_balancer__error_thrust_reset(Propeller_balancer__error_thrust_mem* self);

void Propeller_balancer__error_thrust_step(float theta,
                                           Propeller_balancer__error_thrust_out* _out,
                                           Propeller_balancer__error_thrust_mem* self);

typedef struct Propeller_balancer__traj_ffw_mem {
  Propeller_balancer__traj_mem traj;
} Propeller_balancer__traj_ffw_mem;

typedef struct Propeller_balancer__traj_ffw_out {
  float ffw_traj_thrust_diff;
} Propeller_balancer__traj_ffw_out;

void Propeller_balancer__traj_ffw_reset(Propeller_balancer__traj_ffw_mem* self);

void Propeller_balancer__traj_ffw_step(Propeller_balancer__traj_ffw_out* _out,
                                       Propeller_balancer__traj_ffw_mem* self);

typedef struct Propeller_balancer__grav_ffw_out {
  float ffw_grav_thrust_diff;
} Propeller_balancer__grav_ffw_out;

void Propeller_balancer__grav_ffw_step(float theta,
                                       Propeller_balancer__grav_ffw_out* _out);

typedef struct Propeller_balancer__ffcontrol_mem {
  Propeller_balancer__error_thrust_mem error_thrust;
  Propeller_balancer__traj_ffw_mem traj_ffw;
} Propeller_balancer__ffcontrol_mem;

typedef struct Propeller_balancer__ffcontrol_out {
  float ffw_thrust_diff;
} Propeller_balancer__ffcontrol_out;

void Propeller_balancer__ffcontrol_reset(Propeller_balancer__ffcontrol_mem* self);

void Propeller_balancer__ffcontrol_step(float theta,
                                        Propeller_balancer__ffcontrol_out* _out,
                                        Propeller_balancer__ffcontrol_mem* self);

typedef struct Propeller_balancer__thrust_diff_saturation_out {
  float thrust_sat;
} Propeller_balancer__thrust_diff_saturation_out;

void Propeller_balancer__thrust_diff_saturation_step(float theta,
                                                     float thrust,
                                                     Propeller_balancer__thrust_diff_saturation_out* _out);

typedef struct Propeller_balancer__interpolate_out {
  float out;
} Propeller_balancer__interpolate_out;

void Propeller_balancer__interpolate_step(float min, float max,
                                          Propeller_balancer__interpolate_out* _out);

typedef struct Propeller_balancer__optimal_thrust_out {
  float u[2];
} Propeller_balancer__optimal_thrust_out;

void Propeller_balancer__optimal_thrust_step(float thrust_diff,
                                             Propeller_balancer__optimal_thrust_out* _out);

typedef struct Propeller_balancer__compute_mem {
  Propeller_balancer__ffcontrol_mem ffcontrol;
} Propeller_balancer__compute_mem;

typedef struct Propeller_balancer__compute_out {
  float u[2];
} Propeller_balancer__compute_out;

void Propeller_balancer__compute_reset(Propeller_balancer__compute_mem* self);

void Propeller_balancer__compute_step(float theta,
                                      Propeller_balancer__compute_out* _out,
                                      Propeller_balancer__compute_mem* self);

typedef struct Propeller_balancer__remapped_motor_values_out {
  int pwm;
} Propeller_balancer__remapped_motor_values_out;

void Propeller_balancer__remapped_motor_values_step(float raw_thrust,
                                                    int motor_num,
                                                    Propeller_balancer__remapped_motor_values_out* _out);

typedef struct Propeller_balancer__actuate_out {
  int pwmL;
  int pwmR;
} Propeller_balancer__actuate_out;

void Propeller_balancer__actuate_step(float u[2],
                                      Propeller_balancer__actuate_out* _out);

typedef struct Propeller_balancer__propeller_balancer_mem {
  Propeller_balancer__compute_mem compute;
} Propeller_balancer__propeller_balancer_mem;

typedef struct Propeller_balancer__propeller_balancer_out {
  int pwmL;
  int pwmR;
} Propeller_balancer__propeller_balancer_out;

void Propeller_balancer__propeller_balancer_reset(Propeller_balancer__propeller_balancer_mem* self);

void Propeller_balancer__propeller_balancer_step(float raw_a,
                                                 Propeller_balancer__propeller_balancer_out* _out,
                                                 Propeller_balancer__propeller_balancer_mem* self);

typedef struct Propeller_balancer__main_mem {
  Propeller_balancer__propeller_balancer_mem propeller_balancer;
} Propeller_balancer__main_mem;

typedef struct Propeller_balancer__main_out {
  int pwmL;
  int pwmR;
} Propeller_balancer__main_out;

void Propeller_balancer__main_reset(Propeller_balancer__main_mem* self);

void Propeller_balancer__main_step(float raw_a,
                                   Propeller_balancer__main_out* _out,
                                   Propeller_balancer__main_mem* self);

#endif // PROPELLER_BALANCER_H
