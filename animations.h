void Ripple(LedStrip strip);
void locator_Move();
void clearLeds();
void clearLeds(LedStrip strip);
Animation getPattern(String effect);
void RGB_FILL(LedStrip strip);
void ColorGlitter( fract8 chanceOfGlitter, LedStrip strip);
void SingleRace(LedStrip strip);
void Crash(LedStrip strip);
void Rainbow(LedStrip strip);
void Blocked(LedStrip strip);
void Bpm(LedStrip strip);
void Twinkle(LedStrip strip);
void Eyes(LedStrip strip);
void Solid(LedStrip strip);
void Locator(LedStrip strip);
void sectionFire(LedStrip strip);
void addLightning();
void addGlitter();
void setupLeds();
void chase();
void checkIn(); 
void updateZoneLeds();
void updateSectionLeds();
Animation nextAnimation();

void storeAnimationSettings();
void loadAnimationSettings();

void calculateMax()
{
    maxLEDs=0;
  for (int idx =0; idx < ZONE_COUNT; idx ++)
  {
    maxLEDs = max(maxLEDs,zones[idx].ledCount);
  }
}
void locator_Move()
{
  if(locatorLED <= maxLEDs)
  {
    String temp_str = String(locatorLED);
    temp_str.toCharArray(MQTT_locatorLED, temp_str.length() + 1);
    client.publish(USER_MQTT_CLIENT_NAME"/locator", MQTT_locatorLED);
    locatorLED++;    
  }
  else
  {
    locatorLED = 0;
  }
  timer.setTimeout(locatorDelay, locator_Move);
}

void clearLeds(){
  for(int idx = 0; idx < ZONE_COUNT; idx++)
    {
      clearLeds(zones[idx]);
    } 
}


void clearLeds(LedStrip strip){
  if (strip.active){
    fill_solid(strip.leds, strip.ledCount, CRGB::Black);
  }
}


Animation getPattern(String effect){
  Animation result = RAINBOW;
  if (effect == "Rainbow"){
    result = RAINBOW;
  }else if (effect == "Spooky_Eyes"){
    result = SPOOKY_EYES;
  }else if (effect == "Color_Chase"){
    result = CHASE;
  }else if (effect == "Color_Glitter"){
    result = COLOR_GLITTER;
  }else if (effect == "Single_Race"){
    result = SINGLE_RACE;
  }else if (effect == "Double_Crash"){
    result = DOUBLE_CRASH;
  }else if (effect == "Blocked_Colors"){
    result = BLOCKED_COLORS;
  }else if (effect == "BPM"){
    result = BPM;
  }else if (effect == "Twinkle"){
    result = TWINKLE;
  }else if (effect == "Fill_Solid"){
    result = FILL;
  }else if (effect == "LED_Locator"){
    result = LED_LOCATOR;
  }else if (effect == "Ripple"){
    result = RIPPLE;
  }else if (effect == "Fire"){
    result = FIRE;
  }

  return result;
}
void setZonesNextAnimation(){
  Animation pattern = nextAnimation();
  for(int idx = 0; idx < ZONE_COUNT;idx++){
    Serial.println((String)"Setting zone "+idx+" to pattern :"+pattern); 
    zones[idx].pattern = pattern;
  }
}
Animation nextAnimation() {
  Animation pattern = zones[0].pattern;
  switch (pattern) {
    case NONE:
      return DOUBLE_CRASH;
      break;
    case DOUBLE_CRASH:
      return RIPPLE;
      break;
    case RIPPLE:
      return FIRE;
      break;
    case FIRE:
      return BPM;
      break;
    case BPM:
      return FILL;
      break;
    case FILL:
      return CHASE;
      break;
    case CHASE:
      return COLOR_GLITTER;
      break;
    case COLOR_GLITTER:
      return RAINBOW;
      break;
    case RAINBOW:
      return TWINKLE;
      break;
    case TWINKLE:
      return SPOOKY_EYES;
      break;
    case SPOOKY_EYES:
      return SINGLE_RACE;
      break;
    case SINGLE_RACE:
      return BLOCKED_COLORS;
      break;
    case BLOCKED_COLORS:
      locator_Move();
      return LED_LOCATOR;
      break;
    case LED_LOCATOR:
    default:
      return DOUBLE_CRASH;
  }
  
}
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/


