#ifndef _WLANSupport_h_
#define _WLANSupport_h_


#include <Arduino.h>



/****************************************************************************************************
                         EXTERN             
*****************************************************************************************************/
extern int httpGETRequest(const char* serverName, String *responseString);
extern void initWiFi(void);
extern void printWifiIP(void);

#endif