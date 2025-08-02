#include <LiquidCrystal.h>

// Define pins for the LCD screen (RS, Enable, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define pins for the LEDs
const int LED_GREEN = 9;
const int LED_YELLOW = 8;
const int LED_RED = 7;

const int RGB_RED_LED = 10;
const int RGB_GREEN_LED = 6;

// Define the pin for the Gas Sensor's analog output
const int GAS_SENSOR_PIN = A0;

// Define the pin for the TMP36 temperature sensor
const int TMP36_PIN = A1;

// Define thresholds for temperature in celcius
const float HOT_TEMP_THRESHOLD = 30.0; //Above this value, the temperature is considered hot/alarming
const float WARM_TEMP_TRESHOLD = 25.0; 

// Define thresholds for air quality alerts
const int GOOD_AIR_THRESHOLD = 90; // Below this value, air quality is considered optimal
const int MEDIUM_AIR_THRESHOLD = 170; // Below this value, air quality is considered average

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize the LCD screen
  lcd.begin(16, 2);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(RGB_RED_LED, OUTPUT);
  pinMode(RGB_GREEN_LED, OUTPUT);
  
  // Display a startup message
  lcd.clear();
  lcd.print("Safe-T");
  lcd.setCursor(0, 1);
  lcd.print("Starting up...");
  delay(2000);
}

void loop() {
  
  // Read the analog value from the TMP36 sensor
  int tempAnalogValue = analogRead(TMP36_PIN);
  
  // Convert the analog value to voltage
  float voltage = tempAnalogValue * (5.0 / 1024.0);
  
  // Convert the voltage to temperature in Celsius
  // The TMP36 outputs 10mV per degree Celsius with a 500mV offset for negative temperatures
  float temp = (voltage - 0.5) * 100;
  
  // Read the analog value from the Gas Sensor
  int airQualityValue = analogRead(GAS_SENSOR_PIN);
  
  lcd.clear();
  
  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
  
  initializeLeds();
  
  if (temp < WARM_TEMP_TRESHOLD) {
   digitalWrite(RGB_GREEN_LED, HIGH);
  } else if (temp < HOT_TEMP_THRESHOLD ) {
   digitalWrite(RGB_GREEN_LED, HIGH);
   digitalWrite(RGB_RED_LED, HIGH);
  } else {
   digitalWrite(RGB_RED_LED, HIGH);
  }

  // Display air quality status on the second line and control LEDs
  lcd.setCursor(0, 1);

  if (airQualityValue < GOOD_AIR_THRESHOLD) {
    digitalWrite(LED_GREEN, HIGH);
    lcd.print("Air: OPTIMAL");
  } else if (airQualityValue < MEDIUM_AIR_THRESHOLD) {
    digitalWrite(LED_YELLOW, HIGH);
    lcd.print("Air: AVERAGE");
  } else {
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

void initializeLeds() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(RGB_RED_LED, LOW);
  digitalWrite(RGB_GREEN_LED, LOW);
}