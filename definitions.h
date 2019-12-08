
enum AnimationLevel {
  EVERYTHING,
  ZONE_LEVEL,
  SECTION_LEVEL,
};

AnimationLevel ANIMATION_LEVEL = EVERYTHING;

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
  int id=0;
  bool active = false;
  int center = 0;
  int steps = -1;
  int previousLed = 0;
  int start = 0;
  int endIdx = 0;
  int fireStart = 1;
  int fireEnd = 1;
  Animation pattern = RIPPLE;
  CRGB* leds;
  int ledCount = 0;
};

struct Section : LedStrip {
};

struct Zone : LedStrip {
  int sectionCount;
  int pin;
  Section sections[MAX_SECTION];
};
