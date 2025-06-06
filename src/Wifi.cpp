#include <Arduino.h>
#include <WiFi.h>

#include <HTTPClient.h>
#include "Wifi.hpp"

#define AP_WIFI_SSID "Led_Cube"
#define AP_WIFI_PW "#Led_Cube#"


/****************************************************************************************************
                         Defines
*****************************************************************************************************/
#define WLAN_MAX_RETRY 5

//#undef __USE_AP__
#define __USE_AP__

/****************************************************************************************************
                         Global                                                       
*****************************************************************************************************/
static const char* ssid = WIFI_SSID;
static const char* password = WIFI_PW;
static const char* AP_wifi_ssid = AP_WIFI_SSID;
static const char* AP_wifi_password = AP_WIFI_PW;
char AP_ssid[50];

/****************************************************************************************************
                         FORWARD             
*****************************************************************************************************/
int httpGETRequest(const char* serverName, String *responseString);
void initWiFi(void);

/******************************************************************************************************/
void initWiFi(void) 
/******************************************************************************************************/
{
    uint8_t connectCounter = 0;
#ifdef __USE_AP__    
    sprintf(AP_ssid, AP_wifi_ssid);
     Serial.printf("%s\n",AP_ssid) ;                                                  

     Serial.printf("Connecting...\n");
 
    WiFi.mode(WIFI_AP_STA);
    //AP-Mode
    WiFi.softAP(AP_ssid,AP_wifi_password);   
    IPAddress IP_auto = WiFi.softAPIP();
     Serial.printf("AP IP address auto: \n");
     Serial.printf("Test %d:%d:%d:%d\n",IP_auto[0],IP_auto[1],IP_auto[2],IP_auto[3]);
    delay(100);
  
     Serial.printf("Set softAPConfig\n");
    IPAddress IP_fix(192, 168, 2, 33);
    IPAddress NMask(255, 255, 255, 0);
    WiFi.softAPConfig(IP_fix, IP_fix, NMask);
  
    IPAddress IP_readback = WiFi.softAPIP();
     Serial.printf("AP IP address readback: \n");
     Serial.printf("Test %d:%d:%d:%d\n",IP_readback[0],IP_readback[1],IP_readback[2],IP_readback[3]);
#endif

    WiFi.begin(ssid, password);
    WiFi.setSleep(false);
     Serial.printf("Connecting to WiFi ..\n");
    while (WiFi.status() != WL_CONNECTED) 
    {
         Serial.printf(".");
        connectCounter ++;
        delay(1000);
        if(WLAN_MAX_RETRY == connectCounter )
        {
            ESP.restart();
        }
    }
     Serial.printf("\nIP ");
    Serial.println(WiFi.localIP());
 
}


void printWifiIP(void)
{
     Serial.printf("IP %s\n",String(WiFi.localIP()).c_str());
    Serial.println(WiFi.localIP());
}

/******************************************************************************************************/
int httpGETRequest(const char* serverName, String *responseString) 
{
    int httpResponseCode = -1;
    
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
  
    // Send HTTP POST request
    httpResponseCode = http.GET();
  
    String payload = "{}"; 
  
    if (httpResponseCode>0) 
    {
         Serial.printf("HTTP Response code: \n");
         Serial.printf("%d\n",httpResponseCode);
         Serial.printf("-\n");
        payload = http.getString();
    }
    else 
    {
         Serial.printf("Error code: \n");
        Serial.printf("%d\n",httpResponseCode);
    }
    // Free resources
    http.end();

    *responseString = payload;

    return httpResponseCode;
}
