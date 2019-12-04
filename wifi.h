
void setup_wifi() 
{
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  if (WIFI_AP){
    WiFi.mode(WIFI_AP); //Access Point mode
    WiFi.softAP(USER_MQTT_CLIENT_NAME+"_AP", USER_AP_PASSWORD);
    Serial.println("Wifi AP active");
  }

  if (WIFI_CONNECT){
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
    }
    if(retries > 1500)
    {
    ESP.restart();
    }
  }
}


