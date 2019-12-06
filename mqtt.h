/************************** MQTT Connection *********************/
void mqttConnect() {
  if (wifiClientActive) {
    // Loop until we're reconnected
    int retries = 0;
    mqttClient.setServer(mqtt_server, mqtt_port);
    while (!mqttClient.connected()) {
      if (retries < 150)
      {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        Serial.println(mqtt_client_name);
        Serial.println(mqtt_user);
        Serial.println(mqtt_pass);
        if (mqttClient.connect(mqtt_client_name, mqtt_user, mqtt_pass))
        {
          mqttActive = true;
          Serial.println("connected");
          // Once connected, publish an announcement...
          if (boot == true)
          {
            mqttClient.publish(USER_MQTT_CLIENT_NAME"/checkIn", "Rebooted");
            boot = false;
          }
          if (boot == false)
          {
            mqttClient.publish(USER_MQTT_CLIENT_NAME"/checkIn", "Reconnected");
          }
          // ... and resubscribe
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/configure");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/modifier");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/effect");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/state");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/color1");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/color2");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/color3");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/power");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/brightness");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/addEffects");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/lightningChance");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/glitterChance");
          mqttClient.subscribe(USER_MQTT_CLIENT_NAME"/glitterColor");
        }
        else 
        {
          Serial.print("failed, rc=");
          Serial.print(mqttClient.state());
          Serial.println(" try again in 5 seconds");
          retries++;
          // Wait 5 seconds before retrying
          delay(5000);
        }
      }
    }
  }
}


/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/
/************************** MQTT CALLBACK ***********************/


