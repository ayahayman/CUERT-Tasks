#include <DHT.h>

#define DHTPIN 2         // Pin connected to the DHT22 data pin
#define DHTTYPE DHT22    // Define the type of sensor used
#define FAN_PIN 9        // PWM pin connected to the fan

DHT dht(DHTPIN, DHTTYPE); // Create an instance of the DHT class

const float setpointTemperature = 25.0; // Desired temperature setpoint (in Celsius)

const unsigned long tempInterval = 100;    // Temperature sampling interval
const unsigned long humidityInterval = 200; // Humidity sampling interval

unsigned long lastTempMillis = 0; // Stores the time of last temperature reading
unsigned long lastHumidityMillis = 0; // Stores last humidity

float temperature = 0.0;
float humidity = 0.0;
int fanSpeed = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  dht.begin();        // Initialize the DHT sensor
  pinMode(FAN_PIN, OUTPUT); // Set fan pin as an output
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastHumidityMillis >= humidityInterval) { // Read humidity every 200 ms
    lastHumidityMillis = currentMillis;
    humidity = dht.readHumidity();
  }
  
  if (currentMillis - lastTempMillis >= tempInterval) { // Read temperature every 100 ms
    lastTempMillis = currentMillis;
    temperature = dht.readTemperature();
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Fan Speed: ");
    Serial.print(fanSpeed);
    Serial.println(" %");
  }
  
  fanSpeed = map(constrain((int)temperature, 25, 125), 25, 125, 0, 255); // Control fan speed based on temperature
  analogWrite(FAN_PIN, fanSpeed);
}
