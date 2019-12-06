
void setup_wifi() 
{
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.persistent(true);
  if (WIFI_AP_ACTIVE && WIFI_CONNECT){
    Serial.println("WIFI_AP_STA"); 
    WiFi.mode(WIFI_AP_STA); //Access Point mode
    WiFi.softAP(USER_MQTT_CLIENT_NAME"_AP", apPassword);
    Serial.println("Wifi AP active");
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
  }else if (WIFI_AP_ACTIVE){
    Serial.println("WIFI_AP"); 
    WiFi.mode(WIFI_AP); //Access Point mode
    WiFi.softAP(USER_MQTT_CLIENT_NAME"_AP", apPassword);
    Serial.println("Wifi AP active");
  }else if (WIFI_CONNECT){//Check to see if we have a saved config
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
  }

}

void reconnect() 
{
  // Loop until we're reconnected
  int retries = 0;
  while (!client.connected()) {
    if(retries < 150)
    {
      mqttConnect();
      retries++;
    }
    if(retries > 1500)
    {
      Serial.println("Unable to connect to WIFI router");
      ESP.restart();
    }
  }
}
