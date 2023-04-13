
#include "Nanode_DeviceDriverSet_xxx0.h"
#include "Nanode_ApplicationFunctionSet_xxx0.h"

void setup()
{
  // Setup Code
  Nanode_Application_FunctionSet.Nanode_ApplicationFunctionSet_Init();
}

void loop()
{
 Nanode_Application_FunctionSet.Nanode_ApplicationFunctionSet_Follow();
}
