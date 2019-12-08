
#define FIRSTZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define SECONDZONE_COLOR_ORDER          GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define THIRDZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define FOURTHZONE_COLOR_ORDER          GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 
#define FIFTHZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR
#define SIXTHZONE_COLOR_ORDER           GRB

#define ZONE_ONE_LED_COUNT 100
#define ZONE_TWO_LED_COUNT 0
#define ZONE_THREE_LED_COUNT 0
#define ZONE_FOUR_LED_COUNT 0
#define ZONE_FIVE_LED_COUNT 0
#define ZONE_SIX_LED_COUNT 0
#define MAX_LED_ZONE_COUNT 100 //led size of the biggest zone

//We could easily have more sections
#define MAX_SECTION 1

#define MAX_ZONE_COUNT 1
//Zones are limited by number
int const ZONE_ONE = 0;
int const ZONE_TWO = 1;
int const ZONE_THREE = 2;
int const ZONE_FOUR = 3;
int const ZONE_FIVE = 4;
int const ZONE_SIX = 5;
int const ZONE_COUNT = MAX_ZONE_COUNT;

#include "definitions.h"


Zone zones[MAX_ZONE_COUNT];
CRGB gAllLeds[MAX_ZONE_COUNT][MAX_LED_ZONE_COUNT];

void setupZonesStats() {
  zones[ZONE_ONE].ledCount = ZONE_ONE_LED_COUNT;
  zones[ZONE_ONE].id = ZONE_ONE;
  Serial.println((String)"Zones active: "+zones[ZONE_ONE].active);
  zones[ZONE_ONE].active = true;
  Serial.println((String)"Zones active: "+zones[ZONE_ONE].active);
  zones[ZONE_ONE].pin = 22;
  zones[ZONE_ONE].sectionCount = 1;
  zones[ZONE_ONE].leds = gAllLeds[ZONE_ONE];
  zones[ZONE_ONE].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].endIdx  =      99;         //ending LED for this zone
  zones[ZONE_ONE].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[0].active = true;
  zones[ZONE_ONE].sections[0].id = 0;
  zones[ZONE_ONE].sections[0].id = 0;
  zones[ZONE_ONE].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[0].endIdx  =      99;         //ending LED for this zone
  zones[ZONE_ONE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#if MAX_SECTIONS>1
  zones[ZONE_ONE].sections[1].active = false;
  zones[ZONE_ONE].sections[1].id = 1;
  zones[ZONE_ONE].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[1].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>2
  zones[ZONE_ONE].sections[2].active = false;
  zones[ZONE_ONE].sections[2].id = 2;
  zones[ZONE_ONE].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[2].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>3
  zones[ZONE_ONE].sections[3].active = false;
  zones[ZONE_ONE].sections[3].id = 3;
  zones[ZONE_ONE].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[3].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>4
  zones[ZONE_ONE].sections[4].active = false;
  zones[ZONE_ONE].sections[4].id = 4;
  zones[ZONE_ONE].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[4].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>5
  zones[ZONE_ONE].sections[5].active = false;
  zones[ZONE_ONE].sections[5].id = 5;
  zones[ZONE_ONE].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[5].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>6
  zones[ZONE_ONE].sections[6].active = false;
  zones[ZONE_ONE].sections[6].id = 6;
  zones[ZONE_ONE].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[6].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>7
  zones[ZONE_ONE].sections[7].active = false;
  zones[ZONE_ONE].sections[7].id = 7;
  zones[ZONE_ONE].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[7].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>8
  zones[ZONE_ONE].sections[8].active = false;
  zones[ZONE_ONE].sections[8].id = 8;
  zones[ZONE_ONE].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_ONE].sections[8].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_ONE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_ONE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif




