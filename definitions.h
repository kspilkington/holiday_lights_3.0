
enum AnimationLevel {
  EVERYTHING,
  ZONE_LEVEL,
  SECTION_LEVEL,
};

AnimationLevel ANIMATION_LEVEL=EVERYTHING;

//Declare an Enum so we can easily use a switch statement
enum Animation {
  NONE,
  DOUBLE_CRASH,
  RIPPLE,
  FIRE,
  BPM,
  FILL,
  CHASE,
  COLOR_GLITTER,
  RAINBOW,
  TWINKLE,
  SPOOKY_EYES,
  SINGLE_RACE,
  BLOCKED_COLORS,
  LED_LOCATOR
};



struct LedStrip {
  bool active = true;
  int center=0;
  int steps=-1;
  int previousLed = 0;
  int start=0;
  int end=1000;
  int fireStart=1;
  int fireEnd=1;
  Animation pattern = RAINBOW;
  CRGB* leds;
  int ledCount=0;
};

struct Section : LedStrip {
  int sectionId=0;
};

struct Zone : LedStrip {
  int sectionCount;
  int pin;
  Section sections[MAX_SECTION];
};

struct Settings {

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
byte brightness = 84;
char charPayload[50];
int maxLEDs = 500;
int locatorLED = 0;
char MQTT_locatorLED[50];
int locatorDelay = 1000;
bool mqttActive = true;

}
