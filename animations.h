
void Ripple(LedStrip strip);
void locator_Move();
void clearLeds();
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
void updateLeds();
void updateSectionLeds();
Animation nextAnimation();

void storeAnimationSettings();
void loadAnimationSettings();

void locator_Move()
{
  if(effect == "LED_Locator")
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
}

void clearLeds(){
  for(int idx = 0; idx < ZONE_COUNT; idx++)
    {
      if (zones[idx].active){
        fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::Black);
      }
    } 
  locator_Move();
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
Animation nextAnimation() {
  Animation pattern = zones[0].pattern;
  switch (patern) {
    case Animation.NONE:
      return Animation.DOUBLE_CRASH;
      break;
    case Animation.DOUBLE_CRASH:
      return Animation.RIPPLE;
      break;
    case Animation.RIPPLE:
      return Animation.FIRE;
      break;
    case Animation.FIRE:
      return Animation.BPM;
      break;
    case Animation.BPM:
      return Animation.FILL;
      break;
    case Animation.FILL:
      return Animation.CHASE;
      break;
    case Animation.CHASE:
      return Animation.COLOR_GLITTER;
      break;
    case Animation.COLOR_GLITTER:
      return Animation.RAINBOW;
      break;
    case Animation.RAINBOW:
      return Animation.TWINKLE;
      break;
    case Animation.TWINKLE:
      return Animation.SPOOKY_EYES;
      break;
    case Animation.SPOOKY_EYES:
      return Animation.SINGLE_RACE;
      break;
    case Animation.SINGLE_RACE:
      return Animation.BLOCKED_COLORS;
      break;
    case Animation.BLOCKED_COLORS:
      return Animation.LED_LOCATOR;
      break;
    case Animation.LED_LOCATOR:
      return Animation.NONE;
      break;
    default:
      return Animation.DOUBLE_CRASH;
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

 
void updateLeds(){
  if (showLights == true){
    for (int idx = 0; idx < ZONE_COUNT;idx++){
      if (zones[idx].active){
        switch(zones[idx].pattern){
          case RIPPLE:
            Ripple(zones[idx]);
            break;
          case CHASE:
            RGB_FILL(zones[idx]);
            break;
          case DOUBLE_CRASH:
          Crash(zones[idx]);
            break;
          case FIRE:
            for(int idy=0;idy<zones[idx].sectionCount;idy++){
              if (zones[idx].sections[idy].active){
                sectionFire(zones[idx].sections[idy]);
              }
            }
            break;
          case BPM:
          Bpm(zones[idx]);
            break;
          case FILL:
          Solid(zones[idx]);
            break;
          case COLOR_GLITTER:
          ColorGlitter(glitterChance, zones[idx]);
            break;
          case RAINBOW:
            Rainbow(zones[idx]);
            break;
          case TWINKLE:
          Twinkle(zones[idx]);
            break;
          case SPOOKY_EYES:
          Eyes(zones[idx]);
            break;
          case LED_LOCATOR:
          Locator(zones[idx]);
            break;
          case SINGLE_RACE:
            SingleRace(zones[idx]);
            break;
          case BLOCKED_COLORS:
            Blocked(zones[idx]);
            break;
          default:
            break;
        }
      }
    }
    addGlitter();
    addLightning(); 
  }else{
    for(int idx = 0; idx < ZONE_COUNT; idx ++)
    {
      if (zones[idx].active) 
      {
      fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::Black); 
      }
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
              default:
               break;
            }
          }
        }
      }
    }
    addGlitter();
    addLightning(); 
  }else{
       for(int idx = 0; idx < ZONE_COUNT; idx ++)
       {
           if (zones[idx].active) 
           {
            fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::Black); 
           }
       } 
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
    if (zones[ZONE_ONE].active)
    {
        FastLED.addLeds<WS2812B, Pin_firstZone, FIRSTZONE_COLOR_ORDER>(firstZoneLeds, ZONE_ONE_LED_COUNT);
    }

    if (zones[ZONE_TWO].active)
    {
    FastLED.addLeds<WS2812B, Pin_secondZone, SECONDZONE_COLOR_ORDER>(secondZoneLeds, ZONE_TWO_LED_COUNT);
    }

    if (zones[ZONE_THREE].active)
    {
    FastLED.addLeds<WS2812B, Pin_thirdZone, THIRDZONE_COLOR_ORDER>(thirdZoneLeds, ZONE_THREE_LED_COUNT);
    }

    if (zones[ZONE_FOUR].active)
    {
    FastLED.addLeds<WS2812B, Pin_fourthZone, FOURTHZONE_COLOR_ORDER>(fourthZoneLeds, ZONE_FOUR_LED_COUNT);
    }

    if (zones[ZONE_FIVE].active)
    {
    FastLED.addLeds<WS2812B, Pin_fifthZone, FIFTHZONE_COLOR_ORDER>(fifthZoneLeds, ZONE_FIVE_LED_COUNT);
    }
    
    if (zones[ZONE_SIX].active)
    {
    FastLED.addLeds<WS2812B, Pin_sixthZone, SIXTHZONE_COLOR_ORDER>(sixthZoneLeds, ZONE_SIX_LED_COUNT);
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
