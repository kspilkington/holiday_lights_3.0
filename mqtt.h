/************************** MQTT Connection *********************/
void mqttConnect(){
    if (mqttActive)
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(mqtt_client_name, mqtt_user, mqtt_pass)) 
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            if(boot == true)
            {
            client.publish(USER_MQTT_CLIENT_NAME"/checkIn","Rebooted");
            boot = false;
            }
            if(boot == false)
            {
            client.publish(USER_MQTT_CLIENT_NAME"/checkIn","Reconnected"); 
            }
            // ... and resubscribe
            client.subscribe(USER_MQTT_CLIENT_NAME"/configure");
            client.subscribe(USER_MQTT_CLIENT_NAME"/modifier");
            client.subscribe(USER_MQTT_CLIENT_NAME"/effect");
            client.subscribe(USER_MQTT_CLIENT_NAME"/state");
            client.subscribe(USER_MQTT_CLIENT_NAME"/color1");
            client.subscribe(USER_MQTT_CLIENT_NAME"/color2");
            client.subscribe(USER_MQTT_CLIENT_NAME"/color3");
            client.subscribe(USER_MQTT_CLIENT_NAME"/power");
            client.subscribe(USER_MQTT_CLIENT_NAME"/brightness");
            client.subscribe(USER_MQTT_CLIENT_NAME"/addEffects");
            client.subscribe(USER_MQTT_CLIENT_NAME"/lightningChance");
            client.subscribe(USER_MQTT_CLIENT_NAME"/glitterChance");
            client.subscribe(USER_MQTT_CLIENT_NAME"/glitterColor");
        } 
        else 
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            retries++;
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}


/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/


