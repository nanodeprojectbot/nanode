
#ifndef _CameraWebServer_AP_H
#define _CameraWebServer_AP_H
#include "esp_camera.h"
#include <WiFi.h>

class Nanode_CameraWebServer_AP
{

public:
  void Nanode_CameraWebServer_AP_Init(void);
  String wifi_name;

private:
 
  char *ssid = "ELEGOO-";
  //char *password = "elegoo2020";
  char *password = "CSCIU310Project2022";
};

#endif
