
#include <hardwareSerial.h>
#include <stdio.h>
#include <string.h>
#include "Nanode_ApplicationFunctionSet_xxx0.h"
#include "Nanode_DeviceDriverSet_xxx0.h"

#include "ArduinoJson-v6.11.1.h" //ArduinoJson
#include "Nanode_MPU6050_getdata.h"

#define _is_print 1
#define _Test_print 0

Nanode_ApplicationFunctionSet Nanode_Application_FunctionSet;


Nanode_MPU6050_getdata AppMPU6050getdata;
NanodeDeviceDriverSet_Motor AppMotor;
DeviceDriverSet_ULTRASONIC AppULTRASONIC;
DeviceDriverSet_Servo AppServo;

static boolean
function_xxx(long x, long s, long e) //f(x)
{
  if (s <= x && x <= e)
    return true;
  else
    return false;
}


enum NanodeMotionControl
{
  Forward,       
  Backward,      
  Left,          
  Right,         
  LeftForward,   
  LeftBackward,  
  RightForward,  
  RightBackward, 
  stop_it        
};           


enum NanodeFunctionalModel
{
  Standby_mode,           
  TraceBased_mode,        
  ObstacleAvoidance_mode, 
  Follow_mode,            
  Rocker_mode,            
};


struct Application_xxx
{
  NanodeMotionControl Motion_Control;
  NanodeFunctionalModel Functional_Mode;
  unsigned long CMD_NanodeControl_Millis;
  unsigned long CMD_LightingControl_Millis;
};
Application_xxx Application_Nanodexxx0;

bool Nanode_NanodeLeaveTheGround(void);
void Nanode_NanodeLinearMotionControl(NanodeMotionControl direction, uint8_t directionRecord, uint8_t speed, uint8_t Kp, uint8_t UpperLimit);
void Nanode_NanodeMotionControl(NanodeMotionControl direction, uint8_t is_speed);

void Nanode_ApplicationFunctionSet::Nanode_ApplicationFunctionSet_Init(void)
{
  bool res_error = true;
  Serial.begin(9600);
  AppMotor.NanodeDeviceDriverSet_Motor_Init();
  AppULTRASONIC.DeviceDriverSet_ULTRASONIC_Init();
  res_error = AppMPU6050getdata.Nanode_MPU6050_dveInit();
  AppMPU6050getdata.Nanode_MPU6050_calibration();
  AppServo.DeviceDriverSet_Servo_Init(90);

  while (Serial.read() >= 0)
  {
    
  }
  delay(2000);
  Application_Nanodexxx0.Functional_Mode = Follow_mode;
}



static void Nanode_NanodeLinearMotionControl(NanodeMotionControl direction, uint8_t directionRecord, uint8_t speed, uint8_t Kp, uint8_t UpperLimit)
{
  static float Yaw; 
  static float yaw_So = 0;
  static uint8_t en = 110;
  static unsigned long is_time;
  if (en != directionRecord || millis() - is_time > 10)
  {
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_void, /*speed_A*/ 0,
                                           /*direction_B*/ direction_void, /*speed_B*/ 0, /*controlED*/ control_enable); //Motor control
    AppMPU6050getdata.Nanode_MPU6050_dveGetEulerAngles(&Yaw);
    is_time = millis();
  }
 
  if (en != directionRecord || Nanode_Application_FunctionSet.Nanode_LeaveTheGround == false)
  {
    en = directionRecord;
    yaw_So = Yaw;
  }
  
  int R = (Yaw - yaw_So) * Kp + speed;
  if (R > UpperLimit)
  {
    R = UpperLimit;
  }
  else if (R < 10)
  {
    R = 10;
  }
  int L = (yaw_So - Yaw) * Kp + speed;
  if (L > UpperLimit)
  {
    L = UpperLimit;
  }
  else if (L < 10)
  {
    L = 10;
  }
  if (direction == Forward) 
  {
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_just, /*speed_A*/ R,
                                           /*direction_B*/ direction_just, /*speed_B*/ L, /*controlED*/ control_enable);
  }
  else if (direction == Backward) 
  {
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ L,
                                           /*direction_B*/ direction_back, /*speed_B*/ R, /*controlED*/ control_enable);
  }
}

