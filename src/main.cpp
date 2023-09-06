#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled.
#endif

BluetoothSerial SerialBT;
String incoming = "";

void setup() {
    Serial.begin(115200);
    SerialBT.begin("BT-Classic-Ping-Pong");
    Serial.println("Bluetooth device started.");
}

void loop() {
    if (SerialBT.available()) {
        char received = char(SerialBT.read());
        incoming += received;

        if (incoming.endsWith("Ping")) {
            SerialBT.write((uint8_t*) "Pong\n", 5);
            incoming = "";
        }
    }

    delay(20);
}
