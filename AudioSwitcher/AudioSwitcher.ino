#include "IoTController.h"

#define RELAY_PIN  13

String deviceType = "audio-switcher";
String deviceToken = "kjf365";
short consoleLevel = 3;
String lastStatus = "0";

void configGPIO() {
  pinMode(RELAY_PIN, OUTPUT);
}

void setSwitchStatus(String newSwtichStatus) {
  if (!lastStatus.equals(newSwtichStatus)) {
    IoTController::sendMqttMessage(newSwtichStatus);
    lastStatus = newSwtichStatus;
  }
}

void setup() {
  IoTController::setup(deviceType, consoleLevel, deviceToken);
  IoTController::addCommonData("switch_status", "swst", 2, "0", "String", [](String newSwtichStatus) {
    setSwitchStatus(newSwtichStatus);
  });
  IoTController::init();
  configGPIO();
}

void loop() {
  IoTController::loop();
}
