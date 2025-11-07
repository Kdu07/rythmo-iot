#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>

#define I2C_ADDR    0x27
#define SENSOR_ADDR 0x1C
#define LCD_COLUMNS 16
#define LCD_LINES   2
#define BUTTON_OPTIONS 14
#define BUTTON_SELECT 17
#define BUTTON_RESET 12
#define BUTTON_START 16
#define PIEZO 34
#define LED_RED 2
#define LED_GREEN 15
#define SD_CS 5  // Chip Select do SD Card

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);
Adafruit_MPU6050 mpu;
bool sdCardOK = false; // Flag para verificar se o SD Card está funcionando

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
  unsigned long startTime = 0; // Tempo de início da medição
  
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

  bool delayMillis2(int interval) {
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
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      int piezo = analogRead(PIEZO);
      if(delayMillis(500)){ //TAXA DE ATUALIZAÇÃO DO DISPLAY LCD
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
        lcd.setCursor(2 ,1);
        lcd.print(a.acceleration.z);

        lcd.setCursor(8,1);
        lcd.print("V:      ");
        lcd.setCursor(10,1);
        lcd.print(piezo);
      }
    }
  }

  void writeData(){
    if(started != -1 && sdCardOK){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      int piezo = analogRead(PIEZO);
      
      // Cria o arquivo com cabeçalho se não existir
      if(!SD.exists("dados.csv")){
        File dados = SD.open("dados.csv", FILE_WRITE);
        if(dados){
          dados.println("Time(ms),Number,Pista,AX,AY,AZ,Vibracao");
          dados.close();
          Serial.println("Arquivo dados.csv criado com cabeçalho");
        } else {
          Serial.println("Erro ao criar arquivo dados.csv");
          sdCardOK = false; // Marca SD como não OK
          return;
        }
      }
      
      // Abre arquivo para adicionar dados
      File dados = SD.open("dados.csv", FILE_APPEND);
      if(dados){
        unsigned long currentTime = millis() - startTime;
        String linha = String(currentTime) + "," + 
                      String(number) + "," + 
                      textSelect + "," + 
                      String(a.acceleration.x, 2) + "," + 
                      String(a.acceleration.y, 2) + "," + 
                      String(a.acceleration.z, 2) + "," + 
                      String(piezo);
        dados.println(linha);
        dados.close();
      } else {
        Serial.println("Erro ao abrir arquivo para escrita");
        sdCardOK = false; // Marca SD como não OK
      }
    }  
  }

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
          startTime = millis(); // Inicia o cronômetro da medição
        }
        Serial.print("Start - started: ");
        Serial.println(started);
        Serial.print("Iniciando medição número: ");
        Serial.println(number);
    }
  }

  void reset(){
    int value = digitalRead((BUTTON_RESET));
    if (value == LOW){
      if(started != -1){
        Serial.print("Finalizando medição número: ");
        Serial.println(number);
        number++; // Incrementa apenas quando uma medição é finalizada
      }
      selected = -1;
      started = -1; 
      aux = 0;
      option = 0;
      optionsToText(option);
      lcd.clear();
      Serial.println("Reset - voltando ao menu");
    } 
  }

  void led(){
    if (delayMillis2(550) && started == -1){
      digitalWrite(LED_RED, HIGH);
    } else {
      digitalWrite(LED_RED, LOW);
    }
  }

  void ledStarted(){
    if (started != -1){
      digitalWrite(LED_GREEN, HIGH);
    } else {
      digitalWrite(LED_GREEN, LOW);
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
  
  
  pinMode(BUTTON_OPTIONS, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(PIEZO, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  Serial.println("Inicializando MPU6050...");
  // Inicializa o acelerômetro no endereço 0x1C
  if (mpu.begin() == false) {
    Serial.println("Sensor init failed");
    Serial.println("Verifique as conexões I2C!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MPU6050");
    while (false)
      delay(10);
  }
  Serial.println("Sensor MPU6050 encontrado!");

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Inicializa o cartão SD
  Serial.println("Inicializando SPI para SD Card...");
  SPI.begin(); // Inicializa o barramento SPI
  delay(100);
  
  Serial.println("Inicializando cartão SD...");
  Serial.print("Pino CS: ");
  Serial.println(SD_CS);
  
  if (!SD.begin(SD_CS)) {
    Serial.println("Falha ao inicializar o cartão SD!");
    Serial.println("Possíveis causas:");
    Serial.println("1. Cartão não inserido");
    Serial.println("2. Cartão corrompido ou não formatado (FAT16/FAT32)");
    Serial.println("3. Conexões incorretas");
    Serial.println("4. Pino CS incorreto");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro SD Card");
    lcd.setCursor(0, 1);
    lcd.print("Verificar cartao");
    sdCardOK = false;
    delay(3000);
    lcd.clear();
  } else {
    Serial.println("Cartão SD inicializado com sucesso!");
    uint8_t cardType = SD.cardType();
    Serial.print("Tipo do cartão: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("Tamanho do cartão: %lluMB\n", cardSize);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SD Card OK!");
    lcd.setCursor(0, 1);
    lcd.print(String(cardSize) + "MB");
    sdCardOK = true;
    delay(2000);
    lcd.clear();
  }

}


void loop() {
  display.led();
  display.ledStarted();
  display.text();
  display.options();
  display.start();
  display.select();
  display.reset();
  display.writeData(); // Grava dados no SD Card quando started != -1
}

