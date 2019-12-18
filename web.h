void handleRoot();
void changeColor();
void getColor();
void getAnimationWeb();
void changeAnimationWeb();
void badParam(String param);

void setupWeb() {

  webServer.on("/", handleRoot);
  webServer.on("/web", HTTP_POST, changeAnimationWeb);
  webServer.on("/web", HTTP_GET, getAnimationWeb);
  webServer.on("/color", HTTP_POST, changeColor);
  webServer.on("/color", HTTP_GET, getColor);
  webServer.begin();
}


void handleWeb() {
  static bool webServerStarted = false;

  // check for connection
  if ( wifiApActive || WiFi.status() == WL_CONNECTED) {
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

void handleRoot() {
  webServer.send(200, "text/html", "");
}

void changeColor() {

}

void getColor() {
    String message="";
    String param = webServer.arg("color");
    if (param ==  "1") {
      message = (String)""+gColors[0];
    }else if (param ==  "2") {
      message = (String)""+gColors[1];
    }else if (param ==  "3") {
      message = (String)""+gColors[2];
    }
    if (message !=""){
      webServer.send(200,"text/plain",message);
    }else {
      badParam("color");
    }
}

void badParam(String param){
      webServer.send(400,"text/plain","No parameter: "+param);
}

void getAnimationWeb() {

}

void changeAnimationWeb() {

}
