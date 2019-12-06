
#define FIRSTZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define SECONDZONE_COLOR_ORDER          GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define THIRDZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define FOURTHZONE_COLOR_ORDER          GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define FIFTHZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR
#define SIXTHZONE_COLOR_ORDER           GRB

#define ZONE_ONE_LED_COUNT 300
#define ZONE_TWO_LED_COUNT 0
#define ZONE_THREE_LED_COUNT 0
#define ZONE_FOUR_LED_COUNT 0
#define ZONE_FIVE_LED_COUNT 0
#define ZONE_SIX_LED_COUNT 0
#define MAX_LED_ZONE_COUNT 300 //led size of the biggest zone

//We could easily have more sections
#define MAX_SECTION 9



Zone zones[ZONE_COUNT];
CRGB gAllLeds[ZONE_COUNT][MAX_LED_ZONE_COUNT];

void setupZonesStats() {
  zones[ZONE_ONE].ledCount = ZONE_ONE_LED_COUNT;
  zones[ZONE_ONE].active = true;
  zones[ZONE_ONE].pin = 22;
  zones[ZONE_ONE].sectionCount = 1;
  zones[ZONE_ONE].leds = gAllLeds[ZONE_ONE];
  zones[ZONE_ONE].sections[0].active = true;
  zones[ZONE_ONE].sections[0].sectionId = 0;
  zones[ZONE_ONE].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[0].end  =      299;         //ending LED for this zone
  zones[ZONE_ONE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[0].active = false;
  zones[ZONE_ONE].sections[1].sectionId = 1;
  zones[ZONE_ONE].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[1].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[2].active = false;
  zones[ZONE_ONE].sections[2].sectionId = 2;
  zones[ZONE_ONE].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[2].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[3].active = false;
  zones[ZONE_ONE].sections[3].sectionId = 3;
  zones[ZONE_ONE].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[3].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[4].active = false;
  zones[ZONE_ONE].sections[4].sectionId = 4;
  zones[ZONE_ONE].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[4].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[5].active = false;
  zones[ZONE_ONE].sections[5].sectionId = 5;
  zones[ZONE_ONE].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[5].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[6].active = false;
  zones[ZONE_ONE].sections[6].sectionId = 6;
  zones[ZONE_ONE].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[6].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[7].active = false;
  zones[ZONE_ONE].sections[7].sectionId = 7;
  zones[ZONE_ONE].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[7].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_ONE].sections[8].active = false;
  zones[ZONE_ONE].sections[8].sectionId = 8;
  zones[ZONE_ONE].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[8].end  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes






  zones[ZONE_TWO].ledCount = ZONE_TWO_LED_COUNT;
  zones[ZONE_TWO].active = false;
  zones[ZONE_TWO].pin = 4;
  zones[ZONE_TWO].sectionCount = 1;
  zones[ZONE_TWO].leds = gAllLeds[ZONE_TWO];
  zones[ZONE_TWO].sections[0].active = true;
  zones[ZONE_TWO].sections[0].sectionId = 0;
  zones[ZONE_TWO].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[0].end  =      1000;         //ending LED for this zone
  zones[ZONE_TWO].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[1].active = true;
  zones[ZONE_TWO].sections[1].sectionId = 1;
  zones[ZONE_TWO].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[1].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[2].active = true;
  zones[ZONE_TWO].sections[2].sectionId = 2;
  zones[ZONE_TWO].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[2].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[3].active = true;
  zones[ZONE_TWO].sections[3].sectionId = 3;
  zones[ZONE_TWO].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[3].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[4].active = true;
  zones[ZONE_TWO].sections[4].sectionId = 4;
  zones[ZONE_TWO].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[4].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[5].active = true;
  zones[ZONE_TWO].sections[5].sectionId = 5;
  zones[ZONE_TWO].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[5].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[6].active = true;
  zones[ZONE_TWO].sections[6].sectionId = 6;
  zones[ZONE_TWO].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[6].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[7].active = true;
  zones[ZONE_TWO].sections[7].sectionId = 7;
  zones[ZONE_TWO].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[7].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_TWO].sections[8].active = true;
  zones[ZONE_TWO].sections[8].sectionId = 8;
  zones[ZONE_TWO].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[8].end  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes



  zones[ZONE_THREE].ledCount = ZONE_THREE_LED_COUNT;
  zones[ZONE_THREE].active = false;
  zones[ZONE_THREE].pin = 0;
  zones[ZONE_THREE].sectionCount = 9;
  zones[ZONE_THREE].leds = gAllLeds[ZONE_THREE];
  zones[ZONE_THREE].sections[0].active = true;
  zones[ZONE_THREE].sections[0].sectionId = 0;
  zones[ZONE_THREE].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[0].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[1].active = true;
  zones[ZONE_THREE].sections[1].sectionId = 1;
  zones[ZONE_THREE].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[1].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[2].active = true;
  zones[ZONE_THREE].sections[2].sectionId = 2;
  zones[ZONE_THREE].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[2].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[3].active = true;
  zones[ZONE_THREE].sections[3].sectionId = 3;
  zones[ZONE_THREE].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[3].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[4].active = true;
  zones[ZONE_THREE].sections[4].sectionId = 4;
  zones[ZONE_THREE].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[4].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[5].active = true;
  zones[ZONE_THREE].sections[5].sectionId = 5;
  zones[ZONE_THREE].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[5].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[6].active = true;
  zones[ZONE_THREE].sections[6].sectionId = 6;
  zones[ZONE_THREE].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[6].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[7].active = true;
  zones[ZONE_THREE].sections[7].sectionId = 7;
  zones[ZONE_THREE].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[7].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_THREE].sections[8].active = true;
  zones[ZONE_THREE].sections[8].sectionId = 8;
  zones[ZONE_THREE].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[8].end  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes



  zones[ZONE_FOUR].ledCount = ZONE_FOUR_LED_COUNT;
  zones[ZONE_FOUR].active = false;
  zones[ZONE_FOUR].pin = 14;
  zones[ZONE_FOUR].sectionCount = 9;
  zones[ZONE_FOUR].leds = gAllLeds[ZONE_FOUR];
  zones[ZONE_FOUR].sections[0].active = true;
  zones[ZONE_FOUR].sections[0].sectionId = 0;
  zones[ZONE_FOUR].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[0].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[1].active = true;
  zones[ZONE_FOUR].sections[1].sectionId = 1;
  zones[ZONE_FOUR].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[1].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[2].active = true;
  zones[ZONE_FOUR].sections[2].sectionId = 2;
  zones[ZONE_FOUR].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[2].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[3].active = true;
  zones[ZONE_FOUR].sections[3].sectionId = 3;
  zones[ZONE_FOUR].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[3].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[4].active = true;
  zones[ZONE_FOUR].sections[4].sectionId = 4;
  zones[ZONE_FOUR].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[4].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[5].active = true;
  zones[ZONE_FOUR].sections[5].sectionId = 5;
  zones[ZONE_FOUR].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[5].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[6].active = true;
  zones[ZONE_FOUR].sections[6].sectionId = 6;
  zones[ZONE_FOUR].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[6].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[7].active = true;
  zones[ZONE_FOUR].sections[7].sectionId = 7;
  zones[ZONE_FOUR].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[7].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FOUR].sections[8].active = true;
  zones[ZONE_FOUR].sections[8].sectionId = 8;
  zones[ZONE_FOUR].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[8].end  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes



  zones[ZONE_FIVE].ledCount = ZONE_FIVE_LED_COUNT;
  zones[ZONE_FIVE].active = false;
  zones[ZONE_FIVE].pin = 12;
  zones[ZONE_FIVE].sectionCount = 9;
  zones[ZONE_FIVE].leds = gAllLeds[ZONE_FIVE];
  zones[ZONE_FIVE].sections[0].active = true;
  zones[ZONE_FIVE].sections[0].sectionId = 0;
  zones[ZONE_FIVE].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[0].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[1].active = true;
  zones[ZONE_FIVE].sections[1].sectionId = 1;
  zones[ZONE_FIVE].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[1].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[2].active = true;
  zones[ZONE_FIVE].sections[2].sectionId = 2;
  zones[ZONE_FIVE].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[2].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[3].active = true;
  zones[ZONE_FIVE].sections[3].sectionId = 3;
  zones[ZONE_FIVE].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[3].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[4].active = true;
  zones[ZONE_FIVE].sections[4].sectionId = 4;
  zones[ZONE_FIVE].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[4].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[5].active = true;
  zones[ZONE_FIVE].sections[5].sectionId = 5;
  zones[ZONE_FIVE].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[5].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[6].active = true;
  zones[ZONE_FIVE].sections[6].sectionId = 6;
  zones[ZONE_FIVE].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[6].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[7].active = true;
  zones[ZONE_FIVE].sections[7].sectionId = 7;
  zones[ZONE_FIVE].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[7].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_FIVE].sections[8].active = true;
  zones[ZONE_FIVE].sections[8].sectionId = 8;
  zones[ZONE_FIVE].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[8].end  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes



  zones[ZONE_SIX].ledCount = ZONE_SIX_LED_COUNT;
  zones[ZONE_SIX].active = false;
  zones[ZONE_SIX].pin = 13;
  zones[ZONE_SIX].sectionCount = 9;
  zones[ZONE_SIX].leds = gAllLeds[ZONE_SIX];
  zones[ZONE_SIX].sections[0].active = true;
  zones[ZONE_SIX].sections[0].sectionId = 0;
  zones[ZONE_SIX].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[0].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[1].active = true;
  zones[ZONE_SIX].sections[1].sectionId = 1;
  zones[ZONE_SIX].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[1].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[2].active = true;
  zones[ZONE_SIX].sections[2].sectionId = 2;
  zones[ZONE_SIX].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[2].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[3].active = true;
  zones[ZONE_SIX].sections[3].sectionId = 3;
  zones[ZONE_SIX].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[3].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[4].active = true;
  zones[ZONE_SIX].sections[4].sectionId = 4;
  zones[ZONE_SIX].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[4].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[5].active = true;
  zones[ZONE_SIX].sections[5].sectionId = 5;
  zones[ZONE_SIX].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[5].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[6].active = true;
  zones[ZONE_SIX].sections[6].sectionId = 6;
  zones[ZONE_SIX].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[6].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[7].active = true;
  zones[ZONE_SIX].sections[7].sectionId = 7;
  zones[ZONE_SIX].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[7].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

  zones[ZONE_SIX].sections[8].active = true;
  zones[ZONE_SIX].sections[8].sectionId = 8;
  zones[ZONE_SIX].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[8].end  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
}
