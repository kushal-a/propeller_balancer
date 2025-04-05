/* --- Generated the 24/3/2025 at 19:45 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. jan. 18 10:20:49 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc -target c -s main -hepts propeller_balancer.ept --- */

#ifndef PROPELLER_BALANCER_TYPES_H
#define PROPELLER_BALANCER_TYPES_H

#include "stdbool.h"
#include "assert.h"
#include "mc_ext_types.h"
static const long Propeller_balancer__frequency = 50;

static const float Propeller_balancer__g = 9.800000;

static const float Propeller_balancer__h = 90.000000;

static const float Propeller_balancer__l = 348.000000;

static const float Propeller_balancer__mass = 1.050000;

static const float Propeller_balancer__inertia = 13500.000000;

static const long Propeller_balancer__pwmMax = 100;

static const long Propeller_balancer__vMax = 100;

static const long Propeller_balancer__sensor_min = 214;

static const long Propeller_balancer__sensor_max = 955;

static const float Propeller_balancer__kp = 0.120000;

static const float Propeller_balancer__kd = 0.000000;

static const float Propeller_balancer__kappa = 0.700000;

static const float Propeller_balancer__alpha_sat = 0.700000;

static const long Propeller_balancer__motor_min[2] = {24, 22};

static const long Propeller_balancer__motor_max[2] = {255, 250};

static const float Propeller_balancer__motor_constant = 1.000000;

#endif // PROPELLER_BALANCER_TYPES_H
