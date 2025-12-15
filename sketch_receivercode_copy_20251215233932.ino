#include <VirtualWire.h>

#define RF_RX_PIN 11     // RF Receiver data pin
#define BUZZER_PIN 3
#define LED_PIN 4

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  vw_set_rx_pin(RF_RX_PIN);
  vw_setup(2000);
  vw_rx_start();          // Start receiver

  Serial.begin(9600);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    buf[buflen] = '\0';   // Convert to string
    Serial.print("Message received: ");
    Serial.println((char*)buf);

    if (strcmp((char*)buf, "ACCIDENT") == 0) {
      digitalWrite(BUZZER_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);

      delay(5000);

      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }
  }
}
