#ifndef MC_EXT_H
#define MC_EXT_H

/* int_of_float */
typedef struct {
  int o;
} Mc_ext__int_of_float_out;

void Mc_ext__int_of_float_step(float a, Mc_ext__int_of_float_out *out);

/* float_of_int */
typedef struct {
  float o;
} Mc_ext__float_of_int_out;

void Mc_ext__float_of_int_step(int a, Mc_ext__float_of_int_out *out);

#endif
