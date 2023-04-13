#ifndef Nanode_MPU6050_getdata_H_
#define Nanode_MPU6050_getdata_H_
#include <Arduino.h>
class Nanode_MPU6050_getdata
{
public:
  bool Nanode_MPU6050_dveInit(void);
  bool Nanode_MPU6050_calibration(void);
  bool Nanode_MPU6050_dveGetEulerAngles(float *Yaw);

public:

  int16_t gz;

  unsigned long now, lastTime = 0;
  float dt;      
  float agz = 0; 
  long gzo = 0;  
};

extern Nanode_MPU6050_getdata Nanode_MPU6050Getdata;
#endif
