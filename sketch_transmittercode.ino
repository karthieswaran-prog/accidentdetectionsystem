#include <VirtualWire.h>

#define VIBRATION_PIN 2     // Digital output of vibration sensor
#define RF_TX_PIN 12        // RF Transmitter data pin

void setup() {
  pinMode(VIBRATION_PIN, INPUT);

  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000);           // Bits per second

  Serial.begin(9600);
}

void loop() {
  int vibration = digitalRead(VIBRATION_PIN);

  if (vibration == HIGH) {   // Accident detected
    const char *msg = "ACCIDENT";

    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx();            // Wait until message is sent

    Serial.println("Accident detected! Signal sent.");

    delay(3000);             // Prevent repeated signals
  }
}
