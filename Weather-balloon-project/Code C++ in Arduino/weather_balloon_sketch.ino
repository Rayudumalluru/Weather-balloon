#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3HUO_Rf2A"
#define BLYNK_TEMPLATE_NAME "WEATHER MONITORING SYSTEM"
#define BLYNK_AUTH_TOKEN "dJNV30B6BTQIC3cIDOFCbkf24CSn6olp"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

// -------- WiFi --------
char ssid[] = "WIFI-NAME";
char pass[] = "WIFI-PASSWORD";

// -------- Sensors --------
Adafruit_BMP280 bmp;

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN 34

// MQ calibration (adjust later)
float R0 = 10.0;

BlynkTimer timer;

// -------- Moving Average --------
#define FILTER_SIZE 10
float mqBuffer[FILTER_SIZE];
int mqIndex = 0;

// -------- ADC Setup --------
void setupADC() {
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
}

// -------- MQ135 Resistance --------
float getResistance(int adc) {
  float voltage = adc * (3.3 / 4095.0);
  if (voltage <= 0.01) return 0;
  return ((3.3 - voltage) / voltage) * 10.0;
}

// -------- Filtered ADC --------
int getFilteredADC() {
  int raw = analogRead(MQ135_PIN);

  mqBuffer[mqIndex] = raw;
  mqIndex = (mqIndex + 1) % FILTER_SIZE;

  float sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    sum += mqBuffer[i];
  }

  return sum / FILTER_SIZE;
}

// -------- MAIN FUNCTION --------
void sendData() {

  Serial.println("------ SENSOR DATA ------");

  // ===== BMP280 =====
  float temp_bmp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(1013.25);

  if (!isnan(temp_bmp) && !isnan(pressure)) {
    Blynk.virtualWrite(V0, temp_bmp);
    Blynk.virtualWrite(V1, pressure);
    Blynk.virtualWrite(V2, altitude);

    Serial.printf("BMP Temp: %.2f | Pressure: %.2f | Alt: %.2f\n",
                  temp_bmp, pressure, altitude);
  } else {
    Serial.println("BMP280 ERROR");
  }

  // ===== DHT11 =====
  float humidity = dht.readHumidity();
  float temp_dht = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temp_dht)) {
    Blynk.virtualWrite(V3, temp_dht);
    Blynk.virtualWrite(V4, humidity);

    Serial.printf("DHT Temp: %.2f | Humidity: %.2f\n",
                  temp_dht, humidity);
  } else {
    Serial.println("DHT11 ERROR");
  }

  // ===== MQ-135 (REAL) =====
  int adc = getFilteredADC();
  float rs = getResistance(adc);

  if (rs > 0) {
    float ratio = rs / R0;

    // CO2 approximation
    float co2 = 116.6020682 * pow(ratio, -2.769034857);

    // Clamp realistic range
    if (co2 < 350) co2 = 350;
    if (co2 > 5000) co2 = 5000;

    // AQI mapping
    float aqi = map(co2, 400, 2000, 50, 300);
    if (aqi < 0) aqi = 0;
    if (aqi > 500) aqi = 500;

    Blynk.virtualWrite(V5, aqi);
    Blynk.virtualWrite(V6, co2);

    Serial.printf("ADC: %d | RS: %.2f | CO2: %.2f ppm | AQI: %.2f\n",
                  adc, rs, co2, aqi);
  } else {
    Serial.println("MQ135 ERROR");
  }

  Serial.println("--------------------------\n");
}

// -------- SETUP --------
void setup() {
  Serial.begin(115200);
  delay(1000);

  setupADC();
  Wire.begin(21, 22);
  dht.begin();

  // BMP init
  if (!bmp.begin(0x76)) {
    if (!bmp.begin(0x77)) {
      Serial.println("BMP280 NOT FOUND!");
      while (1);
    }
  }

  Serial.println("Sensors initialized");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendData);
}

// -------- LOOP --------
void loop() {
  Blynk.run();
  timer.run();
}