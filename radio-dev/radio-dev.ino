#include <SoftwareSerial.h>

SoftwareSerial hm10(2, 3);  // RX, TX

void setup() {
  Serial.begin(115200);     // USB serial
  hm10.begin(9600);         // HM-10 UART
  Serial.println("Radio Dev Example");

}

void loop() {
  // HM-10 -> USB serial monitor
if (hm10.available()) {
    int value = hm10.read();
    Serial.println(value);
}

  // USB serial monitor -> HM-10
  if (Serial.available()) {
    Serial.println("Pushing Data");
    hm10.write(Serial.read());
  }
}