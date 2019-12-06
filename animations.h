void locator_Move();
void clearLeds();
void clearLeds(LedStrip strip);
Animation getPattern(String effect);
void rippleAnimation(LedStrip strip);
void rgbFillAnimation(LedStrip strip);
void colorGlitterAnimation( fract8 chanceOfGlitter, LedStrip strip);
void singleRaceAnimation(LedStrip strip);
void crashAnimation(LedStrip strip);
void rainbowAnimation(LedStrip strip);
void blockedAnimation(LedStrip strip);
void bpmAnimation(LedStrip strip);
void twinkleAnimation(LedStrip strip);
void eyesAnimation(LedStrip strip);
void solidAnimation(LedStrip strip);
void locatorAnimation(LedStrip strip);
void sectionFireAnimation(LedStrip strip);
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
  maxLEDs = 0;
  for (int idx = 0; idx < ZONE_COUNT; idx ++)
  {
    maxLEDs = max(maxLEDs, zones[idx].ledCount);
  }
}
void locator_Move()
{
  if (locatorLED <= maxLEDs)
  {
    String temp_str = String(locatorLED);
    temp_str.toCharArray(MQTT_locatorLED, temp_str.length() + 1);
    mqttClient.publish(USER_MQTT_CLIENT_NAME"/locator", MQTT_locatorLED);
    locatorLED++;
  }
  else
  {
    locatorLED = 0;
  }
  timer.setTimeout(locatorDelay, locator_Move);
}

void clearLeds() {
  for (int idx = 0; idx < ZONE_COUNT; idx++)
  {
    clearLeds(zones[idx]);
  }
}


void clearLeds(LedStrip strip) {
  if (strip.active) {
    fill_solid(strip.leds, strip.ledCount, CRGB::Black);
  }
}


