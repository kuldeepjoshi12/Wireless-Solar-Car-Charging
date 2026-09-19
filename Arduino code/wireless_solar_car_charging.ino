
  Wireless Solar Car Charging Station
  ------------------------------------
  Educational / Prototype Project

  Features:
  - Detects whether a vehicle is present
  - Checks charging platform alignment
  - Turns wireless charging module ON/OFF
  - Provides status through Serial Monitor
  - LED indicates charging status

  IMPORTANT:
  This code is intended for a LOW-VOLTAGE prototype.
  Do not connect Arduino pins directly to an EV battery,
  high-power charging system, or mains electricity.
*/

#define VEHICLE_SENSOR_PIN 2
#define ALIGNMENT_SENSOR_PIN 3

#define CHARGING_RELAY_PIN 8
#define STATUS_LED_PIN 13

// Change this if your sensor works in reverse.
#define SENSOR_ACTIVE LOW

bool charging = false;

void setup() {
  Serial.begin(9600);

  pinMode(VEHICLE_SENSOR_PIN, INPUT);
  pinMode(ALIGNMENT_SENSOR_PIN, INPUT);

  pinMode(CHARGING_RELAY_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);

  // Charging OFF at startup
  digitalWrite(CHARGING_RELAY_PIN, LOW);
  digitalWrite(STATUS_LED_PIN, LOW);

  Serial.println("=================================");
  Serial.println(" Wireless Solar Car Charging");
  Serial.println(" Station");
  Serial.println("=================================");
  Serial.println("System Ready");
}

void loop() {

  bool vehicleDetected =
    digitalRead(VEHICLE_SENSOR_PIN) == SENSOR_ACTIVE;

  bool vehicleAligned =
    digitalRead(ALIGNMENT_SENSOR_PIN) == SENSOR_ACTIVE;

  // Vehicle detected AND correctly aligned
  if (vehicleDetected && vehicleAligned) {

    if (!charging) {
      startCharging();
    }

  } else {

    if (charging) {
      stopCharging();
    }

    // Display reason
    if (!vehicleDetected) {
      Serial.println("Waiting for vehicle...");
    }
    else if (!vehicleAligned) {
      Serial.println("Vehicle detected - Please align vehicle.");
    }
  }

  delay(500);
}


// ---------------------------------
// Start Charging
// ---------------------------------
void startCharging() {

  charging = true;

  digitalWrite(CHARGING_RELAY_PIN, HIGH);
  digitalWrite(STATUS_LED_PIN, HIGH);

  Serial.println("---------------------------------");
  Serial.println("Vehicle Detected");
  Serial.println("Vehicle Aligned");
  Serial.println("Wireless Charging: ON");
  Serial.println("---------------------------------");
}


// ---------------------------------
// Stop Charging
// ---------------------------------
void stopCharging() {

  charging = false;

  digitalWrite(CHARGING_RELAY_PIN, LOW);
  digitalWrite(STATUS_LED_PIN, LOW);

  Serial.println("---------------------------------");
  Serial.println("Wireless Charging: OFF");
  Serial.println("---------------------------------");
}