void chase()
{
  if(startPosition == 5)
  {
    startPosition = 0;
  }
  else
  {
    startPosition++;
  }
  timer.setTimeout(chaseDelay, chase);
}

void checkIn()
{
  client.publish(USER_MQTT_CLIENT_NAME"/checkIn","OK");
  timer.setTimeout(120000, checkIn);
}

 
void updateZoneLeds(){
  if (showLights == true){
    for (int idx = 0; idx < ZONE_COUNT;idx++){
      if (zones[idx].active){
        Serial.println((String)"Setting pattern for Zone "+idx);
        switch(zones[idx].pattern){
          case RIPPLE:
          Serial.println("Ripple");
            Ripple(zones[idx]);
            break;
          case CHASE:
          Serial.println("RGB_FILL");
            RGB_FILL(zones[idx]);
            break;
          case DOUBLE_CRASH:
          Serial.println("Crash");
          Crash(zones[idx]);
            break;
          case FIRE:
          Serial.println("FIRE");
            for(int idy=0;idy<zones[idx].sectionCount;idy++){
              if (zones[idx].sections[idy].active){
                sectionFire(zones[idx].sections[idy]);
              }
            }
            break;
          case BPM:
          Serial.println("Bpm");
          Bpm(zones[idx]);
            break;
          case FILL:
          Serial.println("Solid");
          Solid(zones[idx]);
            break;
          case COLOR_GLITTER:
          Serial.println("ColorGlitter");
          ColorGlitter(glitterChance, zones[idx]);
            break;
          case RAINBOW:
          Serial.println("Rainbow");
            Rainbow(zones[idx]);
            break;
          case TWINKLE:
          Serial.println("Twinkle");
          Twinkle(zones[idx]);
            break;
          case SPOOKY_EYES:
          Serial.println("Eyes");
          Eyes(zones[idx]);
            break;
          case LED_LOCATOR:
          Serial.println("Locator");
          Locator(zones[idx]);
            break;
          case SINGLE_RACE:
          Serial.println("SingleRace");
            SingleRace(zones[idx]);
            break;
          case BLOCKED_COLORS:
          Serial.println("Blocked");
            Blocked(zones[idx]);
            break;
          case NONE:
          default:
            clearLeds(zones[idx]);
            break;
        }
      }
    }
    addGlitter();
    addLightning(); 
  }else{
    for(int idx = 0; idx < ZONE_COUNT; idx ++)
    {
      clearLeds();
    } 
  }
} 


void updateSectionLeds(){
  if (showLights == true){
    for (int idx = 0; idx < ZONE_COUNT;idx++){
      if (zones[idx].active){
        for(int idy = 0; idy < zones[idx].sectionCount; idy++){
          if (zones[idx].sections[idy].active){
            switch(zones[idx].sections[idy].pattern){
              case RIPPLE:
                Ripple(zones[idx].sections[idy]);
                break;
              case CHASE:
                RGB_FILL(zones[idx].sections[idy]);
                break;
              case DOUBLE_CRASH:
              Crash(zones[idx].sections[idy]);
                break;
              case FIRE:
                sectionFire(zones[idx].sections[idy]);
                break;
              case BPM:
              Bpm(zones[idx].sections[idy]);
                break;
              case FILL:
              Solid(zones[idx].sections[idy]);
                break;
              case COLOR_GLITTER:
              ColorGlitter(glitterChance, zones[idx].sections[idy]);
                break;
              case RAINBOW:
               Rainbow(zones[idx].sections[idy]);
                break;
              case TWINKLE:
              Twinkle(zones[idx].sections[idy]);
                break;
              case SPOOKY_EYES:
              Eyes(zones[idx].sections[idy]);
                break;
              case LED_LOCATOR:
              Locator(zones[idx].sections[idy]);
                break;
              case SINGLE_RACE:
                SingleRace(zones[idx].sections[idy]);
                break;
              case BLOCKED_COLORS:
                Blocked(zones[idx].sections[idy]);
                break;
              case NONE:
              default:
                clearLeds(zones[idx].sections[idy]);
               break;
            }
          }
        }
      }
    }
    addGlitter();
    addLightning(); 
  }else{
       clearLeds();
  }
}