Animation getPattern(String effect) {
  Animation result = RAINBOW;
  if (effect == "Rainbow") {
    result = RAINBOW;
  } else if (effect == "Spooky_Eyes") {
    result = SPOOKY_EYES;
  } else if (effect == "Color_Chase") {
    result = CHASE;
  } else if (effect == "Color_Glitter") {
    result = COLOR_GLITTER;
  } else if (effect == "Single_Race") {
    result = SINGLE_RACE;
  } else if (effect == "Double_Crash") {
    result = DOUBLE_CRASH;
  } else if (effect == "Blocked_Colors") {
    result = BLOCKED_COLORS;
  } else if (effect == "BPM") {
    result = BPM;
  } else if (effect == "Twinkle") {
    result = TWINKLE;
  } else if (effect == "Fill_Solid") {
    result = FILL;
  } else if (effect == "LED_Locator") {
    result = LED_LOCATOR;
  } else if (effect == "Ripple") {
    result = RIPPLE;
  } else if (effect == "Fire") {
    result = FIRE;
  }

  return result;
}
void setZonesNextAnimation() {
  Animation pattern = nextAnimation();
  for (int idx = 0; idx < ZONE_COUNT; idx++) {
    Serial.println((String)"Setting zone " + idx + " to pattern :" + pattern);
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
  if (startPosition == 5)
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
  mqttClient.publish(USER_MQTT_CLIENT_NAME"/checkIn", "OK");
  timer.setTimeout(120000, checkIn);
}


void updateZoneLeds() {
  if (showLights == true) {
    for (int idx = 0; idx < ZONE_COUNT; idx++) {
      if (zones[idx].active) {
        Serial.println((String)"Setting pattern for Zone " + idx);
        switch (zones[idx].pattern) {
          case RIPPLE:
            Serial.println("Ripple");
            rippleAnimation(zones[idx]);
            break;
          case CHASE:
            Serial.println("RGB_FILL");
            rgbFillAnimation(zones[idx]);
            break;
          case DOUBLE_CRASH:
            Serial.println("Crash");
            crashAnimation(zones[idx]);
            break;
          case FIRE:
            Serial.println("FIRE");
            for (int idy = 0; idy < zones[idx].sectionCount; idy++) {
              if (zones[idx].sections[idy].active) {
                sectionFireAnimation(zones[idx].sections[idy]);
              }
            }
            break;
          case BPM:
            Serial.println("Bpm");
            bpmAnimation(zones[idx]);
            break;
          case FILL:
            Serial.println("Solid");
            solidAnimation(zones[idx]);
            break;
          case COLOR_GLITTER:
            Serial.println("ColorGlitter");
            colorGlitterAnimation(glitterChance, zones[idx]);
            break;
          case RAINBOW:
            Serial.println("Rainbow");
            rainbowAnimation(zones[idx]);
            break;
          case TWINKLE:
            Serial.println("Twinkle");
            twinkleAnimation(zones[idx]);
            break;
          case SPOOKY_EYES:
            Serial.println("Eyes");
            eyesAnimation(zones[idx]);
            break;
          case LED_LOCATOR:
            Serial.println("Locator");
            locatorAnimation(zones[idx]);
            break;
          case SINGLE_RACE:
            Serial.println("SingleRace");
            singleRaceAnimation(zones[idx]);
            break;
          case BLOCKED_COLORS:
            Serial.println("Blocked");
            blockedAnimation(zones[idx]);
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
  } else {
    for (int idx = 0; idx < ZONE_COUNT; idx ++)
    {
      clearLeds();
    }
  }
}


void updateSectionLeds() {
  if (showLights == true) {
    for (int idx = 0; idx < ZONE_COUNT; idx++) {
      if (zones[idx].active) {
        for (int idy = 0; idy < zones[idx].sectionCount; idy++) {
          if (zones[idx].sections[idy].active) {
            switch (zones[idx].sections[idy].pattern) {
              case RIPPLE:
                rippleAnimation(zones[idx].sections[idy]);
                break;
              case CHASE:
                rgbFillAnimation(zones[idx].sections[idy]);
                break;
              case DOUBLE_CRASH:
                Crash(zones[idx].sections[idy]);
                break;
              case FIRE:
                sectionFireAnimation(zones[idx].sections[idy]);
                break;
              case BPM:
                bpmAnimation(zones[idx].sections[idy]);
                break;
              case FILL:
                solidAnimation(zones[idx].sections[idy]);
                break;
              case COLOR_GLITTER:
                colorGlitterAnimation(glitterChance, zones[idx].sections[idy]);
                break;
              case RAINBOW:
                rainbowAnimation(zones[idx].sections[idy]);
                break;
              case TWINKLE:
                twinkleAnimation(zones[idx].sections[idy]);
                break;
              case SPOOKY_EYES:
                eyesAnimation(zones[idx].sections[idy]);
                break;
              case LED_LOCATOR:
                locatorAnimation(zones[idx].sections[idy]);
                break;
              case SINGLE_RACE:
                singleRaceAnimation(zones[idx].sections[idy]);
                break;
              case BLOCKED_COLORS:
                blockedAnimation(zones[idx].sections[idy]);
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
  } else {
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
  if (showLightning && showLights)
  {
    for (int idx = 0; idx < ZONE_COUNT; idx ++)
    {
      if (zones[idx].active)
      {
        fadeToBlackBy(zones[idx].leds, zones[idx].ledCount, 1);
      }
    }

    unsigned int chance = random16();
    if ( chance > lightningChance)
    {
      for (int idx = 0; idx < ZONE_COUNT; idx ++)
      {
        if (zones[idx].active)
        {
          fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::White);
        }
      }
      lightning = 20;
      if (audioEffects )
      {
        int thunder = random8();
        if ( thunder > 128)
        {
          mqttClient.publish("Audio", "2");
        }
        if ( thunder < 127)
        {
          mqttClient.publish("Audio", "1");
        }
      }
    }
    if (lightning != 1)
    {
      if (lightning > 15)
      {
        for (int idx = 0; idx < ZONE_COUNT; idx ++)
        {
          if (zones[idx].active)
          {
            fadeToBlackBy(zones[idx].leds, zones[idx].ledCount, 1);
          }
        }
        lightning--;
      }
      if (lightning == 15)
      {

        for (int idx = 0; idx < ZONE_COUNT; idx ++)
        {
          if (zones[idx].active)
          {
            fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::White);
          }
        }
        lightning--;
      }
      if (lightning > 5 && lightning < 15)
      {
        for (int idx = 0; idx < ZONE_COUNT; idx ++)
        {
          if (zones[idx].active)
          {
            fadeToBlackBy(zones[idx].leds, zones[idx].ledCount, 150);
          }
        }
        lightning--;
      }
      if (lightning == 5)
      {
        for (int idx = 0; idx < ZONE_COUNT; idx ++)
        {
          if (zones[idx].active)
          {
            fill_solid(zones[idx].leds, zones[idx].ledCount, CRGB::White);
          }
        }
        lightning--;
      }
      if (lightning > 0 && lightning < 5)
      {
        for (int idx = 0; idx < ZONE_COUNT; idx ++)
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
  if (showGlitter && showLights)
  {
    if ( random8() < glitterFrequency)
    {
      for (int idx = 0; idx < ZONE_COUNT; idx ++)
      {
        if (zones[idx].active)
        {
          zones[idx].leds[random16(zones[idx].ledCount)] = CRGB(redG, greenG, blueG);
        }
      }
    }
  }
}

void setupLeds()
{
  Serial.println("Setting up zone leds");
  if (zones[ZONE_ONE].active && ZONE_ONE_LED_COUNT > 0)
  {
    Serial.println("Setting up zone 1 leds");
    LEDS.addLeds<WS2812, Pin_firstZone, FIRSTZONE_COLOR_ORDER>(AllLeds[0], ZONE_ONE_LED_COUNT);
  }

  if (zones[ZONE_TWO].active && ZONE_TWO_LED_COUNT > 0)
  {
    Serial.println("Setting up zone 2 leds");
    LEDS.addLeds<WS2812, Pin_secondZone, SECONDZONE_COLOR_ORDER>(AllLeds[1], ZONE_TWO_LED_COUNT);
  }

  if (zones[ZONE_THREE].active && ZONE_THREE_LED_COUNT > 0)
  {
    Serial.println("Setting up zone 3 leds");
    LEDS.addLeds<WS2812B, Pin_thirdZone, THIRDZONE_COLOR_ORDER>(AllLeds[2], ZONE_THREE_LED_COUNT);
  }

  if (zones[ZONE_FOUR].active && ZONE_FOUR_LED_COUNT > 0)
  {
    Serial.println("Setting up zone 4 leds");
    LEDS.addLeds<WS2812B, Pin_fourthZone, FOURTHZONE_COLOR_ORDER>(AllLeds[3], ZONE_FOUR_LED_COUNT);
  }

  if (zones[ZONE_FIVE].active && ZONE_FIVE_LED_COUNT > 0)
  {
    Serial.println("Setting up zone 5 leds");
    LEDS.addLeds<WS2812B, Pin_fifthZone, FIFTHZONE_COLOR_ORDER>(AllLeds[4], ZONE_FIVE_LED_COUNT);
  }

  if (zones[ZONE_SIX].active && ZONE_SIX_LED_COUNT > 0)
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

void rippleAnimation(LedStrip strip)
{
  int start = strip.start;
  int end = strip.end;
  int ledCount = strip.ledCount;
  for (int idx = start; idx < end; idx++)
  {
    strip.leds[idx] = CRGB((gColors[1].red / 75), (gColors[1].green / 75), (gColors[1].blue / 75));
  }
  switch (strip.steps)
  {
    case -1:
      strip.center = random16(ledCount);
      strip.steps = 0;
      break;
    case 0:
      strip.leds[strip.center] = gColors[0].;
      strip.steps ++;
      break;
    case 12:
      strip.steps = -1;
      break;
    default:                                                             // Middle of the ripples.
      strip.leds[start + ((strip.center + strip.steps + ledCount) % ledCount)] += CRGB((gColors[0].red / (strip.steps * 5)), (gColors[0].green / (strip.steps * 5)), (gColors[0].blue / (strip.steps * 5)));
      strip.leds[start + ((strip.center - strip.steps + ledCount) % ledCount)] += CRGB((gColors[0].red / (strip.steps * 5)), (gColors[0].green / (strip.steps * 5)), (gColors[0].blue / (strip.steps * 5)));
      strip.steps ++;
      break;
  }
}

void rgbFillAnimation(LedStrip strip)
{
  if (startPosition < 6)
  {
    fadeToBlackBy( strip.leds, strip.ledCount, 80);
    for (int pixel = startPosition + 1; pixel < strip.ledCount; pixel += 6)
    {
      if (pixel <= strip.ledCount)
      {
        strip.leds[pixel] = gColors[0];
      }
    }
    for (int pixel = startPosition + 3; pixel < strip.ledCount; pixel += 6)
    {
      if (pixel <= strip.ledCount)
      {
        strip.leds[pixel] = gColors[1];
      }
    }
    for (int pixel = startPosition + 5; pixel < strip.ledCount; pixel += 6)
    {
      if (pixel <= strip.ledCount)
      {
        strip.leds[pixel] = gColors[2];
      }
    }
  }
  if (startPosition == 1)
  {
    strip.leds[0] = gColors[2];
  }
  if (startPosition == 2)
  {
    strip.leds[1] = gColors[2];
  }
  if (startPosition == 3)
  {
    strip.leds[2] = gColors[2];
    strip.leds[0] = gColors[1];
  }
  if (startPosition == 4)
  {
    strip.leds[3] = gColors[2];
    strip.leds[1] = gColors[1];
  }
  if (startPosition == 5)
  {
    strip.leds[4] = gColors[2];
    strip.leds[2] = gColors[1];
    strip.leds[0] = gColors[0];
  }
}

void colorGlitterAnimation( fract8 chanceOfGlitter, LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 2);
  if (startPosition == 0)
  {
    if ( random8() < chanceOfGlitter)
    {
      strip.leds[ random16(strip.ledCount) ] += CRGB::Red;
    }
  }
  if (startPosition == 1)
  {
    if ( random8() < chanceOfGlitter)
    {
      strip.leds[ random16(strip.ledCount) ] += CRGB::Orange;
    }
  }
  if (startPosition == 2)
  {
    if ( random8() < chanceOfGlitter)
    {
      strip.leds[ random16(strip.ledCount) ] += CRGB::Yellow;
    }
  }
  if (startPosition == 3)
  {
    if ( random8() < chanceOfGlitter)
    {
      strip.leds[ random16(strip.ledCount) ] += CRGB::Green;
    }
  }
  if (startPosition == 4)
  {
    if ( random8() < chanceOfGlitter)
    {
      strip.leds[ random16(strip.ledCount) ] += CRGB::Blue;
    }
  }
  if (startPosition == 5)
  {
    if ( random8() < chanceOfGlitter)
    {
      strip.leds[ random16(strip.ledCount) ] += CRGB::Violet;
    }
  }
}

void singleRaceAnimation(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 1);
  int pos = beatsin16( raceSpeed, 0, strip.ledCount);
  if (pos > strip.previousLed)
  {
    strip.leds[pos] = gColors[0];
    strip.previousLed = pos;
  }
  if (pos < strip.previousLed)
  {
    strip.leds[pos] = gColors[1];
    strip.previousLed = pos;
  }
}

void crashAnimation(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 15);
  if (strip.active) {
    int pos = beatsin16( raceSpeed, 0, (strip.end - strip.start ));
    strip.leds[strip.start + pos] = gColors[0];
    strip.leds[strip.end - pos] = gColors[1];
  }
}

void rainbowAnimation(LedStrip strip)
{
  fill_rainbow( strip.leds, strip.ledCount, gHue, numberOfRainbows);
}

void blockedAnimation(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 2);
  for ( int mark = 0; mark < strip.ledCount; mark += 30)
  {
    for ( int i = 0; i < 9; i++)
    {
      if (startPosition == 0 || startPosition == 1)
      {
        if (i + mark <= strip.ledCount)
        {
          strip.leds[i + mark] = gColors[0];
        }
        if (i + 10 + mark <= strip.ledCount)
        {
          strip.leds[i + 10 + mark] = gColors[1];
        }
        if (i + 20 + mark <= strip.ledCount)
        {
          strip.leds[i + 20 + mark] = gColors[2].;
        }
      }
      if (startPosition == 2 || startPosition == 3)
      {
        if (i + mark <= strip.ledCount)
        {
          strip.leds[i + mark] = gColors[1];
        }
        if (i + 10 + mark <= strip.ledCount)
        {
          strip.leds[i + 10 + mark] = gColors[2];
        }
        if (i + 20 + mark <= strip.ledCount)
        {
          strip.leds[i + 20 + mark] = gColors[0];
        }
      }
      if (startPosition == 4 || startPosition == 5)
      {
        if (i + mark <= strip.ledCount)
        {
          strip.leds[i + mark] = gColors[2];
        }
        if (i + 10 + mark <= strip.ledCount)
        {
          strip.leds[i + 10 + mark] = gColors[1];
        }
        if (i + 20 + mark <= strip.ledCount)
        {
          strip.leds[i + 20 + mark] = gColors[0];
        }
      }
    }
  }
}

void bpmAnimation(LedStrip strip)
{
  if ((gColors[0].red * 2) > (gColors[0].green + gColors[0].blue))
  {
    CRGBPalette16 palette_Zone = LavaColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < strip.ledCount; i++)
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((gColors[0].green * 2) > (gColors[0].red + gColors[0].blue))
  {
    CRGBPalette16 palette_Zone = ForestColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < strip.ledCount; i++)
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((gColors[0].blue * 2) > (gColors[0].green + gColors[0].red))
  {
    CRGBPalette16 palette_Zone = CloudColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < strip.ledCount; i++)
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((gColors[0].blue * 2) == (gColors[0].green + gColors[0].red))
  {
    CRGBPalette16 palette_Zone = PartyColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < strip.ledCount; i++)
    {
      strip.leds[i] = ColorFromPalette(palette_Zone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
}

void twinkleAnimation(LedStrip strip)
{
  fadeToBlackBy( strip.leds, strip.ledCount, 80);
  for ( int i = 0; i < strip.ledCount - 5; i += 5)
  {
    if (i <= strip.ledCount)
    {
      if (random8() > twinkleChance)
      {
        strip.leds[i] = gColors[0];
      }
      else
      {
        strip.leds[i] = CRGB( 150, 100, 40);
      }
    }
  }
}

void eyesAnimation(LedStrip strip)
{
  unsigned int chance = random8();
  if ( chance > eyeChance)
  {
    unsigned int eye = random16(strip.ledCount);
    strip.leds[eye] = gColors[0];
    strip.leds[eye - 4] = gColors[0];
  }
  if ( chance > 39)
  {
    fadeToBlackBy( strip.leds, strip.ledCount, 10);
  }
}

void solidAnimation(LedStrip strip)
{
  fill_solid(strip.leds, strip.ledCount, gColors[0]);
}

void locatorAnimation(LedStrip strip)
{
  if (locatorLED <= strip.ledCount)
  {
    fill_solid(strip.leds, strip.ledCount, CRGB::Black);
    strip.leds[locatorLED] = gColors[0];
  }
}

void sectionFireAnimation(LedStrip strip)
{
  int sectionEnd = strip.end;
  int sectionStart = strip.start;
  const int size = sectionEnd - sectionStart;
  static byte heat[size];
  for ( int i = 0; i < size; i++)
  {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / size) + 2));
  }

  for ( int k = size - 1; k >= 2; k--)
  {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }
  if ( random8() < SPARKING )
  {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }
  for ( int j = 0; j < size; j++)
  {
    byte colorindex = scale8( heat[j], 240);
    CRGB color = ColorFromPalette( gPal, colorindex);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (size - 1) - j;
    } else {
      pixelnumber = j;
    }
    int thisFlame = ((pixelnumber * firesize) / 100);

    if (strip.fireStart == 1)
    {
      if (thisFlame <=  size)
      {
        strip.leds[sectionStart + thisFlame] = color;
      }
    }

    if (strip.fireEnd == 1)
    {
      if (thisFlame <=  size )
      {
        strip.leds[sectionEnd - thisFlame] = color;
      }
    }
  }
}


void storeAnimationSettings() {
  //Store the Settings to NVM
}

void loadAnimationSettings() {
  //TODO: Load the settings from NVM
}
