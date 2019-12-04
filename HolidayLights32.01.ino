/*****************  NEEDED TO MAKE NODEMCU WORK ***************************/
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

/******************  LIBRARY SECTION *************************************/

#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <SimpleTimer.h>    //https://github.com/thehookup/Simple-Timer-Library
#include <PubSubClient.h>   //https://github.com/knolleary/pubsubclient
#include <WiFi.h>    //if you get an error here you need to install the ESP8266 board manager 
#include <ESPmDNS.h>    //if you get an error here you need to install the ESP8266 board manager 
#include <ArduinoOTA.h>     //ArduinoOTA is now included with the ArduinoIDE
#include <EEPROM.h>    //Long term storage (for state and wifi setup
#include <WebServer.h>

/*******************  User set variables *******************************/
#include "secrets.h" //Has the various usernnames aand files
/***************************
 * Contents of Secrets File
#define USER_SSID                 ""
#define USER_PASSWORD             ""
#define USER_MQTT_SERVER          ""
#define USER_MQTT_PORT            1883
#define USER_MQTT_USERNAME        "t"
#define USER_MQTT_PASSWORD        ""
#define USER_MQTT_CLIENT_NAME     "LightMCU"           // Used to define MQTT topics, MQTT Client ID, and ArduinoOTA
 */

#define FIRSTZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define SECONDZONE_COLOR_ORDER          GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define THIRDZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define FOURTHZONE_COLOR_ORDER          GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define FIFTHZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR
#define SIXTHZONE_COLOR_ORDER           GRB                 
#define SECTION_START  0
#define SECTION_END  1
#define FIRE_START  2
#define FIRE_END  3
//We could easily have more sections
#define MAX_SECTION 9

#define ZONE_ONE_LED_COUNT 1000
#define ZONE_TWO_LED_COUNT 1000
#define ZONE_THREE_LED_COUNT 1000
#define ZONE_FOUR_LED_COUNT 1000
#define ZONE_FIVE_LED_COUNT 1000
#define ZONE_SIX_LED_COUNT 1000

//Zones are limited by pins (so with nodemcu just 6
int const ZONE_ONE = 0;
int const ZONE_TWO = 1;
int const ZONE_THREE = 2;
int const ZONE_FOUR = 3;
int const ZONE_FIVE = 4;
int const ZONE_SIX = 5;
int const ZONE_COUNT = 6;

#include "definitions.h"


Zone zones[6];
CRGB firstZoneLeds[ZONE_ONE_LED_COUNT];
CRGB secondZoneLeds[ZONE_TWO_LED_COUNT];
CRGB thirdZoneLeds[ZONE_THREE_LED_COUNT];
CRGB fourthZoneLeds[ZONE_FOUR_LED_COUNT];
CRGB fifthZoneLeds[ZONE_FIVE_LED_COUNT];
CRGB sixthZoneLeds[ZONE_SIX_LED_COUNT];

