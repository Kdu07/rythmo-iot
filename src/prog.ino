#include <LiquidCrystal_I2C.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
// #include <SPIFFS.h>
// #include <LittleFS.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
#define BUTTON_OPTIONS 5
#define BUTTON_SELECT 17
#define BUTTON_RESET 18
#define BUTTON_START 16
#define PIEZO 34

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);
Adafruit_MMA8451 mma = Adafruit_MMA8451();

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
  int aux = 0;
  
  // Debounce para os botões
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 300; // 300ms de debounce
  

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
    // ESTADO 1: Nada foi selecionado ainda
    if (selected == -1){
      if(lastState != option){
        lastState = option;
        lcd.clear();
        Serial.println("ESTADO 1: Menu de Selecao");
      }
      lcd.setCursor(0,0);
      lcd.print(textOption);
      lcd.setCursor(0,1);
      lcd.print(textSelect);
    } 
    // ESTADO 2: Algo foi selecionado MAS ainda não foi iniciado
    else if (selected != -1 && started == -1){
      if(lastState != option){
        lastState = option;
        lcd.clear();
        Serial.println("ESTADO 2: Pista Selecionada");
      }
      lcd.setCursor(0,0);
      lcd.print(textSelected);
      lcd.setCursor(0,1);
      lcd.print(textSelect);
      delayMillis(1000);
    } 
    // ESTADO 3: Foi iniciado (mostra sensores)
    else if (started != -1){
      sensors_event_t event;
      mma.getEvent(&event);
      int piezo = analogRead(PIEZO);
      if(delayMillis(300)){
        // lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("X:      ");
        lcd.setCursor(2,0);
        lcd.print(event.acceleration.x);

        lcd.setCursor(8,0);
        lcd.print("Y:      ");
        lcd.setCursor(10,0);
        lcd.print(event.acceleration.y);
      
        lcd.setCursor(0,1);
        lcd.print("Z:      ");
        lcd.setCursor(2 ,1);
        lcd.print(event.acceleration.z);

        lcd.setCursor(8,1);
        lcd.print("V:      ");
        lcd.setCursor(10,1);
        lcd.print(piezo);
      }
    }
  }

  // void writeData(){
  //   if(started != -1){
  //     unsigned long startTime = millis();
  //     sensors_event_t event;
  //     mma.getEvent(&event);
  //     if(!SPIFFS.exists("/dados.csv")){
  //       File dados = SPIFFS.open("/dados.csv","w");
  //       dados.println("Time,Number,Pista,AX,AY,AZ");
  //       dados.close();
  //     }
  //     File dados = SPIFFS.open("/dados.csv","a");
  //     dados.println(String(millis()-startTime) + "," + String(number) + "," + textSelect + "," + String(event.acceleration.x) + "," + String(event.acceleration.y) + "," + String(event.acceleration.z) );
  //     dados.close();
  //   }  
  // }

  void options(){
    int value = digitalRead((BUTTON_OPTIONS));
    if (value == LOW && selected == -1 && (millis() - lastDebounceTime) > debounceDelay){
      lastDebounceTime = millis();
      if(option < 4){
        option++;
        optionsToText(option);
      } else {
        option = 0;
        optionsToText(option);
      }
      Serial.print("Options - option: ");
      Serial.println(option);
    } 
  }

  void select(){
    int value = digitalRead((BUTTON_SELECT));
    if (value == LOW && (millis() - lastDebounceTime) > debounceDelay){
      lastDebounceTime = millis();
      selected = option;
      aux = 0;
      Serial.print("Select - selected: ");
      Serial.print(selected);
      Serial.print(" started: ");
      Serial.println(started);
    } 
  }

  void start(){
    int value = digitalRead((BUTTON_START));
    if (value == LOW && (millis() - lastDebounceTime) > debounceDelay && selected != -1 ){
        lastDebounceTime = millis();
        started = option;
        if(aux == 0){
          lcd.clear();
          aux = 1;
        }
        Serial.print("Start - started: ");
        Serial.println(started);
    }
  }

  void reset(){
    int value = digitalRead((BUTTON_RESET));
    if (value == LOW){
      selected = -1;
      started = -1; 
      aux = 0;
      option = 0;
      optionsToText(option);
      number++;
      lcd.clear();
      Serial.println("Reset - voltando ao menu");
    } 
  }

};


Display display;

void setup() {
  // Init
  Serial.begin(9600);
  delay(1000); // Aguarda inicialização da serial
  
  Serial.println("Iniciando sistema...");
  
  // Inicializa I2C com pinos específicos (SDA=21, SCL=22 no ESP32)
  Wire.begin(21, 22);
  
  // Escaneia dispositivos I2C
  Serial.println("Escaneando dispositivos I2C...");
  byte error, address;
  int nDevices = 0;
  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado no endereço 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  if (nDevices == 0) {
    Serial.println("Nenhum dispositivo I2C encontrado!");
  }
  
  // Inicializa LCD
  Serial.println("Inicializando LCD...");
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Teste básico do LCD
  lcd.setCursor(0, 0);
  lcd.print("Teste LCD");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  
  pinMode(BUTTON_OPTIONS, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(PIEZO, INPUT);

  Serial.println("Inicializando MMA8451...");
  // Especifica o endereço I2C correto (0x1C ao invés do padrão 0x1D)
  if (!mma.begin(0x1C)) {
    Serial.println("Sensor init failed");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MMA8451 Erro!");
    while (true)
      delay(10);
  }
  Serial.println("Found a MMA8451 sensor");

  mma.setRange(MMA8451_RANGE_2_G);

  // SPIFFS.begin(true);
  // LittleFS.begin(true,"/littlefs", 10, "spiffs");

}


void loop() {
    display.text();
    display.options();
    display.start();
    display.select();
    display.reset();
    // display.writeData();
}

