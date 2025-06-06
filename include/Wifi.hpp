#ifndef _WIFI_HPP_
#define _WIFI_HPP_


#include <Arduino.h>



/****************************************************************************************************
                         EXTERN             
*****************************************************************************************************/
extern int httpGETRequest(const char* serverName, String *responseString);
extern void initWiFi(void);
extern void printWifiIP(void);

#endif