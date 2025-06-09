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
const char* ssid = "FRITZ!Box 6591 Cable JE";
const char* password = "46118655562450441459";
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
{
    Serial.println("Starte nur Access Point Modus");

    WiFi.mode(WIFI_AP);

    // feste IP-Adresse setzen (muss vor softAP() passieren!)
    IPAddress ip(192, 168, 2, 33);
    IPAddress gateway(192, 168, 2, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(ip, gateway, subnet);

    // Access Point starten
    WiFi.softAP("Led_Cube", "#Led_Cube#");

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP gestartet! IP-Adresse: ");
    Serial.println(myIP);
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
