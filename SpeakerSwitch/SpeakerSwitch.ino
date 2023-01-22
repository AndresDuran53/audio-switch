#include "IoTController.h"

#define SPEAKER_PIN  13

String deviceType = "speaker-switch";
String deviceToken = "nag241";
short consoleLevel = 3;
boolean lastStatus = false;

void configGPIO() {
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_PIN, LOW);
}

void setSpeakerStatus(String newStatus) {
  Logger::log("Setting New Speaker Status: " + newStatus, Logger::INFO_LOG);
  boolean boolStatus = false;
  if (newStatus == "0") boolStatus = true;
  digitalWrite(SPEAKER_PIN, boolStatus);
  lastStatus = boolStatus;
}

void setup() {
  configGPIO();
  IoTController::setup(deviceType, consoleLevel, deviceToken);
  IoTController::createStoredData("speaker_status", "spst", 2, "0", "String", [](String newStatus) {setSpeakerStatus(newStatus);});
  IoTController::init();
}

void loop() {
  IoTController::loop();
}