void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  String newTopic = topic;
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0';
  String newPayload = String((char *)payload);
  int intPayload = newPayload.toInt();
  Serial.println(newPayload);
  Serial.println();
  newPayload.toCharArray(charPayload, newPayload.length() + 1); 
  if (newTopic == USER_MQTT_CLIENT_NAME"/modifier")
  {
    client.publish(USER_MQTT_CLIENT_NAME"/modifierState", charPayload);
    if(effect == "Double_Crash" || effect == "Single_Race")
    {
      raceSpeed = (intPayload/20);
    }
    if(effect == "BPM")
    {
      BeatsPerMinute = (intPayload/4);
    }
    if(effect == "Color_Chase" || effect == "Blocked_Colors")
    {
      chaseDelay = (intPayload*5);
      if(chaseDelay < 100)
      {
        chaseDelay = 100;
      }
    }
    if(effect == "Color_Glitter")
    {
      glitterChance = (intPayload/2);
    }
    if(effect == "Rainbow")
    {
      numberOfRainbows = (intPayload/30);
    }
    if(effect == "Twinkle")
    {
      twinkleChance = map(intPayload, 0, 500, 0, 255);
    }
    if(effect == "Spooky_Eyes")
    {
      eyeChance = map(intPayload, 0, 500, 200, 255);
    }
    if(effect == "Fire")
    {
      firesize = map(intPayload, 0, 500, 10, 120);
    }
    if(effect == "LED_Locator")
    {
      locatorDelay = map(intPayload, 0, 500, 500, 5000);
    }
  }
  if (newTopic == USER_MQTT_CLIENT_NAME"/addEffects")
  {
    if(newPayload == "Audio On")
    {
      audioEffects = true;
      client.publish(USER_MQTT_CLIENT_NAME"/audio/state", charPayload);
    }
    if(newPayload == "Audio Off")
    {
      audioEffects = false;
      client.publish(USER_MQTT_CLIENT_NAME"/audio/state", charPayload);
    }
    if(newPayload == "Glitter On")
    {
      showGlitter = true;
      client.publish(USER_MQTT_CLIENT_NAME"/glitter/state", charPayload);
    }
    if(newPayload == "Glitter Off")
    {
      showGlitter = false;
      client.publish(USER_MQTT_CLIENT_NAME"/glitter/state", charPayload);
    }
    if(newPayload == "Lightning On")
    {
      showLightning = true;
      client.publish(USER_MQTT_CLIENT_NAME"/lightning/state","Lightning On");
    }
    if(newPayload == "Lightning Off")
    {
      showLightning = false;
      client.publish(USER_MQTT_CLIENT_NAME"/lightning/state","Lightning Off");
    }
  }
  if (newTopic == USER_MQTT_CLIENT_NAME"/effect") 
  {
    effect = newPayload;
    Animation pattern = getPattern(effect);
    if (ANIMATION_LEVEL == EVERYTHING || ANIMATION_LEVEL == ZONE_LEVEL){
      for(int idx = 0; idx < ZONE_COUNT;idx++){
          zones[idx].pattern = pattern;
      }
    }else{
      for(int idx = 0; idx < ZONE_COUNT;idx++){
        for(int idy=0; idy < MAX_SECTION;idy++){
          zones[idx].sections[idy].pattern = pattern;
        }
      }
    }
    client.publish(USER_MQTT_CLIENT_NAME"/effectState", charPayload);
    clearLeds();
  }
  for(int idx=0;idx< ZONE_COUNT; idx++)
  {
    if (newTopic == (USER_MQTT_CLIENT_NAME"/effect/zone")+idx)
    {
      effect = newPayload;
      client.publish((USER_MQTT_CLIENT_NAME"/effectState/zone")+idx, charPayload);
      zones[idx].pattern = getPattern(effect);
    }
    for (int idy=0;idy<zones[idx].sectionCount;idy++)
    {
      if (newTopic == ((USER_MQTT_CLIENT_NAME"/effect/zone")+idx+((String)"/section")+idy))
      {
        effect = newPayload;
        zones[idx].sections[idy].pattern = getPattern(effect);
        client.publish(((USER_MQTT_CLIENT_NAME"/effectState/zone")+idx+((String)"/section")+idy).c_str(), charPayload);
      }
    }
  }
  
  
  if (newTopic == USER_MQTT_CLIENT_NAME "/effect/animationLevel")
  {
    if (newPayload == "Everything"){
      ANIMATION_LEVEL = EVERYTHING;
    }else if (newPayload == "Zone"){
      ANIMATION_LEVEL = ZONE_LEVEL;
    }else if (newPayload == "Section"){
      ANIMATION_LEVEL = SECTION_LEVEL;
    }
    client.publish(USER_MQTT_CLIENT_NAME"/effectState/animationLevel", charPayload);
    clearLeds();
  }

  
  if (newTopic == USER_MQTT_CLIENT_NAME "/color1")
  {
    client.publish(USER_MQTT_CLIENT_NAME "/color1State", charPayload); 
    // get the position of the first and second commas
    uint8_t firstIndex = newPayload.indexOf(',');
    uint8_t lastIndex = newPayload.lastIndexOf(',');
    
    uint8_t rgb_red = newPayload.substring(0, firstIndex).toInt();
    if (rgb_red < 0 || rgb_red > 255) {
      return;
    } else {
      red1 = rgb_red;
    }
    
    uint8_t rgb_green = newPayload.substring(firstIndex + 1, lastIndex).toInt();
    if (rgb_green < 0 || rgb_green > 255) {
      return;
    } else {
      green1 = rgb_green;
    }
    
    uint8_t rgb_blue = newPayload.substring(lastIndex + 1).toInt();
    if (rgb_blue < 0 || rgb_blue > 255) {
      return;
    } else {
      blue1 = rgb_blue;
    }
  }

  if (newTopic == USER_MQTT_CLIENT_NAME "/color2")
  {
    client.publish(USER_MQTT_CLIENT_NAME "/color2State", charPayload); 
    // get the position of the first and second commas
    uint8_t firstIndex = newPayload.indexOf(',');
    uint8_t lastIndex = newPayload.lastIndexOf(',');
    
    uint8_t rgb_red = newPayload.substring(0, firstIndex).toInt();
    if (rgb_red < 0 || rgb_red > 255) {
      return;
    } else {
      red2 = rgb_red;
    }
    
    uint8_t rgb_green = newPayload.substring(firstIndex + 1, lastIndex).toInt();
    if (rgb_green < 0 || rgb_green > 255) {
      return;
    } else {
      green2 = rgb_green;
    }
    
    uint8_t rgb_blue = newPayload.substring(lastIndex + 1).toInt();
    if (rgb_blue < 0 || rgb_blue > 255) {
      return;
    } else {
      blue2 = rgb_blue;
    }
  }

  if (newTopic == USER_MQTT_CLIENT_NAME "/color3")
  {
    client.publish(USER_MQTT_CLIENT_NAME "/color3State", charPayload); 
    // get the position of the first and second commas
    uint8_t firstIndex = newPayload.indexOf(',');
    uint8_t lastIndex = newPayload.lastIndexOf(',');
    
    uint8_t rgb_red = newPayload.substring(0, firstIndex).toInt();
    if (rgb_red < 0 || rgb_red > 255) {
      return;
    } else {
      red3 = rgb_red;
    }
    
    uint8_t rgb_green = newPayload.substring(firstIndex + 1, lastIndex).toInt();
    if (rgb_green < 0 || rgb_green > 255) {
      return;
    } else {
      green3 = rgb_green;
    }
    
    uint8_t rgb_blue = newPayload.substring(lastIndex + 1).toInt();
    if (rgb_blue < 0 || rgb_blue > 255) {
      return;
    } else {
      blue3 = rgb_blue;
    }
  }

  if (newTopic == USER_MQTT_CLIENT_NAME "/glitterColor")
  {
    client.publish(USER_MQTT_CLIENT_NAME "/glitterColorState", charPayload); 
    // get the position of the first and second commas
    uint8_t firstIndex = newPayload.indexOf(',');
    uint8_t lastIndex = newPayload.lastIndexOf(',');
    
    uint8_t rgb_red = newPayload.substring(0, firstIndex).toInt();
    if (rgb_red < 0 || rgb_red > 255) {
      return;
    } else {
      redG = rgb_red;
    }
    
    uint8_t rgb_green = newPayload.substring(firstIndex + 1, lastIndex).toInt();
    if (rgb_green < 0 || rgb_green > 255) {
      return;
    } else {
      greenG = rgb_green;
    }
    
    uint8_t rgb_blue = newPayload.substring(lastIndex + 1).toInt();
    if (rgb_blue < 0 || rgb_blue > 255) {
      return;
    } else {
      blueG = rgb_blue;
    }
  }
  
  if (newTopic == USER_MQTT_CLIENT_NAME"/glitterChance") 
  {
    client.publish(USER_MQTT_CLIENT_NAME "/glitterChanceState", charPayload); 
    glitterFrequency = intPayload;
  }
  
  if (newTopic == USER_MQTT_CLIENT_NAME"/lightningChance") 
  {
    client.publish(USER_MQTT_CLIENT_NAME "/lightningChanceState", charPayload); 
    lightningChance = (65535 - intPayload);
  }
  
  if (newTopic == USER_MQTT_CLIENT_NAME"/brightness") 
  {
    client.publish(USER_MQTT_CLIENT_NAME "/brightnessState", charPayload); 
    brightness = intPayload;
  }
  
  if (newTopic == USER_MQTT_CLIENT_NAME"/power")
  {
    if(ON.equalsIgnoreCase(newPayload))
    {
      showLights = true;
    }
    else if(OFF.equalsIgnoreCase(newPayload))
    {
      showLights = false;
    }
    else if (TOGGLE.equalsIgnoreCase(newPayload)){
      showLights = !showLights;
    }
    client.publish(USER_MQTT_CLIENT_NAME "/powerState", showLights?"ON":"OFF"); 
  }
}