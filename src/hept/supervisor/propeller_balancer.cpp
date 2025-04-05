/* --- Generated the 24/3/2025 at 19:45 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. jan. 18 10:20:49 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc -target c -s main -hepts propeller_balancer.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "propeller_balancer.h"

void Propeller_balancer__atan2_step(float a, float b,
                                    Propeller_balancer__atan2_out* _out) {
  _out->c = atan2(a,b);
}

void Propeller_balancer__sin_step(float a, Propeller_balancer__sin_out* _out) {
  _out->c = sin(a);
}

void Propeller_balancer__cos_step(float a, Propeller_balancer__cos_out* _out) {
  _out->c = cos(a);
}

void Propeller_balancer__exp_step(float a, Propeller_balancer__exp_out* _out) {
  _out->c = exp(a);
}

void Propeller_balancer__sqrt_step(float a,
                                   Propeller_balancer__sqrt_out* _out) {
  _out->c = sqrt(a);
}

void Propeller_balancer__abs_step(float a, Propeller_balancer__abs_out* _out) {
  Mc_ext__long_of_float_out Mc_ext__long_of_float_out_st;
  
  long v;
  float c_false;
  float c_true;
  long ck;
  Mc_ext__long_of_float_step(a, &Mc_ext__long_of_float_out_st);
  v = Mc_ext__long_of_float_out_st.o;
  ck = (v>0);
  if (ck) {
    c_true = a;
    _out->c = c_true;
  } else {
    c_false = -(a);
    _out->c = c_false;
  };;
}

void Propeller_balancer__sign_step(float a,
                                   Propeller_balancer__sign_out* _out) {
  Mc_ext__long_of_float_out Mc_ext__long_of_float_out_st;
  
  long v;
  float c_false;
  float c_true;
  long ck;
  Mc_ext__long_of_float_step(a, &Mc_ext__long_of_float_out_st);
  v = Mc_ext__long_of_float_out_st.o;
  ck = (v>0);
  if (ck) {
    c_true = 1.000000;
    _out->c = c_true;
  } else {
    c_false = -1.000000;
    _out->c = c_false;
  };;
}

void Propeller_balancer__traj_reset(Propeller_balancer__traj_mem* self) {
  self->v_5 = true;
  self->v = true;
}

void Propeller_balancer__traj_step(Propeller_balancer__traj_out* _out,
                                   Propeller_balancer__traj_mem* self) {
  Mc_ext__float_of_long_out Mc_ext__float_of_long_out_st;
  
  float v_9;
  float v_8;
  float v_7;
  float v_4;
  float v_3;
  float v_2;
  Mc_ext__float_of_long_step(Propeller_balancer__frequency,
                            &Mc_ext__float_of_long_out_st);
  v_8 = Mc_ext__float_of_long_out_st.o;
  Mc_ext__float_of_long_step(Propeller_balancer__frequency,
                            &Mc_ext__float_of_long_out_st);
  v_3 = Mc_ext__float_of_long_out_st.o;
  _out->theta = 0.000000;
  v_2 = (_out->theta-self->v_1);
  v_4 = (v_2*v_3);
  if (self->v) {
    _out->d_theta = 0.000000;
  } else {
    _out->d_theta = v_4;
  };
  v_7 = (_out->d_theta-self->v_6);
  v_9 = (v_7*v_8);
  if (self->v_5) {
    _out->dd_theta = 0.000000;
  } else {
    _out->dd_theta = v_9;
  };
  self->v_6 = _out->d_theta;
  self->v_5 = false;
  self->v_1 = _out->theta;
  self->v = false;;
}

void Propeller_balancer__remapped_sensor_values_step(long raw, long sensor_num,
                                                     Propeller_balancer__remapped_sensor_values_out* _out) {
  Mc_ext__float_of_long_out Mc_ext__float_of_long_out_st;
  Mc_ext__long_of_float_out Mc_ext__long_of_float_out_st;
  
  float v_13;
  float v_12;
  float v_11;
  long v_10;
  long v;
  long value_false_false;
  long value_false_true;
  long ck_1;
  long value_false;
  long value_true;
  long ck;
  ck = (raw<Propeller_balancer__sensor_min);
  if (ck) {
    value_true = 0;
    _out->value = value_true;
  } else {
    ck_1 = (raw>Propeller_balancer__sensor_max);
    if (ck_1) {
      value_false_true = 1000;
      value_false = value_false_true;
    } else {
      Mc_ext__float_of_long_step(741, &Mc_ext__float_of_long_out_st);
      v_12 = Mc_ext__float_of_long_out_st.o;
      v = (raw-Propeller_balancer__sensor_min);
      v_10 = (1000*v);
      Mc_ext__float_of_long_step(v_10, &Mc_ext__float_of_long_out_st);
      v_11 = Mc_ext__float_of_long_out_st.o;
      v_13 = (v_11/v_12);
      Mc_ext__long_of_float_step(v_13, &Mc_ext__long_of_float_out_st);
      value_false_false = Mc_ext__long_of_float_out_st.o;
      value_false = value_false_false;
    };
    _out->value = value_false;
  };;
}

void Propeller_balancer__sense_step(float raw_a,
                                    Propeller_balancer__sense_out* _out) {
  Propeller_balancer__atan2_out Propeller_balancer__atan2_out_st;
  Propeller_balancer__atan2_step(Propeller_balancer__g, raw_a,
                                 &Propeller_balancer__atan2_out_st);
  _out->theta = Propeller_balancer__atan2_out_st.c;
}

void Propeller_balancer__pd_reset(Propeller_balancer__pd_mem* self) {
  Propeller_balancer__traj_reset(&self->traj);
  self->v = true;
}

void Propeller_balancer__pd_step(float theta,
                                 Propeller_balancer__pd_out* _out,
                                 Propeller_balancer__pd_mem* self) {
  Propeller_balancer__traj_out Propeller_balancer__traj_out_st;
  
  float v_17;
  float v_16;
  float v_15;
  float setpolong;
  float a;
  float b;
  float error;
  float p;
  float d;
  Propeller_balancer__traj_step(&Propeller_balancer__traj_out_st, &self->traj);
  setpolong = Propeller_balancer__traj_out_st.theta;
  a = Propeller_balancer__traj_out_st.d_theta;
  b = Propeller_balancer__traj_out_st.dd_theta;
  error = (theta-setpolong);
  v_15 = (error-self->v_14);
  if (self->v) {
    d = 0.000000;
  } else {
    d = v_15;
  };
  v_17 = (Propeller_balancer__kd*d);
  p = error;
  v_16 = (Propeller_balancer__kp*p);
  _out->pidvalue = (v_16+v_17);
  self->v_14 = error;
  self->v = false;;
}

void Propeller_balancer__error_thrust_reset(Propeller_balancer__error_thrust_mem* self) {
  Propeller_balancer__pd_reset(&self->pd);
}

void Propeller_balancer__error_thrust_step(float theta,
                                           Propeller_balancer__error_thrust_out* _out,
                                           Propeller_balancer__error_thrust_mem* self) {
  Propeller_balancer__pd_out Propeller_balancer__pd_out_st;
  
  float v;
  float pd_out;
  Propeller_balancer__pd_step(theta, &Propeller_balancer__pd_out_st,
                              &self->pd);
  pd_out = Propeller_balancer__pd_out_st.pidvalue;
  v = (pd_out*77.586207);
  _out->error_thrust_diff = (0.000000-v);;
}

void Propeller_balancer__traj_ffw_reset(Propeller_balancer__traj_ffw_mem* self) {
  Propeller_balancer__traj_reset(&self->traj);
}

void Propeller_balancer__traj_ffw_step(Propeller_balancer__traj_ffw_out* _out,
                                       Propeller_balancer__traj_ffw_mem* self) {
  Propeller_balancer__traj_out Propeller_balancer__traj_out_st;
  
  float theta_t;
  float d_theta_t;
  float dd_theta_t;
  Propeller_balancer__traj_step(&Propeller_balancer__traj_out_st, &self->traj);
  theta_t = Propeller_balancer__traj_out_st.theta;
  d_theta_t = Propeller_balancer__traj_out_st.d_theta;
  dd_theta_t = Propeller_balancer__traj_out_st.dd_theta;
  _out->ffw_traj_thrust_diff = (dd_theta_t*77.586207);;
}

void Propeller_balancer__grav_ffw_step(float theta,
                                       Propeller_balancer__grav_ffw_out* _out) {
  Propeller_balancer__sin_out Propeller_balancer__sin_out_st;
  
  float v_19;
  float v_18;
  float v;
  Propeller_balancer__sin_step(theta, &Propeller_balancer__sin_out_st);
  v = Propeller_balancer__sin_out_st.c;
  v_18 = (10.290000*v);
  v_19 = (0.517241*v_18);
  _out->ffw_grav_thrust_diff = (0.000000-v_19);;
}

void Propeller_balancer__ffcontrol_reset(Propeller_balancer__ffcontrol_mem* self) {
  Propeller_balancer__traj_ffw_reset(&self->traj_ffw);
  Propeller_balancer__error_thrust_reset(&self->error_thrust);
}

void Propeller_balancer__ffcontrol_step(float theta,
                                        Propeller_balancer__ffcontrol_out* _out,
                                        Propeller_balancer__ffcontrol_mem* self) {
  Propeller_balancer__error_thrust_out Propeller_balancer__error_thrust_out_st;
  Propeller_balancer__grav_ffw_out Propeller_balancer__grav_ffw_out_st;
  Propeller_balancer__traj_ffw_out Propeller_balancer__traj_ffw_out_st;
  
  float v_22;
  float v_21;
  float v_20;
  float v;
  Propeller_balancer__grav_ffw_step(theta,
                                    &Propeller_balancer__grav_ffw_out_st);
  v_22 = Propeller_balancer__grav_ffw_out_st.ffw_grav_thrust_diff;
  Propeller_balancer__traj_ffw_step(&Propeller_balancer__traj_ffw_out_st,
                                    &self->traj_ffw);
  v_20 = Propeller_balancer__traj_ffw_out_st.ffw_traj_thrust_diff;
  Propeller_balancer__error_thrust_step(theta,
                                        &Propeller_balancer__error_thrust_out_st,
                                        &self->error_thrust);
  v = Propeller_balancer__error_thrust_out_st.error_thrust_diff;
  v_21 = (v+v_20);
  _out->ffw_thrust_diff = (v_21+v_22);;
}

void Propeller_balancer__thrust_diff_saturation_step(float theta,
                                                     float thrust,
                                                     Propeller_balancer__thrust_diff_saturation_out* _out) {
  Propeller_balancer__sign_out Propeller_balancer__sign_out_st;
  Propeller_balancer__cos_out Propeller_balancer__cos_out_st;
  Propeller_balancer__exp_out Propeller_balancer__exp_out_st;
  Mc_ext__long_of_float_out Mc_ext__long_of_float_out_st;
  Propeller_balancer__abs_out Propeller_balancer__abs_out_st;
  
  float v_30;
  float v_29;
  float v_28;
  float v_27;
  float v_26;
  float v_25;
  long v_32;
  float v_31;
  float thrust_sat_false;
  float thrust_sat_true;
  long ck;
  float v_24;
  float v_23;
  float v;
  float um;
  float r;
  Propeller_balancer__cos_step(theta, &Propeller_balancer__cos_out_st);
  v = Propeller_balancer__cos_out_st.c;
  v_23 = (thrust*v);
  Propeller_balancer__abs_step(v_23, &Propeller_balancer__abs_out_st);
  v_24 = Propeller_balancer__abs_out_st.c;
  um = 7.203000;
  r = (v_24/um);
  v_31 = (r-Propeller_balancer__alpha_sat);
  Mc_ext__long_of_float_step(v_31, &Mc_ext__long_of_float_out_st);
  v_32 = Mc_ext__long_of_float_out_st.o;
  ck = (v_32<0);
  if (ck) {
    thrust_sat_true = thrust;
    _out->thrust_sat = thrust_sat_true;
  } else {
    v_26 = (Propeller_balancer__alpha_sat-r);
    v_27 = (v_26/0.300000);
    Propeller_balancer__exp_step(v_27, &Propeller_balancer__exp_out_st);
    v_28 = Propeller_balancer__exp_out_st.c;
    v_29 = (0.300000*v_28);
    v_30 = (1.000000-v_29);
    Propeller_balancer__sign_step(thrust, &Propeller_balancer__sign_out_st);
    v_25 = Propeller_balancer__sign_out_st.c;
    thrust_sat_false = (v_25*v_30);
    _out->thrust_sat = thrust_sat_false;
  };;
}

void Propeller_balancer__longerpolate_step(float min, float max,
                                          Propeller_balancer__longerpolate_out* _out) {
  
  float v_33;
  float v;
  float ratio;
  v = (max-min);
  ratio = 0.450000;
  v_33 = (ratio*v);
  _out->out = (min+v_33);;
}

void Propeller_balancer__optimal_thrust_step(float thrust_diff,
                                             Propeller_balancer__optimal_thrust_out* _out) {
  Propeller_balancer__longerpolate_out Propeller_balancer__longerpolate_out_st;
  Mc_ext__long_of_float_out Mc_ext__long_of_float_out_st;
  
  long v;
  float p_min_false[2];
  float p_min_true[2];
  long ck;
  float v_37;
  float v_36;
  float v_35;
  float v_34;
  float p_min[2];
  float p_max[2];
  float um;
  um = 7.203000;
  v_36 = (um+thrust_diff);
  v_37 = (0.500000*v_36);
  v_34 = (um-thrust_diff);
  v_35 = (0.500000*v_34);
  Mc_ext__long_of_float_step(thrust_diff, &Mc_ext__long_of_float_out_st);
  v = Mc_ext__long_of_float_out_st.o;
  ck = (v>0);
  p_max[0] = v_35;
  p_max[1] = v_37;
  if (ck) {
    p_min_true[0] = 0.000000;
    p_min_true[1] = thrust_diff;
    {
      long _1;
      for (_1 = 0; _1 < 2; ++_1) {
        p_min[_1] = p_min_true[_1];
      }
    };
  } else {
    p_min_false[0] = thrust_diff;
    p_min_false[1] = 0.000000;
    {
      long _2;
      for (_2 = 0; _2 < 2; ++_2) {
        p_min[_2] = p_min_false[_2];
      }
    };
  };
  {
    long i;
    for (i = 0; i < 2; ++i) {
      Propeller_balancer__longerpolate_step(p_min[i], p_max[i],
                                           &Propeller_balancer__longerpolate_out_st);
      _out->u[i] = Propeller_balancer__longerpolate_out_st.out;
    }
  };;
}

void Propeller_balancer__compute_reset(Propeller_balancer__compute_mem* self) {
  Propeller_balancer__ffcontrol_reset(&self->ffcontrol);
}

void Propeller_balancer__compute_step(float theta,
                                      Propeller_balancer__compute_out* _out,
                                      Propeller_balancer__compute_mem* self) {
  Propeller_balancer__ffcontrol_out Propeller_balancer__ffcontrol_out_st;
  Propeller_balancer__optimal_thrust_out Propeller_balancer__optimal_thrust_out_st;
  Propeller_balancer__thrust_diff_saturation_out Propeller_balancer__thrust_diff_saturation_out_st;
  
  float ffw;
  float thrust_sat;
  Propeller_balancer__ffcontrol_step(theta,
                                     &Propeller_balancer__ffcontrol_out_st,
                                     &self->ffcontrol);
  ffw = Propeller_balancer__ffcontrol_out_st.ffw_thrust_diff;
  Propeller_balancer__thrust_diff_saturation_step(theta, ffw,
                                                  &Propeller_balancer__thrust_diff_saturation_out_st);
  thrust_sat = Propeller_balancer__thrust_diff_saturation_out_st.thrust_sat;
  Propeller_balancer__optimal_thrust_step(thrust_sat,
                                          &Propeller_balancer__optimal_thrust_out_st);
  {
    long _3;
    for (_3 = 0; _3 < 2; ++_3) {
      _out->u[_3] = Propeller_balancer__optimal_thrust_out_st.u[_3];
    }
  };;
}

void Propeller_balancer__remapped_motor_values_step(float raw_thrust,
                                                    long motor_num,
                                                    Propeller_balancer__remapped_motor_values_out* _out) {
  Propeller_balancer__sqrt_out Propeller_balancer__sqrt_out_st;
  Mc_ext__long_of_float_out Mc_ext__long_of_float_out_st;
  
  long pwm_false;
  long pwm_true;
  long ck;
  long v_40;
  long v_39;
  long v_38;
  long v;
  float raw_vel;
  float raw_vel_sq;
  long min_m;
  long max_m;
  long raw_pwm;
  v_40 = 250;
  if (((motor_num<2)&&(0<=motor_num))) {
    max_m = Propeller_balancer__motor_max[motor_num];
  } else {
    max_m = v_40;
  };
  v_39 = 22;
  if (((motor_num<2)&&(0<=motor_num))) {
    min_m = Propeller_balancer__motor_min[motor_num];
  } else {
    min_m = v_39;
  };
  raw_vel_sq = (raw_thrust/Propeller_balancer__motor_constant);
  Propeller_balancer__sqrt_step(raw_vel_sq, &Propeller_balancer__sqrt_out_st);
  raw_vel = Propeller_balancer__sqrt_out_st.c;
  Mc_ext__long_of_float_step(raw_vel, &Mc_ext__long_of_float_out_st);
  v = Mc_ext__long_of_float_out_st.o;
  v_38 = (Propeller_balancer__pwmMax*v);
  raw_pwm = (v_38/Propeller_balancer__vMax);
  ck = (raw_pwm>min_m);
  if (ck) {
    pwm_true = raw_pwm;
    _out->pwm = pwm_true;
  } else {
    pwm_false = 0;
    _out->pwm = pwm_false;
  };;
}

void Propeller_balancer__actuate_step(float u[2],
                                      Propeller_balancer__actuate_out* _out) {
  Propeller_balancer__remapped_motor_values_out Propeller_balancer__remapped_motor_values_out_st;
  
  long v_41;
  long v;
  long pwm[2];
  {
    long i;
    for (i = 0; i < 2; ++i) {
      Propeller_balancer__remapped_motor_values_step(u[i], i,
                                                     &Propeller_balancer__remapped_motor_values_out_st);
      pwm[i] = Propeller_balancer__remapped_motor_values_out_st.pwm;
    }
  };
  v_41 = pwm[1];
  v = pwm[0];
  _out->pwmR = v_41;
  _out->pwmL = v;;
}

void Propeller_balancer__propeller_balancer_reset(Propeller_balancer__propeller_balancer_mem* self) {
  Propeller_balancer__compute_reset(&self->compute);
}

void Propeller_balancer__propeller_balancer_step(float raw_a,
                                                 Propeller_balancer__propeller_balancer_out* _out,
                                                 Propeller_balancer__propeller_balancer_mem* self) {
  Propeller_balancer__actuate_out Propeller_balancer__actuate_out_st;
  Propeller_balancer__compute_out Propeller_balancer__compute_out_st;
  Propeller_balancer__sense_out Propeller_balancer__sense_out_st;
  
  float theta;
  float u[2];
  Propeller_balancer__sense_step(raw_a, &Propeller_balancer__sense_out_st);
  theta = Propeller_balancer__sense_out_st.theta;
  Propeller_balancer__compute_step(theta,
                                   &Propeller_balancer__compute_out_st,
                                   &self->compute);
  {
    long _4;
    for (_4 = 0; _4 < 2; ++_4) {
      u[_4] = Propeller_balancer__compute_out_st.u[_4];
    }
  };
  Propeller_balancer__actuate_step(u, &Propeller_balancer__actuate_out_st);
  _out->pwmL = Propeller_balancer__actuate_out_st.pwmL;
  _out->pwmR = Propeller_balancer__actuate_out_st.pwmR;;
}

void Propeller_balancer__main_reset(Propeller_balancer__main_mem* self) {
  Propeller_balancer__propeller_balancer_reset(&self->propeller_balancer);
}

void Propeller_balancer__main_step(float raw_a,
                                   Propeller_balancer__main_out* _out,
                                   Propeller_balancer__main_mem* self) {
  Propeller_balancer__propeller_balancer_out Propeller_balancer__propeller_balancer_out_st;
  Propeller_balancer__propeller_balancer_step(raw_a,
                                              &Propeller_balancer__propeller_balancer_out_st,
                                              &self->propeller_balancer);
  _out->pwmL = Propeller_balancer__propeller_balancer_out_st.pwmL;
  _out->pwmR = Propeller_balancer__propeller_balancer_out_st.pwmR;
}

