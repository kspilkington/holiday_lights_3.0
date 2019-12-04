# holiday_lights_3.0
Basic controller software for a nodeMCU ESP32 to controll a series of WS2812b lights for holiday animation purposes

## Compiling
1) With the required libraries installed and your board set to ESP32 you will need to populate the secrets.h file (not checked in) to get things to compile.
The template for the secrets.h is in the HolidayLights32.01.ino file. This will have your wifi and mqtt variabes
2) The zoneDefinitions.h file details the various strings that have been setup along with their sizes and number of sections


##Support
1) Supports ArduionOTA (if lights are turned off)
2) Any light strand meeting the WS2812b 5050 spec (if you double the data line should even allow that)
3) Currently supports 6 zones (but easy to expand)
4) A button to turn on/off the lights (short press) or if pressed longer than 2.5 seconds, cycles through the various animations
5) Can set animations different per zone/sector (only through mqtt, not the web server)
6) AP mode for use w/o a mqtt server or wifi
7) Webserver for use/changing settings w/o mqtt/Home Assistant

## Libraries used