/*********************** PATTERN MODIFIERS ***************************/
/*********************** PATTERN MODIFIERS ***************************/
/*********************** PATTERN MODIFIERS ***************************/
/*********************** PATTERN MODIFIERS ***************************/
/*********************** PATTERN MODIFIERS ***************************/

void addLightning()
{
  if(showLightning && showLights)
  {
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fadeToBlackBy(zones[idx].leds, zones[idx].ledCount, 1); 
           }
       } 
    
    unsigned int chance = random16();
    if( chance > lightningChance) 
    {
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::White); 
           }
       }
      lightning = 20;
      if(audioEffects )
      {
        int thunder = random8();
        if( thunder > 128)
        {
          client.publish("Audio","2");
        }
        if( thunder < 127)
        {
          client.publish("Audio","1");
        }
      }
    }
    if(lightning != 1)
    {
      if(lightning > 15)
      {
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fadeToBlackBy(zones[idx].leds, zones[idx].ledCount, 1); 
           }
       }
        lightning--;
      }
      if(lightning == 15)
      {

       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::White); 
           }
       }
        lightning--; 
      }
      if(lightning > 5 && lightning < 15)
      {
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fadeToBlackBy(zones[idx].leds, zones[idx].ledCount, 150); 
           }
       }
        lightning--;
      }
      if(lightning == 5)
      {
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::White); 
           }
       }
        lightning--; 
      }
      if(lightning > 0 && lightning < 5)
      {
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fadeToBlackBy(zones[idx].leds, zones[idx].ledCount, 150); 
           }
       }
        lightning--;
      }
    }
  }
}

void addGlitter()
{
  if(showGlitter && showLights)
  {     
    if( random8() < glitterFrequency) 
    {
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            zones[idx].leds[random16(zones[idx].ledCount)]= CRGB(redG, greenG, blueG); 
           }
       }
    }
  }
}

void setupLeds()
{
    Serial.println("Setting up zone leds");
    if (zones[ZONE_ONE].active && ZONE_ONE_LED_COUNT >0)
    {
        Serial.println("Setting up zone 1 leds");
        Serial.println(Pin_firstZone);
        Serial.println(FIRSTZONE_COLOR_ORDER);
        LEDS.addLeds<WS2812, Pin_firstZone, FIRSTZONE_COLOR_ORDER>(AllLeds[0], ZONE_ONE_LED_COUNT);
    }

    if (zones[ZONE_TWO].active && ZONE_TWO_LED_COUNT >0)
    {
        Serial.println("Setting up zone 2 leds");
      LEDS.addLeds<WS2812, Pin_secondZone, SECONDZONE_COLOR_ORDER>(AllLeds[1], ZONE_TWO_LED_COUNT);
    }

    if (zones[ZONE_THREE].active && ZONE_THREE_LED_COUNT >0)
    {
        Serial.println("Setting up zone 3 leds");
      LEDS.addLeds<WS2812B, Pin_thirdZone, THIRDZONE_COLOR_ORDER>(AllLeds[2], ZONE_THREE_LED_COUNT);
    }

    if (zones[ZONE_FOUR].active && ZONE_FOUR_LED_COUNT >0)
    {
        Serial.println("Setting up zone 4 leds");
      LEDS.addLeds<WS2812B, Pin_fourthZone, FOURTHZONE_COLOR_ORDER>(AllLeds[3], ZONE_FOUR_LED_COUNT);
    }

    if (zones[ZONE_FIVE].active && ZONE_FIVE_LED_COUNT >0)
    {
        Serial.println("Setting up zone 5 leds");
      LEDS.addLeds<WS2812B, Pin_fifthZone, FIFTHZONE_COLOR_ORDER>(AllLeds[4], ZONE_FIVE_LED_COUNT);
    }
    
    if (zones[ZONE_SIX].active && ZONE_SIX_LED_COUNT >0)
    {
        Serial.println("Setting up zone 6 leds");
      LEDS.addLeds<WS2812B, Pin_sixthZone, SIXTHZONE_COLOR_ORDER>(AllLeds[5], ZONE_SIX_LED_COUNT);
    }
}