static void Nanode_NanodeMotionControl(NanodeMotionControl direction, uint8_t is_speed)
{
  Nanode_Application_FunctionSet;
  static uint8_t directionRecord = 0;
  uint8_t Kp, UpperLimit;
  uint8_t speed = is_speed;


    Kp = 2;
    UpperLimit = 180;

  switch (direction)
  {
  case 
      Forward:
    
    if (Application_Nanodexxx0.Functional_Mode == TraceBased_mode)
    {
      AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_just, /*speed_A*/ speed,
                                             /*direction_B*/ direction_just, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    }
    else
    { 
      Nanode_NanodeLinearMotionControl(Forward, directionRecord, speed, Kp, UpperLimit);
      directionRecord = 1;
    }

    break;
  case  Backward:
    
    if (Application_Nanodexxx0.Functional_Mode == TraceBased_mode)
    {
      AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ speed,
                                             /*direction_B*/ direction_back, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    }
    else
    { 
      Nanode_NanodeLinearMotionControl(Backward, directionRecord, speed, Kp, UpperLimit);
      directionRecord = 2;
    }

    break;
  case  Left:
    
    directionRecord = 3;
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_just, /*speed_A*/ speed,
                                           /*direction_B*/ direction_back, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case  Right:
    
    directionRecord = 4;
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ speed,
                                           /*direction_B*/ direction_just, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case  LeftForward:
    
    directionRecord = 5;
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_just, /*speed_A*/ speed,
                                           /*direction_B*/ direction_just, /*speed_B*/ speed / 2, /*controlED*/ control_enable); //Motor control
    break;
  case  LeftBackward:
    
    directionRecord = 6;
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ speed,
                                           /*direction_B*/ direction_back, /*speed_B*/ speed / 2, /*controlED*/ control_enable); //Motor control
    break;
  case  RightForward:
    
    directionRecord = 7;
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_just, /*speed_A*/ speed / 2,
                                           /*direction_B*/ direction_just, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case  RightBackward:
    
    directionRecord = 8;
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ speed / 2,
                                           /*direction_B*/ direction_back, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case  stop_it:
    
    directionRecord = 9;
    AppMotor.NanodeDeviceDriverSet_Motor_control(/*direction_A*/ direction_void, /*speed_A*/ 0,
                                           /*direction_B*/ direction_void, /*speed_B*/ 0, /*controlED*/ control_enable); //Motor control
    break;
  default:
    directionRecord = 10;
    break;
  }
}

void Nanode_ApplicationFunctionSet::Nanode_ApplicationFunctionSet_Follow(void)
{
  static uint16_t ULTRASONIC_Get = 0;
  static unsigned long ULTRASONIC_time = 0;
  static uint8_t Position_Servo = 1;
  static uint8_t timestamp = 3;
  static uint8_t OneCycle = 1;
  if (Application_Nanodexxx0.Functional_Mode == Follow_mode)
  {

    if (Nanode_LeaveTheGround == false)
    {
      Nanode_NanodeMotionControl(stop_it, 0);
      return;
    }
    AppULTRASONIC.DeviceDriverSet_ULTRASONIC_Get(&ULTRASONIC_Get );
    if (false == function_xxx(ULTRASONIC_Get, 0, 20)) 
    {
      Nanode_NanodeMotionControl(stop_it, 0);
      static unsigned long time_Servo = 0;
      static uint8_t Position_Servo_xx = 0;

      if (timestamp == 3)
      {
        if (Position_Servo_xx != Position_Servo) 
        {
          Position_Servo_xx = Position_Servo; 

          if (Position_Servo == 1)
          {
            time_Servo = millis();
            AppServo.DeviceDriverSet_Servo_control(80 );
          }
          else if (Position_Servo == 2)
          {
            time_Servo = millis();
            AppServo.DeviceDriverSet_Servo_control(20 );
          }
          else if (Position_Servo == 3)
          {
            time_Servo = millis();
            AppServo.DeviceDriverSet_Servo_control(80 );
          }
          else if (Position_Servo == 4)
          {
            time_Servo = millis();
            AppServo.DeviceDriverSet_Servo_control(150 );
          }
        }
      }
      else
      {
        if (timestamp == 1)
        {
          timestamp = 2;
          time_Servo = millis();
        }
      }
      if (millis() - time_Servo > 1000) 
      {
        timestamp = 3;
        Position_Servo += 1;
        OneCycle += 1;
        if (OneCycle > 4)
        {
          Position_Servo = 1;
          OneCycle = 5;
        }
      }
    }
    else
    {
      OneCycle = 1;
      timestamp = 1;
      if ((Position_Servo == 1))
      { 
        Nanode_NanodeMotionControl(Forward, 100);
      }
      else if ((Position_Servo == 2))
      { 
        Nanode_NanodeMotionControl(Right, 150);
      }
      else if ((Position_Servo == 3))
      {
        
        Nanode_NanodeMotionControl(Forward, 100);
      }
      else if ((Position_Servo == 4))
      { 
        Nanode_NanodeMotionControl(Left, 150);
      }
    }
  }
  else
  {
    ULTRASONIC_Get = 0;
    ULTRASONIC_time = 0;
  }
}
