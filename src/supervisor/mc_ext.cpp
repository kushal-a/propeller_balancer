#include <math.h>
#include <stdlib.h>
#include "mc_ext.h"

void Mc_ext__long_of_float_step(float a, Mc_ext__long_of_float_out *out)
{
  out->o = (long) a;
}

void Mc_ext__float_of_long_step(long a, Mc_ext__float_of_long_out *out)
{
  out->o = (float) a;
}
