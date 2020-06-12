#include "arduino_secrets.h"
#include "thingProperties.h"

// Libraries
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "Adafruit_SSD1306.h"

// BMP280
#define BMP280_I2C_ADDRESS 0x76
Adafruit_BMP280 bmp280;

// DHT
#define DHTPIN 6
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ssd1306
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  
  bmp280.begin(BMP280_I2C_ADDRESS);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  delay(1500); 
  initProperties();// Defined in thingProperties.h
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);// Connect to Arduino IoT Cloud
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  delay(2000);
  rHumidity = dht.readHumidity();
  rTemperature = dht.readTemperature();
  rPressure = bmp280.readPressure() /100; // divided by 100 to return Hectopascal(hPa)
  rTempIndex = dht.computeHeatIndex((rTemperature), rHumidity, false);
  
  Serial.println((String)"DHT - Temp Raw:    " + rTemperature);
  Serial.println((String)"DHT - Temp Index:  " + rTempIndex);
  Serial.println((String)"DHT - Humidity:    " + rHumidity);
  Serial.println((String)"BMP - Pressure:    " + rPressure);
  Serial.println();
  
  display.setTextColor(WHITE);
  
  display.setCursor(0,2);
  display.setTextSize(1);    
  display.print("Temperature:");
  
  display.setCursor(96,2);
  display.setTextSize(1);    
  display.print(rTempIndex);

  display.setCursor(0,13);
  display.setTextSize(1);    
  display.print("Humidity:");
  
  display.setCursor(96,13);
  display.setTextSize(1);    
  display.print(rHumidity);

  display.setCursor(0,24);
  display.setTextSize(1);    
  display.print("Pressure:");
  
  display.setCursor(84,24);
  display.setTextSize(1);    
  display.print(rPressure);

  display.display();
  display.clearDisplay();  
  
}