void setupZonesStats(){
 zones[ZONE_ONE].ledCount = ZONE_ONE_LED_COUNT;
 zones[ZONE_ONE].active=true;
 zones[ZONE_ONE].pin = 5;
 zones[ZONE_ONE].sectionCount = 1;
 zones[ZONE_ONE].leds = firstZoneLeds;
 zones[ZONE_ONE].sections[0].active = true;
 zones[ZONE_ONE].sections[0].sectionId=0;
 zones[ZONE_ONE].sections[0].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[0].end  =      1000;         //ending LED for this zone
 zones[ZONE_ONE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[0].active = true;
 zones[ZONE_ONE].sections[1].sectionId=1;
 zones[ZONE_ONE].sections[1].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[1].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[2].active = true;
 zones[ZONE_ONE].sections[2].sectionId=2;
 zones[ZONE_ONE].sections[2].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[2].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[3].active = true;
 zones[ZONE_ONE].sections[3].sectionId=3;
 zones[ZONE_ONE].sections[3].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[3].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[4].active = true;
 zones[ZONE_ONE].sections[4].sectionId=4;
 zones[ZONE_ONE].sections[4].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[4].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[5].active = true;
 zones[ZONE_ONE].sections[5].sectionId=5;
 zones[ZONE_ONE].sections[5].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[5].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[6].active = true;
 zones[ZONE_ONE].sections[6].sectionId=6;
 zones[ZONE_ONE].sections[6].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[6].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[7].active = true;
 zones[ZONE_ONE].sections[7].sectionId=7;
 zones[ZONE_ONE].sections[7].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[7].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_ONE].sections[8].active = true;
 zones[ZONE_ONE].sections[8].sectionId=8;
 zones[ZONE_ONE].sections[8].start  =    0;           //starting LED for this zone
 zones[ZONE_ONE].sections[8].end  =      100;         //ending LED for this zone
 zones[ZONE_ONE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_ONE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  




 zones[ZONE_TWO].ledCount = ZONE_TWO_LED_COUNT;
 zones[ZONE_TWO].active=true;
 zones[ZONE_TWO].pin = 4;
 zones[ZONE_TWO].sectionCount = 1;
 zones[ZONE_TWO].leds = secondZoneLeds;
 zones[ZONE_TWO].sections[0].active = true;
 zones[ZONE_TWO].sections[0].sectionId=0;
 zones[ZONE_TWO].sections[0].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[0].end  =      1000;         //ending LED for this zone
 zones[ZONE_TWO].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[1].active = true;
 zones[ZONE_TWO].sections[1].sectionId=1;
 zones[ZONE_TWO].sections[1].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[1].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[2].active = true;
 zones[ZONE_TWO].sections[2].sectionId=2;
 zones[ZONE_TWO].sections[2].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[2].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[3].active = true;
 zones[ZONE_TWO].sections[3].sectionId=3;
 zones[ZONE_TWO].sections[3].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[3].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[4].active = true;
 zones[ZONE_TWO].sections[4].sectionId=4;
 zones[ZONE_TWO].sections[4].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[4].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[5].active = true;
 zones[ZONE_TWO].sections[5].sectionId=5;
 zones[ZONE_TWO].sections[5].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[5].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[6].active = true;
 zones[ZONE_TWO].sections[6].sectionId=6;
 zones[ZONE_TWO].sections[6].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[6].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[7].active = true;
 zones[ZONE_TWO].sections[7].sectionId=7;
 zones[ZONE_TWO].sections[7].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[7].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_TWO].sections[8].active = true;
 zones[ZONE_TWO].sections[8].sectionId=8;
 zones[ZONE_TWO].sections[8].start  =    0;           //starting LED for this zone
 zones[ZONE_TWO].sections[8].end  =      100;         //ending LED for this zone
 zones[ZONE_TWO].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_TWO].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes


 
 zones[ZONE_THREE].ledCount = ZONE_THREE_LED_COUNT;
 zones[ZONE_THREE].active=true;
 zones[ZONE_THREE].pin = 0;
 zones[ZONE_THREE].sectionCount = 9;
 zones[ZONE_THREE].leds = thirdZoneLeds;
 zones[ZONE_THREE].sections[0].active = true;
 zones[ZONE_THREE].sections[0].sectionId=0;
 zones[ZONE_THREE].sections[0].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[0].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[1].active = true;
 zones[ZONE_THREE].sections[1].sectionId=1;
 zones[ZONE_THREE].sections[1].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[1].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[2].active = true;
 zones[ZONE_THREE].sections[2].sectionId=2;
 zones[ZONE_THREE].sections[2].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[2].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[3].active = true;
 zones[ZONE_THREE].sections[3].sectionId=3;
 zones[ZONE_THREE].sections[3].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[3].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[4].active = true;
 zones[ZONE_THREE].sections[4].sectionId=4;
 zones[ZONE_THREE].sections[4].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[4].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[5].active = true;
 zones[ZONE_THREE].sections[5].sectionId=5;
 zones[ZONE_THREE].sections[5].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[5].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[6].active = true;
 zones[ZONE_THREE].sections[6].sectionId=6;
 zones[ZONE_THREE].sections[6].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[6].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[7].active = true;
 zones[ZONE_THREE].sections[7].sectionId=7;
 zones[ZONE_THREE].sections[7].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[7].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_THREE].sections[8].active = true;
 zones[ZONE_THREE].sections[8].sectionId=8;
 zones[ZONE_THREE].sections[8].start  =    0;           //starting LED for this zone
 zones[ZONE_THREE].sections[8].end  =      100;         //ending LED for this zone
 zones[ZONE_THREE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_THREE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes


 
 zones[ZONE_FOUR].ledCount = ZONE_FOUR_LED_COUNT;
 zones[ZONE_FOUR].active=true;
 zones[ZONE_FOUR].pin = 14;
 zones[ZONE_FOUR].sectionCount = 9;
 zones[ZONE_FOUR].leds = fourthZoneLeds;
 zones[ZONE_FOUR].sections[0].active = true;
 zones[ZONE_FOUR].sections[0].sectionId=0;
 zones[ZONE_FOUR].sections[0].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[0].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[1].active = true;
 zones[ZONE_FOUR].sections[1].sectionId=1;
 zones[ZONE_FOUR].sections[1].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[1].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[2].active = true;
 zones[ZONE_FOUR].sections[2].sectionId=2;
 zones[ZONE_FOUR].sections[2].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[2].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[3].active = true;
 zones[ZONE_FOUR].sections[3].sectionId=3;
 zones[ZONE_FOUR].sections[3].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[3].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[4].active = true;
 zones[ZONE_FOUR].sections[4].sectionId=4;
 zones[ZONE_FOUR].sections[4].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[4].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[5].active = true;
 zones[ZONE_FOUR].sections[5].sectionId=5;
 zones[ZONE_FOUR].sections[5].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[5].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[6].active = true;
 zones[ZONE_FOUR].sections[6].sectionId=6;
 zones[ZONE_FOUR].sections[6].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[6].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[7].active = true;
 zones[ZONE_FOUR].sections[7].sectionId=7;
 zones[ZONE_FOUR].sections[7].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[7].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FOUR].sections[8].active = true;
 zones[ZONE_FOUR].sections[8].sectionId=8;
 zones[ZONE_FOUR].sections[8].start  =    0;           //starting LED for this zone
 zones[ZONE_FOUR].sections[8].end  =      100;         //ending LED for this zone
 zones[ZONE_FOUR].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FOUR].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes


 
 zones[ZONE_FIVE].ledCount = ZONE_FIVE_LED_COUNT;
 zones[ZONE_FIVE].active=true;
 zones[ZONE_FIVE].pin = 12;
 zones[ZONE_FIVE].sectionCount = 9;
 zones[ZONE_FIVE].leds = fifthZoneLeds;
 zones[ZONE_FIVE].sections[0].active = true;
 zones[ZONE_FIVE].sections[0].sectionId=0;
 zones[ZONE_FIVE].sections[0].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[0].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FIVE].sections[1].active = true;
 zones[ZONE_FIVE].sections[1].sectionId=1;
 zones[ZONE_FIVE].sections[1].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[1].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FIVE].sections[2].active = true;
 zones[ZONE_FIVE].sections[2].sectionId=2;
 zones[ZONE_FIVE].sections[2].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[2].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

 zones[ZONE_FIVE].sections[3].active = true;
 zones[ZONE_FIVE].sections[3].sectionId=3;
 zones[ZONE_FIVE].sections[3].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[3].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FIVE].sections[4].active = true;
 zones[ZONE_FIVE].sections[4].sectionId=4;
 zones[ZONE_FIVE].sections[4].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[4].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FIVE].sections[5].active = true;
 zones[ZONE_FIVE].sections[5].sectionId=5;
 zones[ZONE_FIVE].sections[5].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[5].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FIVE].sections[6].active = true;
 zones[ZONE_FIVE].sections[6].sectionId=6;
 zones[ZONE_FIVE].sections[6].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[6].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FIVE].sections[7].active = true;
 zones[ZONE_FIVE].sections[7].sectionId=7;
 zones[ZONE_FIVE].sections[7].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[7].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_FIVE].sections[8].active = true;
 zones[ZONE_FIVE].sections[8].sectionId=8;
 zones[ZONE_FIVE].sections[8].start  =    0;           //starting LED for this zone
 zones[ZONE_FIVE].sections[8].end  =      100;         //ending LED for this zone
 zones[ZONE_FIVE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_FIVE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes


 
 zones[ZONE_SIX].ledCount = ZONE_SIX_LED_COUNT;
 zones[ZONE_SIX].active=true;
 zones[ZONE_SIX].pin = 13;
 zones[ZONE_SIX].sectionCount = 9;
 zones[ZONE_SIX].leds = sixthZoneLeds;
 zones[ZONE_SIX].sections[0].active = true;
 zones[ZONE_SIX].sections[0].sectionId=0;
 zones[ZONE_SIX].sections[0].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[0].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[1].active = true;
 zones[ZONE_SIX].sections[1].sectionId=1;
 zones[ZONE_SIX].sections[1].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[1].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[2].active = true;
 zones[ZONE_SIX].sections[2].sectionId=2;
 zones[ZONE_SIX].sections[2].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[2].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[3].active = true;
 zones[ZONE_SIX].sections[3].sectionId=3;
 zones[ZONE_SIX].sections[3].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[3].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[4].active = true;
 zones[ZONE_SIX].sections[4].sectionId=4;
 zones[ZONE_SIX].sections[4].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[4].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[5].active = true;
 zones[ZONE_SIX].sections[5].sectionId=5;
 zones[ZONE_SIX].sections[5].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[5].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[6].active = true;
 zones[ZONE_SIX].sections[6].sectionId=6;
 zones[ZONE_SIX].sections[6].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[6].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[7].active = true;
 zones[ZONE_SIX].sections[7].sectionId=7;
 zones[ZONE_SIX].sections[7].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[7].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
 
 zones[ZONE_SIX].sections[8].active = true;
 zones[ZONE_SIX].sections[8].sectionId=8;
 zones[ZONE_SIX].sections[8].start  =    0;           //starting LED for this zone
 zones[ZONE_SIX].sections[8].end  =      100;         //ending LED for this zone
 zones[ZONE_SIX].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
 zones[ZONE_SIX].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
}


