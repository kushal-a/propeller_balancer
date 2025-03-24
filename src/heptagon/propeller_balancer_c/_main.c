/* --- Generated the 24/3/2025 at 19:45 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. jan. 18 10:20:49 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc -target c -s main -hepts propeller_balancer.ept --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "_main.h"

Propeller_balancer__main_mem mem;
int main(int argc, char** argv) {
  int step_c;
  int step_max;
  float raw_a;
  Propeller_balancer__main_out _res;
  step_c = 0;
  step_max = 0;
  if ((argc==2)) {
    step_max = atoi(argv[1]);
  };
  Propeller_balancer__main_reset(&mem);
  while ((!(step_max)||(step_c<step_max))) {
    step_c = (step_c+1);
    
    if ((scanf("%f", &raw_a)==EOF)) {
      return 0;
    };;
    Propeller_balancer__main_step(raw_a, &_res, &mem);
    printf("%d\n", _res.pwmL);
    printf("%d\n", _res.pwmR);
    fflush(stdout);
  };
  return 0;
}

