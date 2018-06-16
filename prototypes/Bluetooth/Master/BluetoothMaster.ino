#include <MasterCommunicationManager.hpp>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
    MasterCommunicationManager::shared()->update();

    BluetoothPacket receivedPacket = MasterCommunicationManager::shared()->getData();

    if (receivedPacket.isPopulated) {
        Serial.print("Button Data ");
        Serial.println(receivedPacket.buttonData, BIN);
        Serial.print("State ");
        Serial.println(receivedPacket.deviceState, BIN);
    }
}
