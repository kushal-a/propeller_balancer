#ifndef PB_IMU
#define PB_IMU

extern float RateTheta;

extern float AccX;
extern float AccY;
extern float AccZ;
extern float Theta; 

void gyro_signals();
void init_imu();

#endif