#if MAX_ZONE_COUNT >1
  zones[ZONE_TWO].ledCount = ZONE_TWO_LED_COUNT;
  zones[ZONE_TWO].id = ZONE_TWO;
  zones[ZONE_TWO].active = false;
  zones[ZONE_TWO].pin = 4;
  zones[ZONE_TWO].sectionCount = 1;
  zones[ZONE_TWO].leds = gAllLeds[ZONE_TWO];
  zones[ZONE_TWO].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].endIdx  =      99;         //ending LED for this zone
  zones[ZONE_TWO].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[0].active = false;
  zones[ZONE_TWO].sections[0].id = 0;
  zones[ZONE_TWO].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[0].endIdx  =      1000;         //ending LED for this zone
  zones[ZONE_TWO].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

#if MAX_SECTIONS>1
  zones[ZONE_TWO].sections[1].active = true;
  zones[ZONE_TWO].sections[1].id = 1;
  zones[ZONE_TWO].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[1].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>2
  zones[ZONE_TWO].sections[2].active = true;
  zones[ZONE_TWO].sections[2].id = 2;
  zones[ZONE_TWO].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[2].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>3
  zones[ZONE_TWO].sections[3].active = true;
  zones[ZONE_TWO].sections[3].id = 3;
  zones[ZONE_TWO].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[3].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>4
  zones[ZONE_TWO].sections[4].active = true;
  zones[ZONE_TWO].sections[4].id = 4;
  zones[ZONE_TWO].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[4].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>5
  zones[ZONE_TWO].sections[5].active = true;
  zones[ZONE_TWO].sections[5].id = 5;
  zones[ZONE_TWO].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[5].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>6
  zones[ZONE_TWO].sections[6].active = true;
  zones[ZONE_TWO].sections[6].id = 6;
  zones[ZONE_TWO].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[6].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>7
  zones[ZONE_TWO].sections[7].active = true;
  zones[ZONE_TWO].sections[7].id = 7;
  zones[ZONE_TWO].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[7].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>8
  zones[ZONE_TWO].sections[8].active = true;
  zones[ZONE_TWO].sections[8].id = 8;
  zones[ZONE_TWO].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_TWO].sections[8].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_TWO].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_TWO].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif
#endif //End zone 2


#if MAX_ZONE_COUNT >2
  zones[ZONE_THREE].ledCount = ZONE_THREE_LED_COUNT;
  zones[ZONE_THREE_LED_COUNT].id = ZONE_THREE_LED_COUNT;
  zones[ZONE_THREE].active = false;
  zones[ZONE_THREE].pin = 0;
  zones[ZONE_THREE].sectionCount = 9;
  zones[ZONE_THREE].leds = gAllLeds[ZONE_THREE];
  zones[ZONE_THREE].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].endIdx  =      99;         //ending LED for this zone
  zones[ZONE_THREE].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[0].active = true;
  zones[ZONE_THREE].sections[0].id = 0;
  zones[ZONE_THREE].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[0].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

#if MAX_SECTIONS>1
  zones[ZONE_THREE].sections[1].active = true;
  zones[ZONE_THREE].sections[1].id = 1;
  zones[ZONE_THREE].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[1].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>2
  zones[ZONE_THREE].sections[2].active = true;
  zones[ZONE_THREE].sections[2].id = 2;
  zones[ZONE_THREE].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[2].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>3
  zones[ZONE_THREE].sections[3].active = true;
  zones[ZONE_THREE].sections[3].id = 3;
  zones[ZONE_THREE].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[3].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>4
  zones[ZONE_THREE].sections[4].active = true;
  zones[ZONE_THREE].sections[4].id = 4;
  zones[ZONE_THREE].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[4].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>5
  zones[ZONE_THREE].sections[5].active = true;
  zones[ZONE_THREE].sections[5].id = 5;
  zones[ZONE_THREE].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[5].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>6
  zones[ZONE_THREE].sections[6].active = true;
  zones[ZONE_THREE].sections[6].id = 6;
  zones[ZONE_THREE].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[6].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>7
  zones[ZONE_THREE].sections[7].active = true;
  zones[ZONE_THREE].sections[7].id = 7;
  zones[ZONE_THREE].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[7].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>8
  zones[ZONE_THREE].sections[8].active = true;
  zones[ZONE_THREE].sections[8].id = 8;
  zones[ZONE_THREE].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_THREE].sections[8].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_THREE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_THREE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif
