#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <Adafruit_NeoPixel.h>

// NeoPixel configuration
#define PIN       48
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// BLE scan
BLEScan* bleScan;

// Function to map RSSI (negative) to 0-255 brightness
uint8_t rssiToBrightness(int rssi) {
  int b = 256 + rssi*10; // e.g. rssi -1 -> 255
  if (b < 0) b = 0;
  if (b > 255) b = 255;
  return (uint8_t)b;
}

// Current color channels
uint8_t redChannel = 0;
uint8_t greenChannel = 0;
uint8_t blueChannel = 0;

class BeaconCallback : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) override {
    String name = advertisedDevice.getName().c_str();
    int rssi = advertisedDevice.getRSSI();
    uint8_t brightness = rssiToBrightness(rssi);

    if (name == "Beacon-001") {
      redChannel = brightness;
    } else if (name == "Beacon-002") {
      greenChannel = brightness;
    } else if (name == "Beacon-003") {
      blueChannel = brightness;
    } else {
      return; // ignore other devices
    }

    // Update the pixel color combining channels
    pixels.setPixelColor(0, redChannel, greenChannel, blueChannel);
    pixels.show();
  }
};

void setup() {
  Serial.begin(115200);

  // NeoPixel init
  pixels.begin();
  pixels.clear();
  pixels.show();

  // BLE init for scanning
  BLEDevice::init("");
  bleScan = BLEDevice::getScan();
  bleScan->setAdvertisedDeviceCallbacks(new BeaconCallback(), true);
  bleScan->setActiveScan(true);
  bleScan->setInterval(100);
  bleScan->setWindow(99);

  // Start continuous scan
  bleScan->start(0, nullptr, false);
}

void loop() {
  // No action needed; callback updates LED
}
