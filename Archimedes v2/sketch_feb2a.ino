/*
 * 'Archimedes' Linear Optical Photonic Processor
 * Author: James Eckhart, Jr.
 * "Rise above oneself and grasp the world." - Archimedes
 */

const int TRIGGER_PIN = 2;   // Pulses the quantum circuit
const int H_PIN = A0;        // Measures horizontally polarized photons
const int V_PIN = A1;        // Measures vertically polarized photons
const int LED_PIN = 13;      // Onboard LED for visual feedback

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println("=== Archimedes Photonic Processor Initialized ===");
}

int generateRandomBit() {
  // Pulse the laser
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(100);
  digitalWrite(TRIGGER_PIN, LOW);

  // Read photon polarization levels
  float hValue = analogRead(H_PIN);
  float vValue = analogRead(V_PIN);

  // Determine random bit
  if (hValue > vValue) {
    digitalWrite(LED_PIN, LOW);  // Indicate bit 0
    return 0;
  } else if (hValue < vValue) {
    digitalWrite(LED_PIN, HIGH); // Indicate bit 1
    return 1;
  } else {
    // Equal photon counts — retry until a bit is generated
    return generateRandomBit();
  }
}

void loop() {
  int bit = generateRandomBit();
  Serial.print(" Quantum Bit -- Ket: |");
  Serial.print(bit);
  Serial.println(">");
  delay(1000); // Slight delay for readability
}