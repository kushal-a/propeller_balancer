#ifndef MC_EXT_H
#define MC_EXT_H

/* long_of_float */
typedef struct {
  long o;
} Mc_ext__long_of_float_out;

void Mc_ext__long_of_float_step(float a, Mc_ext__long_of_float_out *out);

/* float_of_long */
typedef struct {
  float o;
} Mc_ext__float_of_long_out;

void Mc_ext__float_of_long_step(long a, Mc_ext__float_of_long_out *out);

#endif