/*****************   Animations  ****************************************/
/*****************   Animations  ****************************************/
/*****************   Animations  ****************************************/
/*****************   Animations  ****************************************/
/*****************   Animations  ****************************************/

void Ripple(LedStrip strip)
{
  int start = strip.start;
  int end = strip.end;
  int ledCount = strip.ledCount;
  for (int idx = start; idx < end; idx++)
  {
    strip.leds[idx] = CRGB((red2/75), (green2/75), (blue2/75));
  }   
  switch (strip.steps) 
  {
    case -1:                                                          
      strip.center = random16(ledCount);
      strip.steps = 0;
      break;
    case 0:
      strip.leds[strip.center] = CRGB(red1, green1, blue1);                          
      strip.steps ++;
      break;
    case 12:                                                   
      strip.steps = -1;
      break;
    default:                                                             // Middle of the ripples.
      strip.leds[start+((strip.center + strip.steps + ledCount) % ledCount)] += CRGB((red1/(strip.steps * 5)), (green1/(strip.steps * 5)), (blue1/(strip.steps * 5)));
      strip.leds[start+((strip.center - strip.steps + ledCount) % ledCount)] += CRGB((red1/(strip.steps * 5)), (green1/(strip.steps * 5)), (blue1/(strip.steps * 5)));
      strip.steps ++;                                                         
      break;
  }
}

void RGB_FILL(LedStrip strip)
{
  if(startPosition < 6)
  {
    fadeToBlackBy( strip.leds, strip.ledCount, 80);
    for(int pixel = startPosition+1; pixel < strip.ledCount; pixel+=6)  
    {
      if(pixel <= strip.ledCount)
      {
        strip.leds[pixel] = CRGB(red1,green1,blue1);
      }
    }
    for(int pixel = startPosition+3; pixel < strip.ledCount; pixel+=6)
    {
      if(pixel <= strip.ledCount)
      {
        strip.leds[pixel] = CRGB(red2,green2,blue2);
      }
    }
    for(int pixel = startPosition+5; pixel < strip.ledCount; pixel+=6)
    {
      if(pixel <= strip.ledCount)
      {
        strip.leds[pixel] = CRGB(red3,green3,blue3);
      } 
    }
  }
  if(startPosition == 1)
  {
    strip.leds[0]=CRGB(red3,green3,blue3);
  }
  if(startPosition == 2)
  {
    strip.leds[1]=CRGB(red3,green3,blue3);
  }
  if(startPosition == 3)
  {
    strip.leds[2]=CRGB(red3,green3,blue3);
    strip.leds[0]=CRGB(red2,green2,blue2);
  }
  if(startPosition == 4)
  {
    strip.leds[3]=CRGB(red3,green3,blue3);
    strip.leds[1]=CRGB(red2,green2,blue2);
  }
  if(startPosition == 5)
  {
    strip.leds[4]=CRGB(red3,green3,blue3);
    strip.leds[2]=CRGB(red2,green2,blue2);
    strip.leds[0]=CRGB(red1,green1,blue1);
  }
}

