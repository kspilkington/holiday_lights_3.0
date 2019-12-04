void handleRoot();

void setupWeb(){

  webServer.on("/",handleRoot());

  webServer.on("/color1",HTTP_POST,[](){
    
  });
  webServer.begin();
}

  
void handleWeb() {
  static bool webServerStarted = false;

  // check for connection
  if ( WiFi.status() == WL_CONNECTED ) {
    if (!webServerStarted) {
      // turn off the board's LED when connected to wifi
      digitalWrite(LED, 1);
      Serial.println();
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      webServerStarted = true;
      setupWeb();
    }
    webServer.handleClient();
  } else {
    // blink the board's LED while connecting to wifi
    static uint8_t ledState = 0;
    EVERY_N_MILLIS(125) {
      ledState = ledState == 0 ? 1 : 0;
      digitalWrite(LED, ledState);
      Serial.print (".");
    }
  }
}

void handleRoot(){
  webServer.send(200,"text/html","
  
  ");
}
