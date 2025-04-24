#include "imu/imu.h"
#include "motor/motor.h"

// PINS
#define MOTOR_L 14
#define MOTOR_R 15

#define SDA 17
#define SCL 16

// HARDWARE SPECS

    /// Environment
    #define GRAVITY 10      // in m/s^2 -- acceleration due to gravity
    #define PI 3.14

    // Mechanical structure
    #define L_PP 348        // mm       -- length between propellers
    #define H_COM 90        // mm       -- height of COM above gorund in upright position
    #define INERTIA 0.005   // Kg/m^2   -- Inertia about COM
    #define MASS 1.05       // Kg       -- Mass
    #define KF 1            // in       -- Thrust constant of propellers

    // ESC
    #define ESC_FREQ 50     // in Hz




// CONTROL SPECS
#define KAPPA 0.7           // fraction of weight that is maximum permissible lift
#define ALPHA2 0.7          // fraction of max control input after which saturation kicks in 

// PID
extern int pid_I;
extern int pid_D;
extern int pid_last_e;
extern int pid_dt;
extern float kp;
extern float ki;
extern float kd;


void init_devices();
int run_pid(int timer, int error);
int pid(int error);
int grav_force_diff();
int pid_force_diff(int timer, int error);
int net_force_diff(int timer, int error);
int* actuate_motors(float* thrusts);

