#include <LiquidCrystal.h>

// Define pins for the LCD screen (RS, Enable, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define pins for the LEDs
const int LED_GREEN = 9;
const int LED_YELLOW = 8;
const int LED_RED = 7;

// Define the pin for the Gas Sensor's analog output
const int GAS_SENSOR_PIN = A0;

// Define the pin for the TMP36 temperature sensor
const int TMP36_PIN = A1;

// Define thresholds for air quality alerts
const int GOOD_AIR_THRESHOLD = 90; // Below this value, air quality is considered optimal
const int MEDIUM_AIR_THRESHOLD = 170; // Between these values, air quality is considered average

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the LCD screen
  lcd.begin(16, 2);
  

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Display a startup message
  lcd.clear();
  lcd.print("Safe-T Project");
  lcd.setCursor(0, 1);
  lcd.print("Starting up...");
  delay(2000);
}

void loop() {
  // --- Read values from sensors ---
  
  // Read the analog value from the TMP36 sensor
  int tempAnalogValue = analogRead(TMP36_PIN);
  
  // Convert the analog value to voltage
  float voltage = tempAnalogValue * (5.0 / 1024.0);
  
  // Convert the voltage to temperature in Celsius
  // The TMP36 outputs 10mV per degree Celsius with a 500mV offset for negative temperatures
  float temp = (voltage - 0.5) * 100;
  
  // Read the analog value from the Gas Sensor
  int airQualityValue = analogRead(GAS_SENSOR_PIN);
  
  // --- Logic for controlling LEDs and LCD screen ---
  
  lcd.clear();
  
  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  // Display air quality status on the second line and control LEDs
  lcd.setCursor(0, 1);

  if (airQualityValue < GOOD_AIR_THRESHOLD) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    lcd.print("Air: OPTIMAL");
  } else if (airQualityValue >= GOOD_AIR_THRESHOLD && airQualityValue < MEDIUM_AIR_THRESHOLD) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
    lcd.print("Air: AVERAGE");
  } else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    lcd.print("Air: POOR!");
  }
  
  // Printing values to the Serial Monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *C\t");
  Serial.print("Air Quality (Gas Sensor): ");
  Serial.println(airQualityValue);
  
  // Short pause for system stability
  delay(2000);
}
