#include <SPI.h>
#include <mcp_can.h>

//Constants
const int CAN_CS = 5;

MCP_CAN CAN(CAN_CS);

void setup() {
    Serial.begin(115200);
    SPI.begin(18, 19, 23, CAN_CS);
    // If cannot link to CAN
    while (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) != CAN_OK) {
        Serial.println("Retrying! CAN init failed");
        delay(500);
    }

    CAN.setMode(MCP_NORMAL);
    Serial.println("ESP32 is ready!");
}

// Sends one CAN message with 4 motor speeds (-100 reverse, 0 stop, 100 forward)
void driveMotor(int8_t m0, int8_t m1, int8_t m2, int8_t m3) {
    byte data[4] = {(byte)m0, (byte)m1, (byte)m2, (byte)m3};
    if (CAN.sendMsgBuf(0x100, 0, 4, data) != CAN_OK) {
        Serial.println("send failed");
    }
}

// Keeps sending the same command for ms milliseconds
void driveDuration(int8_t m0, int8_t m1, int8_t m2, int8_t m3, unsigned long ms) {
    unsigned long start = millis();
    while (millis() - start < ms) {
        driveMotor(m0, m1, m2, m3);
        delay(100);
    }
}

void loop() {
    Serial.println("forward");
    driveDuration(60, 60, 60, 60, 1000);
    Serial.println("stop");
    driveDuration(0, 0, 0, 0, 1000);
    Serial.println("reverse");
    driveDuration(-60, -60, -60, -60, 1000);
    Serial.println("stop");
    driveDuration(0, 0, 0, 0, 1000);
    delay(3000);      
}