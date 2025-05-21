#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEAdvertising.h>

void setup() {
  Serial.begin(115200);
  // Initialize BLE stack without setting any local name
  BLEDevice::init("Beacon-003");  // no DEVICE_NAME needed for scanning

  // Grab the advertiser and start broadcasting empty/anonymous advertisements
  BLEAdvertising *adv = BLEDevice::getAdvertising();
  adv->setScanResponse(false);  // no scan-response either
  adv->start();

  Serial.println("BLE radio enabled, advertising anonymously.");
}

void loop() {
  // nothing else needed
}
 