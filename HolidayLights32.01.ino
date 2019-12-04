/*****************  NEEDED TO MAKE NODEMCU WORK ***************************/
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

/******************  LIBRARY SECTION *************************************/

#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <SimpleTimer.h>    //https://github.com/thehookup/Simple-Timer-Library
#include <PubSubClient.h>   //https://github.com/knolleary/pubsubclient
#include <WiFi.h>    //if you get an error here you need to install the ESP32 board manager 
#include <WifiClient.h> //  
#include <ESPmDNS.h>    //if you get an error here you need to install the ESP8266 board manager 
#include <ArduinoOTA.h>     //ArduinoOTA is now included with the ArduinoIDE
#include <EEPROM.h>    //Long term storage (for state and wifi setup
#include <WebServer.h>

/*******************  User set variables *******************************/
#include "secrets.h" //Has the various usernnames aand files

#ifndef USER_SSID
#define USER_SSID                 "default"
#define USER_AP_PASSWORD          "pass"
#define USER_MQTT_SERVER          ""
#define USER_MQTT_PORT            1883
#define USER_MQTT_USERNAME        "mqtt"
#define USER_MQTT_PASSWORD        ""
#define USER_MQTT_CLIENT_NAME     "LightMCU"           // Used to define MQTT topics, MQTT Client ID, and ArduinoOTA
#endif

#define SECTION_START  0
#define SECTION_END  1
#define FIRE_START  2
#define FIRE_END  3
//We could easily have more sections
#define MAX_SECTION 9

//Zones are limited by pins 
int const ZONE_ONE = 0;
int const ZONE_TWO = 1;
int const ZONE_THREE = 2;
int const ZONE_FOUR = 3;
int const ZONE_FIVE = 4;
int const ZONE_SIX = 5;
int const ZONE_COUNT = 6;

#include "definitions.h"
#include "zoneDefinitions.h"


/************ Don't mess with ********************/
const char* ssid = USER_SSID ; 
const char* password = USER_PASSWORD ;
const char* apPassword = USER_AP_PASSWORD;
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
bool mqttActive = true;


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
#include "mqtt.h"
#include "wifi.h"
#include "web.h"


void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON,INPUT); //Setup the button pin
  setup_wifi();
  mqttConnect();
  setupLeds();
  setupZonesStats();
}



void loop() {
  // put your main code here, to run repeatedly:
  handleButton();
  updateLeds
  //need the light handle code here
}

bool buttonActive = false;
bool longPress = false;
long buttonTimer = 0;
long longPressTime = 250;
void handleButton() {
  if (digitalRead(BUTTON) == HIGH){ //Use the button to swap the lights;
    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {
			longPressActive = true;
      Serial.println("Long press, changing animation");
      nextAnimation();
		}
  } else {
    if (buttonActive == true){
      if (longPress){
        longPress = false;
      }else {
        Serial.println("Short press, flipping lights");
        flipLights();
      }
      buttonActive = false;
    }
  }
}

void flipLights(){
  showLights = !showLights;
  Serial.println("Setting showLights : "+showLights);
}
