#ifndef OSC_MANAGER
#define OSC_MANAGER

#include "objects.h"
#include "lantern_events.h"
#include "organique_events.h"


// functions
void receiveOSC(int byteLength);
void initOSC();


void initOSC() {
  // Wire1
  // SCL = 16    SDA = 17
  Wire1.begin(WIRE_ADDR);
  Wire1.onReceive(receiveOSC);
}

void receiveOSC(int byteLength) {
  AudioNoInterrupts();

  Serial.println("receiving OSC...");
  
  // define OSC bundle
  OSCMessage bundleIN;

  // decode incoming OSC message
  while (Wire1.available()) {
    char c = Wire1.read();
    Serial.print((byte)c);
    Serial.print(" ");
    bundleIN.fill(c);
    // delayMicroseconds(100);
  }
  Serial.println();

  Serial.print("err: ");
  Serial.println(bundleIN.hasError());
  
  // char* addr;
  // msg.getAddress(addr);
  // Serial.print("addr: ");
  // Serial.println(addr);

  if (!bundleIN.hasError()) {
    // // lantern events
    // bundleIN.dispatch("/lantern/*/audio/setID", setLanternID);
    bundleIN.dispatch("/li", igniteLantern);
    bundleIN.dispatch("/le", extinguishLantern);

    // // organique events
    bundleIN.dispatch("/on", enterTree);
    bundleIN.dispatch("/ox", exitTree);

    // // silva events
  }

  AudioInterrupts();
}

#endif
