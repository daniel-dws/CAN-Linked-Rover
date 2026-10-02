#include <SPI.h>
#include <mcp_can.h>

const int CAN_CS = 5; //ENA 
MCP_CAN CAN(CAN_CS);

void sendDrive(byte dir, byte speed) {   // dir: 0 stop, 1 fwd, 2 rev
  byte data[2] = { dir, speed };
  if (CAN.sendMsgBuf(0x100, 0, 2, data) != CAN_OK) Serial.println("send failed");
}

void holdFor(byte dir, byte speed, unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {        // resend so the Uno's auto-stop doesn't trip
    sendDrive(dir, speed);
    delay(100);
  }
}

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23, CAN_CS);         // SCK, MISO, MOSI, CS
  while (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK) {   // MCP_16MHZ if needed
    Serial.println("CAN init failed, retrying");
    delay(500);
  }
  CAN.setMode(MCP_NORMAL);
  Serial.println("ESP32 ready");
}

void loop() {
  Serial.println("forward");  holdFor(1, 200, 1000);
  Serial.println("stop");     holdFor(0, 0, 1000);
  Serial.println("reverse");  holdFor(2, 200, 1000);
  Serial.println("stop");     holdFor(0, 0, 1000);
  delay(3000);                            // no messages: Uno should auto-stop
}