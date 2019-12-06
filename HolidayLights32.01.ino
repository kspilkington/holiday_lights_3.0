/*****************  NEEDED TO MAKE NODEMCU WORK ***************************/
#define FASTLED_INTERRUPT_RETRY_COUNT 0
//#define FASTLED_ESP32_RAW_PIN_ORDER

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

#ifndef USER_SSID    //These could be defined in the secrets.h file
#define USER_SSID                 "default"
#define USER_AP_PASSWORD          "pass"
#define USER_MQTT_SERVER          ""
#define USER_MQTT_PORT            1883
#define USER_MQTT_USERNAME        "mqtt"
#define USER_MQTT_PASSWORD        ""
#define USER_MQTT_CLIENT_NAME     "LightMCU"           // Used to define MQTT topics, MQTT Client ID, and ArduinoOTA
#endif

//Zones are limited by number
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
byte brightness = 84;
char charPayload[50];
int maxLEDs = ZONE_ONE_LED_COUNT;
int locatorLED = 0;
char MQTT_locatorLED[50];
int locatorDelay = 1000;

CRGB gColors = CRGB[3];
CRGB glitterColor = CRGB(255, 255, 255);

//Network variables
bool mqttActive = false;
char* ssid = USER_SSID ;
char* password = USER_PASSWORD ;
char* apPassword = USER_AP_PASSWORD;
char* mqtt_server = USER_MQTT_SERVER ;
int mqtt_port = USER_MQTT_PORT ;
char *mqtt_user = USER_MQTT_USERNAME ;
char *mqtt_pass = USER_MQTT_PASSWORD ;
char *mqtt_client_name = USER_MQTT_CLIENT_NAME ;

const boolean WIFI_ACTIVATE_AP = true;
boolean wifiApActive = false;
boolean wifiClientActive = false;
const boolean WIFI_ACTIVATE_CLIENT = true;
bool noWeb = false;


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


WebServer webServer(80);

WiFiClient espClient;
PubSubClient mqttClient(espClient);
SimpleTimer timer;

#include "animations.h"
#include "mqtt.h"
#include "wifi.h"
#include "web.h"



void setup() {
  Serial.begin(115200);
  Serial.println("Starting up");

  FastLED.setDither( 0 );
  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT); //Setup the button pin
  pinMode(LED, OUTPUT); //set the pin (2) for the onboard led

  //Can I check the button here to see if it's high and turn/on/off features based on it?

  if (digitalRead(BUTTON) != HIGH) {
    Serial.println("Starting up Wifi");
    setup_wifi();
    Serial.println("Starting up mqtt");
    mqttConnect();
  } else {
    Serial.println("Turning off all networking for this time due to button press during boot");
    noWeb = true;
  }
  Serial.println("Starting up leds");
  setupLeds();
  Serial.println("Starting up zones");
  setupZonesStats();
  Serial.println("Starting up max");
  calculateMax();
  Serial.println("Starting up mqtt callback");
  if (mqttActive) {
    mqttClient.setServer(mqtt_server, mqtt_port);
    mqttClient.setCallback(mqttCallback);
  }
  Serial.println("Starting ArduionoOTA");
  otaSteup();
  Serial.println("Done with Ota");
  gPal = HeatColors_p;

  timer.setTimeout(10000, chase);
  timer.setTimeout(120000, checkIn);
  Serial.println("Done Setup");

}


void otaSteup() {
  if (!noWeb && (wifiApActive || wifiClientActive)) {
    ArduinoOTA.setHostname(USER_MQTT_CLIENT_NAME);
    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

    ArduinoOTA.begin();
  }
}


void fadeall() {
  for (int i = 0; i < ZONE_ONE_LED_COUNT; i++) {
    firstZoneLeds[i].nscale8(250);
  }
}

void tempLights() {

  static uint8_t hue = 0;
  for (int i = 0; i < ZONE_ONE_LED_COUNT; i++) {
    // Set the i'th led to red
    //    firstZoneLeds[i] = CHSV(hue++, 255, 255);
    AllLeds[0][i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.print("x");

  // Now go in the other direction.
  for (int i = (ZONE_ONE_LED_COUNT) - 1; i >= 0; i--) {
    // Set the i'th led to red
    //    firstZoneLeds[i] = CHSV(hue++, 255, 255);
    AllLeds[0][i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
}
void loop() {
  handleButton();
  LEDS.setBrightness(brightness);
  // put your main code here, to run repeatedly:
  //  Serial.println("Client status:"+client.connected());
  if (!mqttClient.connected())
  {
    Serial.println("Reconnecting");
    reconnect();
  }
  //  Serial.println("OTA");
  if (showLights == false && !noWeb)
  {
    ArduinoOTA.handle();
  }

  if (wifiApActive || wifiClientActive) {
    handleWeb();
  }

  //  tempLights();
  Serial.println("timer");
  timer.run();
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;
  }
  if (ANIMATION_LEVEL == ZONE_LEVEL) {
    Serial.println("Updating zones");
    updateZoneLeds();
  } else if (ANIMATION_LEVEL == SECTION_LEVEL) {
    Serial.println("Updating sections");
    updateSectionLeds();
  } else {
    Serial.println("Updating everything");
    updateZoneLeds();
  }

  Serial.println("leds");
  for (int idx = 0; idx < ZONE_COUNT; idx ++)
  {
    Serial.println(((String)"leds: ") + idx + " show: " + zones[idx].active);
    if (zones[idx].active) {
      FastLED.show();
    }
  }
  Serial.println("leds done");
}


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
  showLights = !showLights;
  Serial.println((String)"Setting showLights : " + showLights);
}
