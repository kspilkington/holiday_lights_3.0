  /*****************  NEEDED TO MAKE NODEMCU WORK ***************************/
//#define FASTLED_INTERRUPT_RETRY_COUNT 0
//#define FASTLED_ALLOW_INTERRUPTS 0
//#define WIFI_CLIENT_ACTIVATE
//#define WIFI_AP_ACTIVATE
//#define MQTT_ACTIVATE
//#define WEBSERVER

/******************  LIBRARY SECTION *************************************/

#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <SimpleTimer.h>    //https://github.com/thehookup/Simple-Timer-Library
#if defined(WIFI_CLIENT_ACTIVATE) || defined(WIFI_AP_ACTIVATE)
#include <WiFi.h>    //if you get an error here you need to install the ESP32 board manager 
#include <ArduinoOTA.h>     //ArduinoOTA is now included with the ArduinoIDE
#endif
#ifdef MQTT_ACTIVATE
#include <WifiClient.h> //  
#include <PubSubClient.h>   //https://github.com/knolleary/pubsubclient
#include <ESPmDNS.h>    //if you get an error here you need to install the ESP8266 board manager 
#endif
#ifdef WEBSERVER
#include <WebServer.h>
#endif
#include <Preferences.h>
/*******************  User set variables *******************************/
#include "secrets.h" //Has the various usernames and files

#ifndef USER_SSID    //These could be defined in the secrets.h file
#define USER_SSID                 "default"
#define USER_AP_PASSWORD          "pass"
#define USER_MQTT_SERVER          ""
#define USER_MQTT_PORT            1883
#define USER_MQTT_USERNAME        "mqtt"
#define USER_MQTT_PASSWORD        ""
#define USER_MQTT_CLIENT_NAME     "LightMCU"           // Used to define MQTT topics, MQTT Client ID, and ArduinoOTA
#endif
#define EEPROM_SIZE = 10




#include "zoneDefinitions.h"
/************ Don't mess with ********************/
//Animation variables
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
bool showGlitter = false;
bool showLightning = false;
bool audioEffects = false;
bool showLights = false;
byte brightness = 100;
char charPayload[50];
int maxLEDs = ZONE_ONE_LED_COUNT;
int locatorLED = 0;
char MQTT_locatorLED[50];
int locatorDelay = 1000;

CRGB gColors[3] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255)};
CRGB glitterColor = CRGB(255, 255, 255);

//Network variables
bool  mqttActive = false;
char* ssid = USER_SSID ;
char* password = USER_PASSWORD ;
char* apPassword = USER_AP_PASSWORD;
char* mqtt_server = USER_MQTT_SERVER ;
int   mqtt_port = USER_MQTT_PORT ;
char *mqtt_user = USER_MQTT_USERNAME ;
char *mqtt_pass = USER_MQTT_PASSWORD ;
char *mqtt_client_name = USER_MQTT_CLIENT_NAME ;
bool  boot = true;

const boolean WIFI_ACTIVATE_AP = true;
boolean wifiApActive = false;
boolean wifiClientActive = false;
const boolean WIFI_ACTIVATE_CLIENT = true;
bool noWeb = false;
Preferences preferences;


//Constants
const int BUTTON = 5;
const int LED = 2;

const int COLOR_COUNT = 3;

const String TOGGLE = "toggle";
const String ON = "on";
const String OFF = "off";

const int Pin_firstZone = 22; //marked as D4 on the board
const int Pin_secondZone = 1; //marked as D2 on the board
const int Pin_thirdZone = 0; //marked as D3 on the board
const int Pin_fourthZone = 14; //marked as D5 on the board
const int Pin_fifthZone = 12; //marked as D6 on the board
const int Pin_sixthZone = 13; //marked as D7 on the board

String message = "SOS I now have Zendesk"; //max length = 100
int* morseMessage[600];
int morseMessageSize=0;



SimpleTimer timer;

#include "animations.h"

