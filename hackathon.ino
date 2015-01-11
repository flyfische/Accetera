#include <Wire.h>
#include "rgb_lcd.h"
#include <SPI.h>
#include <SD.h>

rgb_lcd lcd;
File settingsFile;

int B=3975;                  // B value of the thermistor
float resistance;
float temperature;

const int pinTemp = A0;
const int pinLed = 3;
const int rotary = A1;

const int colorR = 112;
const int colorG = 39;  // This default color is PURPLE
const int colorB = 195;





void setup() 
{
    Serial.begin(9600);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    
    pinMode(pinLed, OUTPUT);
    pinMode(rotary, INPUT);
    pinMode(10, OUTPUT);
    
    Serial.print("Initializing SD card");
    if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
    
}

void loop() 
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("CurrentTemp: ");
    lcd.setCursor(0,1);
    lcd.print("Set Temp: ");
    int val = analogRead(pinTemp);                               // get analog value
    resistance=(float)(1023-val)*10000/val;                      // get resistance
    temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;     // calc temperature
    float temperatureF = (9.0/5.0 * temperature) + 32.0;
    lcd.setCursor(12,0);
    int currentTemp = temperatureF;
    lcd.print(currentTemp);
    int potValue = ((analogRead(rotary) / 1020.0) * 20.0) + 60.0;
    int pastValue = getPotValue();
    if (abs(potValue - pastValue) > 0.75) {
      int value = potValue;
      logPotValue(potValue);
      logSetTemp(potValue);
    }
    else {
        int value = getSetTemp();
    }
    int value = getSetTemp();
    if(temperatureF < value) {
	callHeat(pinLed);      
    }
    else {
	dismissHeat(pinLed);      
    }
    lcd.setCursor(12,1);
    logTemp(temperatureF);
   // logSetTemp(value);
    lcd.print(value);
    delay(1000);
}

void callHeat(int ledpin) {
	analogWrite(ledpin, 255);
       // lcd.setRGB(255, 0, 0); //This sets the LCD to RED to indicate calling heat.
	//code to turn on relay
}
void dismissHeat(int ledpin) {
	analogWrite(ledpin, 0);
       // lcd.setRGB(0, 0, 255); // This sets the LCD to BLUE to indicate no heat.
	//code to turn off relay
}

void logTemp(float temp) {
        SD.remove("current.txt");
	settingsFile = SD.open("current.txt", FILE_WRITE);
	if (settingsFile) {
		settingsFile.println(temp);
		Serial.println("Wrote current temp");
                settingsFile.close();
	}
}

void logSetTemp(float temp) {
        SD.remove("setTemp.txt");
	settingsFile = SD.open("setTemp.txt", FILE_WRITE);
	if (settingsFile) {
		settingsFile.println(temp);
		Serial.println("Wrote set temp");
                settingsFile.close();
	}
}

float getTemp() {
        String file_contents = "";
        char char1[32];
	settingsFile = SD.open("current.txt");
        while (settingsFile.available()) {
          file_contents += (char)settingsFile.read();
        }	
        settingsFile.close();
       file_contents.toCharArray(char1, sizeof(char1) + 1);
       return atof(char1);
       
}

float getSetTemp() {
        String file_contents = "";
        char char1[32];
	settingsFile = SD.open("setTemp.txt");
        while (settingsFile.available()) {
          file_contents += (char)settingsFile.read();
        }	
        settingsFile.close();
       file_contents.toCharArray(char1, sizeof(char1) + 1);
       return atof(char1);
       
}

void logPotValue(float temp) {
        SD.remove("potVal.txt");
	settingsFile = SD.open("potVal.txt", FILE_WRITE);
	if (settingsFile) {
		settingsFile.println(temp);
		Serial.println("Wrote pot value");
                settingsFile.close();
	}
}

float getPotValue() {
        String file_contents = "";
        char char1[32];
	settingsFile = SD.open("potVal.txt");
        while (settingsFile.available()) {
          file_contents += (char)settingsFile.read();
        }	
        settingsFile.close();
       file_contents.toCharArray(char1, sizeof(char1) + 1);
       return atof(char1);
       
}