void mqttCallback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  String newTopic = topic;
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0';
  String newPayload = String((char *)payload);
  int intPayload = newPayload.toInt();
  Serial.println(newPayload);
  newPayload.toCharArray(charPayload, newPayload.length() + 1);
  if (newTopic == USER_MQTT_CLIENT_NAME"/modifier")
  {
    mqttClient.publish(USER_MQTT_CLIENT_NAME"/modifierState", charPayload);
    if (zone[0].pattern == DOUBLE_CRASH || zone[0].pattern == SINGLE_RACE)
    {
      raceSpeed = (intPayload / 20);
    }
    if (zone[0].pattern == BPM)
    {
      BeatsPerMinute = (intPayload / 4);
    }
    if (zone[0].pattern == CHASE || zone[0].pattern == BLOCKED_COLORS)
    {
      chaseDelay = (intPayload * 5);
      if (chaseDelay < 100)
      {
        chaseDelay = 100;
      }
    }
    if (zone[0].pattern == COLOR_GLITTER)
    {
      glitterChance = (intPayload / 2);
    }
    if (zone[0].pattern == RAINBOW)
    {
      numberOfRainbows = (intPayload / 30);
    }
    if (zone[0].pattern == TWINKLE)
    {
      twinkleChance = map(intPayload, 0, 500, 0, 255);
    }
    if (zone[0].pattern == SPOOKY_EYES)
    {
      eyeChance = map(intPayload, 0, 500, 200, 255);
    }
    if (zone[0].pattern == FIRE)
    {
      firesize = map(intPayload, 0, 500, 10, 120);
    }
    if (zone[0].pattern == LED_LOCATOR)
    {
      locatorDelay = map(intPayload, 0, 500, 500, 5000);
    }
  }
  if (newTopic == USER_MQTT_CLIENT_NAME"/addEffects")
  {
    if (newPayload == "Audio On")
    {
      audioEffects = true;
      mqttClient.publish(USER_MQTT_CLIENT_NAME"/audio/state", charPayload);
    }
    if (newPayload == "Audio Off")
    {
      audioEffects = false;
      mqttClient.publish(USER_MQTT_CLIENT_NAME"/audio/state", charPayload);
    }
    if (newPayload == "Glitter On")
    {
      showGlitter = true;
      mqttClient.publish(USER_MQTT_CLIENT_NAME"/glitter/state", charPayload);
    }
    if (newPayload == "Glitter Off")
    {
      showGlitter = false;
      mqttClient.publish(USER_MQTT_CLIENT_NAME"/glitter/state", charPayload);
    }
    if (newPayload == "Lightning On")
    {
      showLightning = true;
      mqttClient.publish(USER_MQTT_CLIENT_NAME"/lightning/state", "Lightning On");
    }
    if (newPayload == "Lightning Off")
    {
      showLightning = false;
      mqttClient.publish(USER_MQTT_CLIENT_NAME"/lightning/state", "Lightning Off");
    }
  }
  if (newTopic == USER_MQTT_CLIENT_NAME"/effect")
  {
    Animation pattern = getPattern(newPayload);
    if (ANIMATION_LEVEL == EVERYTHING || ANIMATION_LEVEL == ZONE_LEVEL) {
      for (int idx = 0; idx < ZONE_COUNT; idx++) {
        zones[idx].pattern = pattern;
      }
    } else {
      for (int idx = 0; idx < ZONE_COUNT; idx++) {
        for (int idy = 0; idy < MAX_SECTION; idy++) {
          zones[idx].sections[idy].pattern = pattern;
        }
      }
    }
    mqttClient.publish(USER_MQTT_CLIENT_NAME"/effectState", newPayload);
    clearLeds();
  }
  for (int idx = 0; idx < ZONE_COUNT; idx++)
  {
    if (newTopic == (USER_MQTT_CLIENT_NAME"/effect/zone") + idx)
    {
      mqttClient.publish((USER_MQTT_CLIENT_NAME"/effectState/zone") + idx, charPayload);
      zones[idx].pattern = getPattern(newPayload);
    }
    for (int idy = 0; idy < zones[idx].sectionCount; idy++)
    {
      if (newTopic == ((USER_MQTT_CLIENT_NAME"/effect/zone") + idx + ((String)"/section") + idy))
      {
        zones[idx].sections[idy].pattern = getPattern(effect);
        mqttClient.publish(((USER_MQTT_CLIENT_NAME"/effectState/zone") + idx + ((String)"/section") + idy).c_str(), charPayload);
      }
    }
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/effect/animationLevel")
  {
    if (newPayload == "Everything") {
      ANIMATION_LEVEL = EVERYTHING;
    } else if (newPayload == "Zone") {
      ANIMATION_LEVEL = ZONE_LEVEL;
    } else if (newPayload == "Section") {
      ANIMATION_LEVEL = SECTION_LEVEL;
    }
    mqttClient.publish(USER_MQTT_CLIENT_NAME"/effectState/animationLevel", charPayload);
    clearLeds();
  }

  for (int idx = 0; idx < COLOR_COUNT; idx++) {
    if (newTopic == ((String)USER_MQTT_CLIENT_NAME + "/color" + idx))
    {
      mqttClient.publish(((String)USER_MQTT_CLIENT_NAME + "/color" + idx + "State"), charPayload);
      // get the position of the first and second commas
      uint8_t firstIndex = newPayload.indexOf(',');
      uint8_t lastIndex = newPayload.lastIndexOf(',');

      uint8_t rgb_red = newPayload.substring(0, firstIndex).toInt();
      if (rgb_red < 0 || rgb_red > 255) {
        return;
      } else {
        gColors[idx].red = rgb_red;
      }

      uint8_t rgb_green = newPayload.substring(firstIndex + 1, lastIndex).toInt();
      if (rgb_green < 0 || rgb_green > 255) {
        return;
      } else {
        gColors[idx].green = rgb_green;
      }

      uint8_t rgb_blue = newPayload.substring(lastIndex + 1).toInt();
      if (rgb_blue < 0 || rgb_blue > 255) {
        return;
      } else {
        gColors[idx].blue = rgb_blue;
      }
    }
  }


  if (newTopic == USER_MQTT_CLIENT_NAME "/glitterColor")
  {
    mqttClient.publish(USER_MQTT_CLIENT_NAME "/glitterColorState", charPayload);
    // get the position of the first and second commas
    uint8_t firstIndex = newPayload.indexOf(',');
    uint8_t lastIndex = newPayload.lastIndexOf(',');

    uint8_t rgb_red = newPayload.substring(0, firstIndex).toInt();
    if (rgb_red < 0 || rgb_red > 255) {
      return;
    } else {
      glitterColor.red = rgb_red;
    }

    uint8_t rgb_green = newPayload.substring(firstIndex + 1, lastIndex).toInt();
    if (rgb_green < 0 || rgb_green > 255) {
      return;
    } else {
      glitterColor.green = rgb_green;
    }

    uint8_t rgb_blue = newPayload.substring(lastIndex + 1).toInt();
    if (rgb_blue < 0 || rgb_blue > 255) {
      return;
    } else {
      glitterColor.blue = rgb_blue;
    }
  }

  if (newTopic == USER_MQTT_CLIENT_NAME"/glitterChance")
  {
    mqttClient.publish(USER_MQTT_CLIENT_NAME "/glitterChanceState", charPayload);
    glitterFrequency = intPayload;
  }

  if (newTopic == USER_MQTT_CLIENT_NAME"/lightningChance")
  {
    mqttClient.publish(USER_MQTT_CLIENT_NAME "/lightningChanceState", charPayload);
    lightningChance = (65535 - intPayload);
  }

  if (newTopic == USER_MQTT_CLIENT_NAME"/brightness")
  {
    mqttClient.publish(USER_MQTT_CLIENT_NAME "/brightnessState", charPayload);
    brightness = intPayload;
  }

  if (newTopic == USER_MQTT_CLIENT_NAME"/power")
  {
    if (ON.equalsIgnoreCase(newPayload))
    {
      showLights = true;
    }
    else if (OFF.equalsIgnoreCase(newPayload))
    {
      showLights = false;
    }
    else if (TOGGLE.equalsIgnoreCase(newPayload)) {
      showLights = !showLights;
    }
    mqttClient.publish(USER_MQTT_CLIENT_NAME "/powerState", showLights ? "ON" : "OFF");
  }
}