#if defined(WIFI_CLIENT_ACTIVATE) || defined(WIFI_AP_ACTIVATE)
#include "wifi.h"
#endif

#ifdef MQTT_ACTIVATE
WiFiClient espClient;
PubSubClient mqttClient(espClient);
#include "mqtt.h"
#endif

#ifdef WEBSERVER
WebServer webServer(80);
#include "web.h"
#endif


void setup() {
  Serial.begin(115200);
  Serial.println("Starting up");

  FastLED.setDither( 0 );
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT); //Setup the button pin
  pinMode(LED, OUTPUT); //set the pin (2) for the onboard led

  //Can I check the button here to see if it's high and turn/on/off features based on it?

#if defined(WIFI_CLIENT_ACTIVATE) || defined(WIFI_AP_ACTIVATE)
  if (digitalRead(BUTTON) == HIGH) {
    Serial.println("Starting up Wifi");
    setup_wifi();
    otaSteup();
  } else {
    Serial.println("Turning off all networking for this time due to button press during boot");
    noWeb = true;
  }
#endif

  Serial.println("Starting up zones");
  setupZonesStats();
  Serial.println("Starting up leds");
  setupLeds();
  Serial.println("Starting up max");
  calculateMax();
#ifdef MQTT_ACTIVATE
  Serial.println("Starting up mqtt");
  mqttConnect();
  if (mqttActive) {
    Serial.println("Starting up mqtt callback");
    mqttClient.setServer(mqtt_server, mqtt_port);
    mqttClient.setCallback(mqttCallback);
    timer.setTimeout(120000, checkIn);
  }
#endif
  gPal = HeatColors_p;

  preferences.begin("LightShow",false);
  loadSettings();

  timer.setTimeout(10000, chase);
  buildMorseMessage();
  Serial.println("Done Setup");

}



void loop() {
  handleButton();
  LEDS.setBrightness(brightness);
  // put your main code here, to run repeatedly:
  //  Serial.println("Client status:"+client.connected());
#ifdef MQTT_ACTIVATE
  if (!noWeb && !mqttClient.connected())
  {
    Serial.println("Reconnecting");
    mqttReconnect();
  }
  client.loop();
#endif
#if defined(WIFI_CLIENT_ACTIVATE) || defined(WIFI_AP_ACTIVATE)
  if (showLights == false && !noWeb)
  {
    ArduinoOTA.handle();
  }
#endif
#ifdef WEBSERVER
  if (wifiApActive || wifiClientActive) {
    handleWeb();
  }
#endif

  for (int idx = 0; idx < MAX_ZONE_COUNT; idx++) {
    if (zones[idx].active) {
      if (showLights){
      FastLED[idx].showLeds(brightness);
      }else {
        clearLeds(zones[idx]);
        FastLED.show();
      }
    }
  }
  timer.run();
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;
  }
  EVERY_N_MILLISECONDS( 100 )
  {
    if (showLights) {
      if (ANIMATION_LEVEL == ZONE_LEVEL) {
        updateZoneLeds();
      } else if (ANIMATION_LEVEL == SECTION_LEVEL) {
        updateSectionLeds();
      } else {
        updateZoneLeds();
      }
    }else{
      clearLeds();
    }
  }

}

//Button Variables
bool buttonActive = false;
bool longPress = false;
long buttonTimer = 0;
long longPressTime = 250;
void handleButton() {
  if (digitalRead(BUTTON) == HIGH) { //Use the button to swap the lights;
    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
    }
    if ((millis() - buttonTimer > longPressTime) && (longPress == false)) {
      longPress = true;
      Serial.println("Long press, changing animation");
      setZonesNextAnimation();
    }
  } else {
    if (buttonActive == true) {
      if (longPress) {
        longPress = false;
      } else {
        Serial.println("Short press, flipping lights");
        flipLights();
      }
      buttonActive = false;
    }
  }
}

void flipLights() {
  clearLeds();
  showLights = !showLights;
  Serial.println((String)"Setting showLights : " + showLights);
}
