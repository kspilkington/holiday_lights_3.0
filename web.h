
void handleIndex();
void handleNotFound();
void handleSetPower();
void handleGetPower();
void handleSwitchOff();
void handleGetColour();
void handleSetColour();
void handleSetBrightness();
void handleGetBrightness();
void handleSelectMode();
void set_color(byte);
void light_up_all();
void turn_off_all();
void badParam(String param);

#include "webHtml.h"

void setupWeb() {

  webServer.on ( "/", handleIndex );
  webServer.onNotFound ( handleNotFound );
  
  webServer.on ( "/togglePower",  handleSetPower);
  webServer.on ("/power", handleGetPower);
  webServer.on ( "/colorPicker",handleGetColorPicker);
  webServer.on ( "/color", HTTP_POST, handleSetColor );
  webServer.on("/color", handleGetColor);
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

void handleIndex(){
Serial.println ( "Request for index page received" );
server.send ( 200, "text/html", page_contents);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}

void handleGetColorPicker() {
Serial.println ( "Request for color picker received" );
server.send ( 200, "text/html", color_picker);

}

void handleSetColor() {
    String param = webServer.arg("color");


}

void handleGetColor() {
    String message="";
    String param = webServer.arg("color");
    if (param ==  "1") {
      message = (String)""+gColors[0].red+""+gColors[0].green+""+gColors[0].blue;
    }else if (param ==  "2") {
      message = (String)""+gColors[1].red+""+gColors[1].green+""+gColors[1].blue;
    }else if (param ==  "3") {
      message = (String)""+gColors[2].red+""+gColors[2].green+""+gColors[2].blue;
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