void ColorGlitter( fract8 chanceOfGlitter, LedStrip strip) 
{
  fadeToBlackBy( strip.leds, strip.ledCount, 2);
  if(startPosition == 0)
  {
    if( random8() < chanceOfGlitter) 
    {
    strip.leds[ random16(strip.ledCount) ] += CRGB::Red;
    }
  }
  if(startPosition == 1)
  {
    if( random8() < chanceOfGlitter) 
    {
    strip.leds[ random16(strip.ledCount) ] += CRGB::Orange;
    }
  }
  if(startPosition == 2)
  {
    if( random8() < chanceOfGlitter) 
    {
    strip.leds[ random16(strip.ledCount) ] += CRGB::Yellow;
    }  
  }
  if(startPosition == 3)
  {
    if( random8() < chanceOfGlitter) 
    {
    strip.leds[ random16(strip.ledCount) ] += CRGB::Green;
    }
  }
  if(startPosition == 4)
  {
    if( random8() < chanceOfGlitter) 
    {
    strip.leds[ random16(strip.ledCount) ] += CRGB::Blue;
    }
  }
  if(startPosition == 5)
  {
    if( random8() < chanceOfGlitter) 
    {
    strip.leds[ random16(strip.ledCount) ] += CRGB::Violet;
    }
  } 
}

void SingleRace(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 1);
  int pos = beatsin16( raceSpeed, 0, strip.ledCount);
  if(pos > strip.previousLed)
  {
    strip.leds[pos] = CRGB(red1,green1,blue1);
    strip.previousLed = pos;
  }
  if(pos < strip.previousLed)
  {
    strip.leds[pos] = CRGB(red2,green2,blue2);
    strip.previousLed = pos;
  }                 
}

void Crash(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 15);
  if (strip.active){
    int pos = beatsin16( raceSpeed, 0, (strip.end - strip.start ));
    strip.leds[strip.start + pos] = CRGB(red1,green1,blue1);
    strip.leds[strip.end - pos] = CRGB(red2,green2,blue2);
  }
}

void Rainbow(LedStrip strip)
{
  Serial.println(strip.ledCount);
  Serial.println(gHue);
  Serial.println(numberOfRainbows);
  fill_rainbow( strip.leds,strip.ledCount, gHue, numberOfRainbows);
}

void Blocked(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 2);
  for( int mark = 0; mark < strip.ledCount; mark+=30)
  {
    for( int i = 0; i < 9; i++) 
    {
      if(startPosition == 0 || startPosition == 1)
      {
        if(i+mark <= strip.ledCount)
        {
          strip.leds[i+mark] = CRGB(red1,green1,blue1);
        }
        if(i+10+mark <= strip.ledCount)
        {
          strip.leds[i+10+mark] = CRGB(red2,green2,blue2);
        }
        if(i+20+mark <= strip.ledCount)
        {
          strip.leds[i+20+mark] = CRGB(red3,green3,blue3);
        }
      }
      if(startPosition == 2 || startPosition == 3)
      {
        if(i+mark <= strip.ledCount)
        {
          strip.leds[i+mark] = CRGB(red2,green2,blue2);
        }
        if(i+10+mark <= strip.ledCount)
        {
          strip.leds[i+10+mark] = CRGB(red3,green3,blue3);
        }
        if(i+20+mark <= strip.ledCount)
        {
          strip.leds[i+20+mark] = CRGB(red1,green1,blue1);
        }
      }
      if(startPosition == 4 || startPosition == 5)
      {
        if(i+mark <= strip.ledCount)
        {
          strip.leds[i+mark] = CRGB(red3,green3,blue3);
        }
        if(i+10+mark <= strip.ledCount)
        {
          strip.leds[i+10+mark] = CRGB(red1,green1,blue1);
        }
        if(i+20+mark <= strip.ledCount)
        {
          strip.leds[i+20+mark] = CRGB(red2,green2,blue2);
        }
      }
    }
  }
}

