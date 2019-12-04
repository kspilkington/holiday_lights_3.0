
void setup_wifi() 
{
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.persistent(true);
  if (WIFI_AP){
    WiFi.mode(WIFI_AP); //Access Point mode
    WiFi.softAP(mqtt_client_name+"_AP", apPassword);
    Serial.println("Wifi AP active");
  }

  if (WIFI_CONNECT){//Check to see if we have a saved config
    WiFi.mode(WIFI_STA); //Connectto your wifi
    WiFi.setHostname(mqtt_client_name);
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

void connectToRouter(char *ssid, char *password){
  Wifi.setConfig(ssid, password);
  WiFi.setHostname(mqtt_client_name);
  WiFi.mode(WIFI_STA);
  wifi.begin();
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
      Serial.println("Unable to connect to WIFI router");
      ESP.restart();
    }
  }
}


