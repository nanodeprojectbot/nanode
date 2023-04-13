
#ifndef Nanode_ApplicationFunctionSet_xxx0_H_
#define Nanode_ApplicationFunctionSet_xxx0_H_

#include <arduino.h>

class Nanode_ApplicationFunctionSet
{
public:
  void Nanode_ApplicationFunctionSet_Init(void);
  void Nanode_ApplicationFunctionSet_Follow(void);  
  
private:
  volatile uint16_t UltrasoundData_mm; 
  volatile uint16_t UltrasoundData_cm; 
  boolean UltrasoundDetectionStatus = false;
public:
  boolean Nanode_LeaveTheGround = true;
  const int ObstacleDetection = 20;
};
extern Nanode_ApplicationFunctionSet Nanode_Application_FunctionSet;
#endif