#endif //End zone 3


#if MAX_ZONE_COUNT >3
  zones[ZONE_FOUR].ledCount = ZONE_FOUR_LED_COUNT;
  zones[ZONE_FOUR_LED_COUNT].id = ZONE_FOUR_LED_COUNT;
  zones[ZONE_FOUR].active = false;
  zones[ZONE_FOUR].pin = 14;
  zones[ZONE_FOUR].sectionCount = 9;
  zones[ZONE_FOUR].leds = gAllLeds[ZONE_FOUR];
  zones[ZONE_FOUR].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].endIdx  =      99;         //ending LED for this zone
  zones[ZONE_FOUR].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[0].active = true;
  zones[ZONE_FOUR].sections[0].id = 0;
  zones[ZONE_FOUR].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[0].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

#if MAX_SECTIONS>1
  zones[ZONE_FOUR].sections[1].active = true;
  zones[ZONE_FOUR].sections[1].id = 1;
  zones[ZONE_FOUR].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[1].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>2
  zones[ZONE_FOUR].sections[2].active = true;
  zones[ZONE_FOUR].sections[2].id = 2;
  zones[ZONE_FOUR].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[2].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>3
  zones[ZONE_FOUR].sections[3].active = true;
  zones[ZONE_FOUR].sections[3].id = 3;
  zones[ZONE_FOUR].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[3].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>4
  zones[ZONE_FOUR].sections[4].active = true;
  zones[ZONE_FOUR].sections[4].id = 4;
  zones[ZONE_FOUR].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[4].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>5
  zones[ZONE_FOUR].sections[5].active = true;
  zones[ZONE_FOUR].sections[5].id = 5;
  zones[ZONE_FOUR].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[5].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>6
  zones[ZONE_FOUR].sections[6].active = true;
  zones[ZONE_FOUR].sections[6].id = 6;
  zones[ZONE_FOUR].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[6].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>7
  zones[ZONE_FOUR].sections[7].active = true;
  zones[ZONE_FOUR].sections[7].id = 7;
  zones[ZONE_FOUR].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[7].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>8
  zones[ZONE_FOUR].sections[8].active = true;
  zones[ZONE_FOUR].sections[8].id = 8;
  zones[ZONE_FOUR].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_FOUR].sections[8].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FOUR].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FOUR].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif
#endif //End zone 4


#if MAX_ZONE_COUNT >4
  zones[ZONE_FIVE].ledCount = ZONE_FIVE_LED_COUNT;
  zones[ZONE_FIVE_LED_COUNT].id = ZONE_FIVE_LED_COUNT;
  zones[ZONE_FIVE].active = false;
  zones[ZONE_FIVE].pin = 12;
  zones[ZONE_FIVE].sectionCount = 9;
  zones[ZONE_FIVE].leds = gAllLeds[ZONE_FIVE];
  zones[ZONE_FIVE].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].endIdx  =      99;         //ending LED for this zone
  zones[ZONE_FIVE].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[0].active = true;
  zones[ZONE_FIVE].sections[0].id = 0;
  zones[ZONE_FIVE].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[0].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

