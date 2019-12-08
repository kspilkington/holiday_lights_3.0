
void setup_wifi()
{
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.persistent(true);
  wifiApActive = false;
  wifiClientActive = false;
  mqttActive = false;
  if (WIFI_ACTIVATE_AP && WIFI_ACTIVATE_CLIENT) {
    Serial.println("WIFI_AP_STA");
    WiFi.mode(WIFI_AP_STA); //Access Point mode
    WiFi.softAP(USER_MQTT_CLIENT_NAME"_AP", apPassword);
    wifiApActive = true;
    Serial.println("Wifi AP active");
    WiFi.setHostname(USER_MQTT_CLIENT_NAME);
    WiFi.begin(ssid, password);
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED || retry < 10) {
      delay(500);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      wifiClientActive = true;
    } else {
      Serial.println("Unable to connect to WiFi");
      wifiClientActive = false;
    }
  } else if (WIFI_ACTIVATE_AP) {
    Serial.println("WIFI_AP");
    WiFi.mode(WIFI_AP); //Access Point mode
    WiFi.softAP(USER_MQTT_CLIENT_NAME"_AP", apPassword);
    Serial.println("Wifi AP active");
    mqttActive = false;
    wifiApActive = true;
  } else if (WIFI_ACTIVATE_CLIENT) { //Check to see if we have a saved config
    Serial.println("WIFI_STA");
    WiFi.mode(WIFI_STA); //Connectto your wifi
    WiFi.setHostname(USER_MQTT_CLIENT_NAME);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    wifiClientActive = true;
  }

}


void otaSteup() {
  if (!noWeb && (wifiApActive || wifiClientActive)) {
    Serial.println("Starting ArduionoOTA");
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
    Serial.println("Done with Ota");
  } else {
    Serial.println("No OTA available");
  }
}
