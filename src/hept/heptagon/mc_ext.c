#include <math.h>
#include <stdlib.h>
#include "mc_ext.h"

void Mc_ext__int_of_float_step(float a, Mc_ext__int_of_float_out *out)
{
  out->o = (int) a;
}

void Mc_ext__float_of_int_step(int a, Mc_ext__float_of_int_out *out)
{
  out->o = (float) a;
}
