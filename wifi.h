
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
  if (WIFI_ACTIVATE_AP && ACTIVATE_WIFI_CLIENT) {
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
  } else if (ACTIVATE_WIFI_AP) {
    Serial.println("WIFI_AP");
    WiFi.mode(WIFI_AP); //Access Point mode
    WiFi.softAP(USER_MQTT_CLIENT_NAME"_AP", apPassword);
    Serial.println("Wifi AP active");
    mqttActive = false;
    wifiApActive = true;
  } else if (ACTIVATE_WIFI_CLIENT) { //Check to see if we have a saved config
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

void reconnect()
{
  // Loop until we're reconnected
  if (wifClientActive && mqttActive) {
    int retries = 0;
    while (!mqttClient.connected()) {
      if (retries < 15)
      {
        mqttConnect();
        retries++;
      }
      if (retries >= 15)
      {
        Serial.println("Unable to connect to mqtt server");
        ESP.restart();
      }
    }
  }
}
