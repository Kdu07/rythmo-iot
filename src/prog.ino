#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
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

// Estado do esp
unsigned short state = 0; // 0 - Desligado; 1 - Seleção de Pista; 2 - Procurando redes; 3 - Seleção de WiFi; 4 - Conectando a rede; 5 - Medição em Andamento


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
  unsigned long startTime = 0;
  int lastDisplayedState = -1; // Track last displayed state to prevent unnecessary clears

  // Debounce para os botões
  unsigned long lastDebounceTime = 0;
  unsigned long debounceDelay = 300;
  
  // Variaveis de WiFi
  static const int MAX_NETWORKS = 5;
  String availableNetworks[MAX_NETWORKS];
  int networkCount = 0;
  int currentNetworkIndex = 0;

  // Timing para mensagens
  unsigned long messageStartTime = 0;
  int messageState = 0; // 0 = no message, 1 = showing message

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
      if(lastState != option || lastDisplayedState != 1){
        lastState = option;
        lastDisplayedState = 1;
        lcd.clear();
        Serial.println("ESTADO 1: Menu de Selecao");
        lcd.setCursor(0,0);
        lcd.print(textOption);
        lcd.setCursor(0,1);
        lcd.print(textSelect);
      }
    } 
    // ESTADO 2: Algo foi selecionado MAS ainda não foi iniciado
    else if (selected != -1 && started == -1){
       if(state == 1) {  
        if(lastDisplayedState != 2) {
          lastDisplayedState = 2;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(textSelected);
          lcd.setCursor(0,1);
          lcd.print(textSelect);
        }
      } else if(state == 2) {
        if(lastDisplayedState != 3) {
          lastDisplayedState = 3;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Procurando");
          lcd.setCursor(0,1);
          lcd.print("redes...");
        }
      } else if(state == 3) {
        if(lastDisplayedState != 4) {
          lastDisplayedState = 4;
          lcd.clear();
          if(networkCount == 0) {
            lcd.setCursor(0, 0);
            lcd.print("Nenhuma rede");
            lcd.setCursor(0, 1);
            lcd.print("encontrada...");
          } else {
            lcd.setCursor(0,0);
            lcd.print("Rede WiFi ["+String(currentNetworkIndex+1)+"]");
            lcd.setCursor(0,1);
            lcd.print(availableNetworks[currentNetworkIndex]);
          }
        }
      }
    } 
    // ESTADO 3: Foi iniciado (mostra sensores)
    else if (started != -1){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      int piezo = analogRead(PIEZO);
      if(delayMillis(500)){ //TAXA DE ATUALIZAÇÃO DO DISPLAY LCD
        if(lastDisplayedState != 5) {
          lastDisplayedState = 5;
          lcd.clear();
        }
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

  void scanWiFiNetworks() {
    Serial.println("Procurando redes WiFi...");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Procurando");
    lcd.setCursor(0,1);
    lcd.print("redes...");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    
    int n = WiFi.scanNetworks();
    Serial.print("Scan completo. Encontradas ");
    Serial.print(n);
    Serial.println(" redes");
    
    networkCount = 0;

    // Filtro para redes sem senha
    for (int i = 0; i < n && networkCount < MAX_NETWORKS; i++) {
      if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
        availableNetworks[networkCount] = WiFi.SSID(i);
        Serial.print("Rede aberta encontrada: ");
        Serial.println(availableNetworks[networkCount]);
        networkCount++;
      }
    }
    
    WiFi.scanDelete();
    
    Serial.print("Redes abertas encontradas: ");
    Serial.println(networkCount);
    
    state = 3;
    lastDisplayedState = -1; // Force LCD update
  }

  void connectToWiFi() {
    if(currentNetworkIndex >= networkCount) {
      Serial.println("Índice de rede inválido");
      return;
    }
    
    String ssid = availableNetworks[currentNetworkIndex];
    
    Serial.print("Conectando à rede: ");
    Serial.println(ssid);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Conectando...");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
    
    WiFi.begin(ssid.c_str());
    
    unsigned long connectStartTime = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - connectStartTime) < 10000) {
      // Wait without blocking
      if((millis() - connectStartTime) % 500 == 0) {
        Serial.print(".");
      }
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConectado com sucesso!");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Conectado!");
      lcd.setCursor(0, 1);
      lcd.print(WiFi.localIP());
      
      messageStartTime = millis();
      messageState = 1;
      state = 4;
    } else {
      Serial.println("\nFalha ao conectar!");
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Falha conexao");
      lcd.setCursor(0, 1);
      lcd.print("Tentar novamente");
      
      messageStartTime = millis();
      messageState = 2;
    }
    lastDisplayedState = -1; // Force LCD update on next state
  }

  // Botão de opções
  void options(){
    int value = digitalRead((BUTTON_OPTIONS));
    if (value == LOW && (millis() - lastDebounceTime) > debounceDelay){
      lastDebounceTime = millis();
      if(state == 1 && selected == -1) {
        if(option < 4){
          option++;
          optionsToText(option);
        } else {
          option = 0;
          optionsToText(option);
        }
        Serial.print("Options - option: ");
        Serial.println(option);
      } else if(state == 2) {
        Serial.println("Estado 2 - Options");
      }
    }
  }

  // Botão de seleção
  void select(){
    int value = digitalRead((BUTTON_SELECT));
    if (value == LOW && (millis() - lastDebounceTime) > debounceDelay){
      lastDebounceTime = millis();
      if(state == 1) {
        selected = option;
        aux = 0;
        Serial.print("Select - selected: ");
        Serial.print(selected);
        Serial.print(" started: ");
        Serial.println(started);
      } else if(state == 2) {
        Serial.println(selected);
        Serial.println("Estado 2 - Select");
      }
    }
  }

  // Botoão de start
  void start(){
    int value = digitalRead((BUTTON_START));
    if (value == LOW && (millis() - lastDebounceTime) > debounceDelay){
        lastDebounceTime = millis();
        
        // Muda o estado para seleção de WiFi
        if(state == 1 && selected != -1) {
          Serial.println("Mudando para estado 2");
          state = 2;
          lastDisplayedState = -1;
          scanWiFiNetworks();
          return;
        }

        // Se o estado não for do WiFi, não faz nada
        if(state != 3) {  
          return;
        }

        connectToWiFi();

        started = option;
        if(aux == 0){
          startTime = millis();
          aux++;
        }
        Serial.print("Start - started: ");
        Serial.println(started);
        Serial.print("Iniciando medição número: ");
        Serial.println(number);
        state = 4;
        lastDisplayedState = -1;
    }
  }


  // Botão de reset
  void reset(){
    int value = digitalRead((BUTTON_RESET));
    if (value == LOW){
      // Reseta a pista
      if(state == 1) {
        if(started != -1){
          Serial.print("Finalizando medição número: ");
          Serial.println(number);
          number++;
        }
        selected = -1;
        started = -1; 
        aux = 0;
        option = 0;
        optionsToText(option);
        lastDisplayedState = -1;
        lcd.clear();
        Serial.println("Reset - voltando ao menu");
      // Reseta a Rede WiFi
      } else if(state == 2) {
        Serial.println("Estado 2 - Reset");
      }
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
      ;
  }
  Serial.println("Sensor MPU6050 encontrado!");

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Inicializa o cartão SD
  Serial.println("Inicializando SPI para SD Card...");
  SPI.begin();
  
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
    unsigned long errorMsgStart = millis();
    while(millis() - errorMsgStart < 3000) {
      // Wait without blocking
    }
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
    unsigned long sdMsgStart = millis();
    while(millis() - sdMsgStart < 2000) {
      // Wait without blocking
    }
    lcd.clear();
  }

  state = 1;
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

