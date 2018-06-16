#include <SlaveCommunicationManager.hpp>

void setup() {
  // put your setup code here, to run once:
}

void loop() {
   BluetoothPacket packet;
   packet.buttonData = 0x0F;
   packet.deviceState = 0x0A; 
   SlaveCommunicationManager::shared()->send(packet, false);
   SlaveCommunicationManager::shared()->update();
} 
