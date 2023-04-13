
#ifndef Nanode_DeviceDriverSet_xxx0_H_
#define Nanode_DeviceDriverSet_xxx0_H_
#include <arduino.h>

/*Motor*/
class NanodeDeviceDriverSet_Motor
{
public:
  void NanodeDeviceDriverSet_Motor_Init(void);
#if _Test_DeviceDriverSet
  void NanodeDeviceDriverSet_Motor_Test(void);
#endif
  void NanodeDeviceDriverSet_Motor_control(boolean direction_A, uint8_t speed_A, 
                                     boolean direction_B, uint8_t speed_B, 
                                     boolean controlED                     
  );                                                                       
private:
#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3

public:
#define speed_Max 255
#define direction_just true
#define direction_back false
#define direction_void 3

#define Duration_enable true
#define Duration_disable false
#define control_enable true
#define control_disable false
};
/*ULTRASONIC*/

//#include <NewPing.h>
class DeviceDriverSet_ULTRASONIC
{
public:
  void DeviceDriverSet_ULTRASONIC_Init(void);
#if _Test_DeviceDriverSet
  void DeviceDriverSet_ULTRASONIC_Test(void);
#endif
  void DeviceDriverSet_ULTRASONIC_Get(uint16_t *ULTRASONIC_Get /*out*/);

private:
#define TRIG_PIN 13      
#define ECHO_PIN 12      
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
};

/*Servo*/
#include <Servo.h>
class DeviceDriverSet_Servo
{
public:
  void DeviceDriverSet_Servo_Init(unsigned int Position_angle);
#if _Test_DeviceDriverSet
  void DeviceDriverSet_Servo_Test(void);
#endif
  void DeviceDriverSet_Servo_control(unsigned int Position_angle);

private:
#define PIN_Servo_z 10
};
#endif
