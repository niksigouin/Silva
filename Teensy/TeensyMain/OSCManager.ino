void initOSC() {
  // Wire1
  // SCL = 16    SDA = 17
  Wire1.begin(WIRE_ADDR);
  Wire1.onReceive(receiveOSC);
}

void receiveOSC(int byteLength) {
  // define OSC bundle
  OSCBundle bundleIN;

  // decode incoming OSC message
  while (Wire1.available()) {
    bundleIN.fill(Wire1.read());
  }

  if (!bundleIN.hasError()) {
    // list of callbacks
    bundleIN.dispatch("/audio/test", audioTest);

    // lantern events
    bundleIN.dispatch("/lantern/setID", setLanternID);
    bundleIN.dispatch("/lantern/ignite", igniteLantern);
    bundleIN.dispatch("/lantern/extinguish", extinguishLantern);

    // organique events
    bundleIN.dispatch("/organique/enter_tree", enterTree);
    bundleIN.dispatch("/organique/leave_tree", leaveTree);

    // silva events
  }
}