/************ Don't mess with ********************/
const char* ssid = USER_SSID ; 
const char* password = USER_PASSWORD ;
const char* mqtt_server = USER_MQTT_SERVER ;
const int mqtt_port = USER_MQTT_PORT ;
const char *mqtt_user = USER_MQTT_USERNAME ;
const char *mqtt_pass = USER_MQTT_PASSWORD ;
const char *mqtt_client_name = USER_MQTT_CLIENT_NAME ; 

const int BUTTON = 5;
const int LED = 2;
CRGBPalette16 gPal;
int glitterFrequency = 100;
int lightningChance = 65280;  
int firesize = 40;
int SPARKING = 85;
int COOLING =  120;
bool gReverseDirection = false;
uint8_t mark = 0;
uint8_t gHue = 0; 
uint8_t startPosition = 0;
uint8_t glitterChance = 250;
int chaseDelay = 1000;
int lastPosition = 1;
int lightning = 1;
int raceSpeed = 12;
int BeatsPerMinute = 62;
uint8_t numberOfRainbows = 7;
int twinkleChance = 250;
int eyeChance = 248;
bool boot = true;
String effect = "None";
bool showGlitter = false;
bool showLightning = false;
bool audioEffects = false;
bool showLights = false;
byte red1 = 255;
byte green1 = 0;
byte blue1 = 0;
byte red2 = 0;
byte green2 = 255;
byte blue2 = 0;
byte red3 = 0;
byte green3 = 0;
byte blue3 = 255;
byte redG = 255;
byte greenG = 255;
byte blueG = 255;
byte brightness = 255;
char charPayload[50];
int maxLEDs = 500;
int locatorLED = 0;
char MQTT_locatorLED[50];
int locatorDelay = 1000;


const boolean WIFI_AP = false;
const boolean WIFI_CONNECT = true;


const String TOGGLE = "toggle";
const String ON = "on";
const String OFF = "off";

const int Pin_firstZone = 5; //marked as D1 on the board
const int Pin_secondZone = 4; //marked as D2 on the board
const int Pin_thirdZone = 0; //marked as D3 on the board
const int Pin_fourthZone = 14; //marked as D5 on the board
const int Pin_fifthZone = 12; //marked as D6 on the board
const int Pin_sixthZone = 13; //marked as D7 on the board


WebServer webServer(80);

WiFiClient espClient;
PubSubClient client(espClient);
SimpleTimer timer;

#include "animations.h"
#include "wifi.h"
#include "web.h"


void setup() {
  // put your setup code here, to run once:

  pinMode(BUTTON,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(BUTTON) == HIGH){ //Use the button to swap the lights;
    flipLights();
  }

}

void flipLights(){
  showLights = !showLights;
  Serial.println("Setting showLights : "+showLights);
}