void Bpm(LedStrip strip)
{
  if((red1*2) > (green1 + blue1))
  {
    CRGBPalette16 palette_Zone = LavaColors_p; 
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for( int i = 0; i < strip.ledCount; i++) 
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue+(i*2), beat-gHue+(i*10));
    } 
  }
  if((green1*2) > (red1 + blue1))
  {
    CRGBPalette16 palette_Zone = ForestColors_p; 
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for( int i = 0; i < strip.ledCount; i++) 
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue+(i*2), beat-gHue+(i*10));
    } 
  }
  if((blue1*2) > (green1 + red1))
  {
    CRGBPalette16 palette_Zone = CloudColors_p; 
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for( int i = 0; i < strip.ledCount; i++) 
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue+(i*2), beat-gHue+(i*10));
    } 
  }
  if((blue1*2) == (green1 + red1))
  {
    CRGBPalette16 palette_Zone = PartyColors_p; 
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for( int i = 0; i < strip.ledCount; i++) 
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue+(i*2), beat-gHue+(i*10));
    } 
  }
}

void Twinkle(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 80);
  for( int i = 0; i < strip.ledCount-5; i+=5)
  {
    if(i <= strip.ledCount)
    {
      if (random8() > twinkleChance)
      {
        strip.leds[i] = CRGB( red1, green1, blue1);
      }
      else
      {
        strip.leds[i] = CRGB( 150, 100, 40);
      }  
    }
  }                     
}

void Eyes(LedStrip strip)
{
  unsigned int chance = random8();
  if( chance > eyeChance) 
  {
    unsigned int eye = random16(strip.ledCount);  
    strip.leds[eye] = CRGB(red1,green1,blue1);
    strip.leds[eye-4] = CRGB(red1,green1,blue1);
  }
  if( chance > 39) 
  {
    fadeToBlackBy( strip.leds, strip.ledCount, 10);
  }
}

void Solid(LedStrip strip)
{
  fill_solid(strip.leds, strip.ledCount, CRGB(red1, green1, blue1));
}

void Locator(LedStrip strip)
{
  if(locatorLED <= strip.ledCount)
  {
    fill_solid(strip.leds, strip.ledCount, CRGB::Black); 
    strip.leds[locatorLED]=CRGB(red1, green1, blue1);
  }
}

   void sectionFire(LedStrip strip)
   {
//     int sectionEnd = zone.sections[section].sectionEnd;
//     int sectionStart = zone.sections[section].sectionStart;
//     const int size = sectionEnd - sectionStart;
//     static byte heat[size];
//     for( int i = 0; i < size; i++) 
//     {
//       heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / size) + 2));
//     }
//  
//     for( int k= size - 1; k >= 2; k--) 
//     {
//       heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
//     }
//     if( random8() < SPARKING ) 
//     {
//       int y = random8(7);
//       heat[y] = qadd8( heat[y], random8(160,255) );
//     }
//     for( int j = 0; j < size; j++) 
//     {
//       byte colorindex = scale8( heat[j], 240);
//       CRGB color = ColorFromPalette( gPal, colorindex);
//       int pixelnumber;
//       if( gReverseDirection ) {
//         pixelnumber = (size -1) - j;
//       } else {
//         pixelnumber = j;
//       }
//       int thisFlame = ((pixelnumber * firesize)/100);
//      
//       if (zone.sections[section].fireStart==1)
//       {
//           if(thisFlame <=  size)
//           {
//           leds[sectionStart + thisFlame] = color;
//           }
//       }
//      
//       if(zone.sections[section].fireEnd==1)
//       {
//           if(thisFlame <=  size )
//           {
//             leds[sectionEnd - thisFlame] = color;
//           }
//       }
//     }
   }


void storeAnimationSettings(){
  //Store the Settings to NVM
}

void loadAnimationSettings(){
  //TODO: Load the settings from NVM
}
