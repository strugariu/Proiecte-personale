#include "AFMotor_R4.h"
#include <IRremote.hpp>

// IR setup
#define IR_RECEIVE_PIN 14   // A0 = D14

// Define 4 motors (no frequency parameters)
AF_DCMotor motorFL(1); // Front-left
AF_DCMotor motorBL(2); // Back-left
AF_DCMotor motorFR(3); // Front-right
AF_DCMotor motorBR(4); // Back-right

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // IR receiver start
  Serial.println("4-Motor IR RC Car Ready!");

  // Set initial motor speed (0–255)
  int speed = 200;
  motorFL.setSpeed(speed);
  motorBL.setSpeed(speed);
  motorFR.setSpeed(speed);
  motorBR.setSpeed(speed);
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t code = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("IR Code: 0x");
    Serial.println(code, HEX);

    switch (code) {
      case 0xF30CFF00: // Button 1 → Forward
        Serial.println("Forward");
        motorFL.run(FORWARD);
        motorBL.run(FORWARD);
        motorFR.run(FORWARD);
        motorBR.run(FORWARD);
        break;

      case 0xE718FF00: // Button 2 → Backward
        Serial.println("Backward");
        motorFL.run(BACKWARD);
        motorBL.run(BACKWARD);
        motorFR.run(BACKWARD);
        motorBR.run(BACKWARD);
        break;

      case 0xA15EFF00: // Button 3 → Brake / Stop
        Serial.println("Brake");
        motorFL.run(RELEASE);
        motorBL.run(RELEASE);
        motorFR.run(RELEASE);
        motorBR.run(RELEASE);
        break;

      default:
        // Ignore unknown signals
        break;
    }

    IrReceiver.resume(); // ready for next IR code
  }
}
