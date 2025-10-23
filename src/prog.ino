#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPIFFS.h>
#include <LittleFS.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
#define BUTTON_OPTIONS 5
#define BUTTON_SELECT 17
#define BUTTON_RESET 18
#define BUTTON_START 16
#define POT 4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);
Adafruit_MPU6050 mpu;

class Display{
  private:
  int option = 0;
  int selected = -1;
  const String textOption = "Select Pista:";
  String textSelect = "Lisa";
  int lastState = 0;
  const String textSelected ="Selected Pista:";
  int started = -1;
  int number = 1;
  unsigned long previousMillis;
  int intervalo = 1000;
  

  public:

  bool delayMillis(int interval) {
    intervalo = interval;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= intervalo) {
      previousMillis = currentMillis;
      return true;
    } else {
      return false;
    }
  }

  bool alreadySelected(){
    if (selected != -1){
      return false;
    } else{
      return true;
    }
  }

    bool alreadyStarted(){
    if (started != -1){
      return false;
    } else{
      return true;
    }
  }

  String optionsToText(int n){
    switch (n){
      case 0:
        textSelect = "Lisa";
      return textSelect; 
      case 1:
        textSelect = "Esburacada";
      return textSelect;
      case 2:
        textSelect = "Paralelepipedo";
      return textSelect;
      case 3:
        textSelect = "Placeholder";
      return textSelect;
      case 4:
        textSelect = "Placeholder2";
      return textSelect;
    }
  }
  
  void text(){
    if (alreadySelected()){
      if(lastState != option){
        lastState = option;
        lcd.clear();
      }
      lcd.setCursor(0,0);
      lcd.print(textOption);
      lcd.setCursor(0,1);
      lcd.print(textSelect);
    } else if (alreadyStarted()){
      if(lastState != option){
        lastState = option;
        lcd.clear();
      }
      lcd.setCursor(0,0);
      lcd.print(textSelected);
      lcd.setCursor(0,1);
      lcd.print(textSelect);
    } else{
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      int pot = analogRead(POT);
      if(delayMillis(1000)){
        // lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("X:      ");
        lcd.setCursor(2,0);
        lcd.print(a.acceleration.x);

        lcd.setCursor(8,0);
        lcd.print("Y:      ");
        lcd.setCursor(10,0);
        lcd.print(a.acceleration.y);
      
        lcd.setCursor(0,1);
        lcd.print("Z:      ");
        lcd.setCursor(2,1);
        lcd.print(a.acceleration.z);

        lcd.setCursor(8,1);
        lcd.print("V:      ");
        lcd.setCursor(10,1);
        lcd.print(pot);
      }
    }
  }

  void writeData(){
    if(started != -1){
      unsigned long startTime = millis();
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      if(!SPIFFS.exists("/dados.csv")){
        File dados = SPIFFS.open("/dados.csv","w");
        dados.println("Time,Number,Pista,AX,AY,AZ");
        dados.close();
      }
      File dados = SPIFFS.open("/dados.csv","a");
      dados.println(String(millis()-startTime) + "," + String(number) + "," + textSelect + "," + String(a.acceleration.x) + "," + String(a.acceleration.y) + "," + String(a.acceleration.z) );
      dados.close();
    }  
  }

  void options(){
    int value = digitalRead((BUTTON_OPTIONS));
    if (value == LOW && selected == -1 ){
      if(option <= 4){
        optionsToText(option);
        option++;
      } else {
        option = 0;
        // optionsToText(option);
      }
    } 
  }

  void select(){
    int value = digitalRead((BUTTON_SELECT));
    if (value == LOW){
      selected = option;
    } 
  }

  void start(){
    int value = digitalRead((BUTTON_START));
    if (value == LOW && selected != -1){
      started = option;
      lcd.clear();
    } 
  }

  void reset(){
    int value = digitalRead((BUTTON_RESET));
    if (value == LOW){
      selected = -1;
      started = -1; 
      number++;
      lcd.clear();
    } 
  }

};


Display display;

void setup() {
  // Init
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  pinMode(BUTTON_OPTIONS, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(POT, INPUT);


  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      delay(10);
  }
  Serial.println("Found a MPU-6050 sensor");

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  SPIFFS.begin(true);
  LittleFS.begin(true,"/littlefs", 10, "spiffs");

}


void loop() {
    display.text();
    display.options();
    display.start();
    display.select();
    display.reset();
    // display.writeData();
}