#if MAX_SECTIONS>1
  zones[ZONE_FIVE].sections[1].active = true;
  zones[ZONE_FIVE].sections[1].id = 1;
  zones[ZONE_FIVE].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[1].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>2
  zones[ZONE_FIVE].sections[2].active = true;
  zones[ZONE_FIVE].sections[2].id = 2;
  zones[ZONE_FIVE].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[2].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>3
  zones[ZONE_FIVE].sections[3].active = true;
  zones[ZONE_FIVE].sections[3].id = 3;
  zones[ZONE_FIVE].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[3].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>4
  zones[ZONE_FIVE].sections[4].active = true;
  zones[ZONE_FIVE].sections[4].id = 4;
  zones[ZONE_FIVE].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[4].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>5
  zones[ZONE_FIVE].sections[5].active = true;
  zones[ZONE_FIVE].sections[5].id = 5;
  zones[ZONE_FIVE].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[5].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>6
  zones[ZONE_FIVE].sections[6].active = true;
  zones[ZONE_FIVE].sections[6].id = 6;
  zones[ZONE_FIVE].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[6].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>7
  zones[ZONE_FIVE].sections[7].active = true;
  zones[ZONE_FIVE].sections[7].id = 7;
  zones[ZONE_FIVE].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[7].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>8
  zones[ZONE_FIVE].sections[8].active = true;
  zones[ZONE_FIVE].sections[8].id = 8;
  zones[ZONE_FIVE].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_FIVE].sections[8].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_FIVE].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_FIVE].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif
#endif //End zone 5


#if MAX_ZONE_COUNT >5
  zones[ZONE_SIX].ledCount = ZONE_SIX_LED_COUNT;
  zones[ZONE_SIX_LED_COUNT].id = ZONE_SIX_LED_COUNT;
  zones[ZONE_SIX].active = false;
  zones[ZONE_SIX].pin = 13;
  zones[ZONE_SIX].sectionCount = 9;
  zones[ZONE_SIX].leds = gAllLeds[ZONE_SIX];
  zones[ZONE_SIX].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].endIdx  =      99;         //ending LED for this zone
  zones[ZONE_SIX].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[0].active = true;
  zones[ZONE_SIX].sections[0].id = 0;
  zones[ZONE_SIX].sections[0].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[0].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[0].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[0].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes

#if MAX_SECTIONS>1
  zones[ZONE_SIX].sections[1].active = true;
  zones[ZONE_SIX].sections[1].id = 1;
  zones[ZONE_SIX].sections[1].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[1].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[1].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[1].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>2
  zones[ZONE_SIX].sections[2].active = true;
  zones[ZONE_SIX].sections[2].id = 2;
  zones[ZONE_SIX].sections[2].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[2].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[2].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[2].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>3
  zones[ZONE_SIX].sections[3].active = true;
  zones[ZONE_SIX].sections[3].id = 3;
  zones[ZONE_SIX].sections[3].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[3].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[3].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[3].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>4
  zones[ZONE_SIX].sections[4].active = true;
  zones[ZONE_SIX].sections[4].id = 4;
  zones[ZONE_SIX].sections[4].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[4].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[4].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[4].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>5
  zones[ZONE_SIX].sections[5].active = true;
  zones[ZONE_SIX].sections[5].id = 5;
  zones[ZONE_SIX].sections[5].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[5].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[5].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[5].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>6
  zones[ZONE_SIX].sections[6].active = true;
  zones[ZONE_SIX].sections[6].id = 6;
  zones[ZONE_SIX].sections[6].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[6].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[6].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[6].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>7
  zones[ZONE_SIX].sections[7].active = true;
  zones[ZONE_SIX].sections[7].id = 7;
  zones[ZONE_SIX].sections[7].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[7].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[7].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[7].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if MAX_SECTIONS>8
  zones[ZONE_SIX].sections[8].active = true;
  zones[ZONE_SIX].sections[8].id = 8;
  zones[ZONE_SIX].sections[8].start  =    0;           //starting LED for this zone
  zones[ZONE_SIX].sections[8].endIdx  =      100;         //ending LED for this zone
  zones[ZONE_SIX].sections[8].fireStart  =       1;           //would you like fire to begin from this point? 0 = no 1 = yes
  zones[ZONE_SIX].sections[8].fireEnd  =         1;           //would you like fire to begin from this point? 0 = no 1 = yes
#endif
#endif //End zone 6
}
