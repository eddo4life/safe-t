#include <LiquidCrystal.h>

// Define pins for the LCD screen (RS, Enable, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int RESET_BUTTON = 13;

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
const float HOT_TEMP_THRESHOLD = 30.0;
const float WARM_TEMP_TRESHOLD = 25.0; 

// Define thresholds for air quality alerts
int GOOD_AIR_THRESHOLD = 285;
int MEDIUM_AIR_THRESHOLD = 450;

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
  pinMode(RESET_BUTTON, INPUT);
  
  // Display a startup message
  showStartupMessage();
}

void loop() {
  // Check for reset button press
  if (digitalRead(RESET_BUTTON) == HIGH) { 
    handleReset();
    delay(300); // Debounce delay
    return; // Skip the rest of the loop for this iteration
  } 
  
  // Normal operation if not reset
  readAndDisplaySensors();
  
  // Short pause for system stability
  delay(2000);
}

void readAndDisplaySensors() {
  // Read temperature
  int tempAnalogValue = analogRead(TMP36_PIN);
  float voltage = tempAnalogValue * (5.0 / 1024.0);
  float temp = (voltage - 0.5) * 100;
  
  // Read air quality
  int airQualityValue = analogRead(GAS_SENSOR_PIN);
  
  lcd.clear();
  
  // Display temperature
  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
  
  initializeLeds();
  
  // Control RGB LEDs based on temperature
  if (temp < WARM_TEMP_TRESHOLD) {
    digitalWrite(RGB_GREEN_LED, HIGH);
  } else if (temp < HOT_TEMP_THRESHOLD) {
    digitalWrite(RGB_GREEN_LED, HIGH);
    digitalWrite(RGB_RED_LED, HIGH);
  } else {
    digitalWrite(RGB_RED_LED, HIGH);
  }

  // Display air quality status and control LEDs
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
  
  // Debug output
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *C\t");
  Serial.print("Air Quality: ");
  Serial.println(airQualityValue);
}

void initializeLeds() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(RGB_RED_LED, LOW);
  digitalWrite(RGB_GREEN_LED, LOW);
}

void handleReset() {
  Serial.println("System reset triggered");
  initializeLeds();
  lcd.clear();
  lcd.print("System Reset");
  lcd.setCursor(0, 1);
  lcd.print("Please wait...");
  
  // Wait while the reset button is still pressed
  int count = 0;
  while (digitalRead(RESET_BUTTON) == HIGH) {
    delay(100);
    if (count == 30) {
      lcd.clear();
      lcd.print("Hold detected...");
      lcd.setCursor(0, 1);
      lcd.print("Release to boot");
    }
    count++;
  }

  delay(1000);
  showStartupMessage();
}
  
void showStartupMessage() {
  lcd.clear();
  lcd.print("Safe-T");
  lcd.setCursor(0, 1);
  lcd.print("Starting up...");
  delay(2000);
}