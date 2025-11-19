#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <math.h> // sqrt se precisar (opcional)

// === Configurações de hardware ===
#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_LINES 2

// Botões (INPUT_PULLUP)
#define BUTTON_OPTIONS 14
#define BUTTON_SELECT 17
#define BUTTON_RESET 12
#define BUTTON_START 16

#define PIEZO_PIN 34 // ADC1_CH6 (por exemplo)
#define LED_RED 2
#define LED_GREEN 15

// SD
#define SD_CS_PIN 5 // Chip select do SD (ajustar conforme seu wiring)
const char *DATA_FILENAME = "/dados.csv";

// MPU6050 I2C
const int MPU_ADDR = 0x68; // endereço padrão do MPU6050

// === Objetos ===
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

// Estado SD global
bool sdCardOK = false;

// ====== Funções MPU6050 (implementação fornecida) ======
bool initMPU()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1
  Wire.write(0);    // Acorda o MPU6050
  return (Wire.endTransmission() == 0);
}

bool readMPU(int16_t &ax_raw, int16_t &ay_raw, int16_t &az_raw)
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Registrador ACCEL_XOUT_H
  if (Wire.endTransmission(false) != 0)
    return false;
  if (Wire.requestFrom(MPU_ADDR, 6, true) != 6)
    return false;
  ax_raw = Wire.read() << 8 | Wire.read();
  ay_raw = Wire.read() << 8 | Wire.read();
  az_raw = Wire.read() << 8 | Wire.read();
  return true;
}

// ====== Classe para UI / controle ======
class UIManager
{
public:
  UIManager() {}

  void begin()
  {
    option = 0;
    selected = -1;
    started = -1;
    number = 1;
    lastLCDUpdate = 0;
    lcdUpdateInterval = 500;
    ledBlinkInterval = 550;
    lastLedMillis = 0;
    lastSaveMillis = 0;
    startTime = 0;
    // carregar texto inicial
    updateOptionText();
  }

  // Chamado no loop
  void update()
  {
    readButtons();
    updateLEDs();
    updateLCD();
    writeDataIfNeeded();
  }

  // Exposição para setar SD OK após setup
  void setSdOk(bool v) { sdCardOK_global = v; }

private:
  // Estado
  int option = 0;
  int selected = -1;
  int started = -1;
  int number = 1;
  int aux = 0;

  // Texto da opção atual
  String optionText = "Lisa";
  static const int NUM_OPTIONS = 5;

  // Timing
  unsigned long lastLCDUpdate = 0;
  unsigned long lcdUpdateInterval = 500;
  unsigned long lastLedMillis = 0;
  unsigned long ledBlinkInterval = 550;
  unsigned long startTime = 0;
  unsigned long lastSaveMillis = 0;
  const unsigned long saveInterval = 200; // grava a cada 200 ms (ajustável)

  // Debounce por botão
  const unsigned long debounceDelay = 250; // ms
  unsigned long lastOptionDebounce = 0;
  unsigned long lastSelectDebounce = 0;
  unsigned long lastStartDebounce = 0;
  unsigned long lastResetDebounce = 0;

  // sd flag (usado pela classe)
  bool sdCardOK_global = false;

  // rastreamento para limpar lcd quando mudanca de estado
  int lastState = -99;

  // ----- Botões e debounce -----
  void readButtons()
  {
    // options
    if (buttonPressed(BUTTON_OPTIONS, &lastOptionDebounce))
    {
      option = (option + 1) % NUM_OPTIONS;
      updateOptionText();
      Serial.print("Options -> option: ");
      Serial.println(option);
    }
    // select
    if (buttonPressed(BUTTON_SELECT, &lastSelectDebounce))
    {
      if (selected == -1)
      {
        selected = option;
        Serial.print("Select -> selected: ");
        Serial.println(selected);
      }
    }
    // start
    if (buttonPressed(BUTTON_START, &lastStartDebounce))
    {
      if (selected != -1 && started == -1)
      {
        started = selected;
        startTime = millis();
        aux = 1;
        Serial.print("Start -> started: ");
        Serial.println(started);
        Serial.print("Iniciando medicao numero: ");
        Serial.println(number);
      }
    }
    // reset
    if (buttonPressed(BUTTON_RESET, &lastResetDebounce, false))
    { // sem debounce extra (pode ser instantâneo)
      if (started != -1)
      {
        Serial.print("Finalizando medicao numero: ");
        Serial.println(number);
        number++;
      }
      // reset estado
      selected = -1;
      started = -1;
      aux = 0;
      option = 0;
      updateOptionText();
      lcd.clear();
      Serial.println("Reset -> voltando ao menu");
    }
  }

  // Retorna true se botão (INPUT_PULLUP) foi lido como pressionado (LOW) e passou debounce
  bool buttonPressed(uint8_t pin, unsigned long *lastDebounceVar, bool useDebounce = true)
  {
    int val = digitalRead(pin);
    unsigned long now = millis();
    if (val == LOW)
    {
      if (!useDebounce)
        return true;
      if (now - *lastDebounceVar > debounceDelay)
      {
        *lastDebounceVar = now;
        return true;
      }
    }
    return false;
  }

  // ----- LCD -----
  void updateLCD()
  {
    unsigned long now = millis();
    if (selected == -1)
    {
      // menu de seleção
      if (lastState != option)
      {
        lastState = option;
        lcd.clear();
      }
      if (now - lastLCDUpdate >= lcdUpdateInterval)
      {
        lastLCDUpdate = now;
        lcd.setCursor(0, 0);
        lcd.print("Select Pista:    ");
        lcd.setCursor(0, 1);
        lcd.print(optionText + "        ");
      }
    }
    else if (selected != -1 && started == -1)
    {
      // selecionado mas não iniciado
      if (now - lastLCDUpdate >= 1000)
      {
        lastLCDUpdate = now;
        lcd.setCursor(0, 0);
        lcd.print("Selected Pista:  ");
        lcd.setCursor(0, 1);
        lcd.print(optionText + "        ");
      }
    }
    else if (started != -1)
    {
      // em execução: mostra sensores
      if (now - lastLCDUpdate >= lcdUpdateInterval)
      {
        lastLCDUpdate = now;
        int16_t rx, ry, rz;
        bool ok = readMPU(rx, ry, rz);
        float ax = 0, ay = 0, az = 0;
        if (ok)
        {
          ax = rx / 16384.0;
          ay = ry / 16384.0;
          az = rz / 16384.0;
        }
        else
        {
          // Em caso de falha, mostrar zeros e tentar re-inicializar
          Serial.println("Falha leitura MPU no updateLCD");
          initMPU();
        }
        int piezo = analogRead(PIEZO_PIN);

        lcd.setCursor(0, 0);
        lcd.print("X:");
        printAlignedFloat(ax, 2, 6);
        lcd.setCursor(8, 0);
        lcd.print("Y:");
        printAlignedFloat(ay, 2, 6);

        lcd.setCursor(0, 1);
        lcd.print("Z:");
        printAlignedFloat(az, 2, 6);
        lcd.setCursor(8, 1);
        lcd.print("V:");
        lcd.print(piezo);
        lcd.print("   ");
      }
    }
  }

  // Imprime float com precisão e posição coerente
  void printAlignedFloat(float v, int decimals, int width)
  {
    String s = String(v, decimals);
    // ajusta para ter pelo menos width caracteres
    while ((int)s.length() < width)
      s = " " + s;
    lcd.print(s);
  }

  // ----- LEDs -----
  void updateLEDs()
  {
    unsigned long now = millis();
    // piscando LED_RED enquanto não iniciado
    if (started == -1)
    {
      if (now - lastLedMillis >= ledBlinkInterval)
      {
        lastLedMillis = now;
        digitalWrite(LED_RED, !digitalRead(LED_RED));
      }
    }
    else
    {
      digitalWrite(LED_RED, LOW);
    }
    // LED verde ligado quando started
    digitalWrite(LED_GREEN, (started != -1) ? HIGH : LOW);
  }

  // ----- SD / gravação -----
  void writeDataIfNeeded()
  {
    // grava em intervalos (para não gravar cada loop)
    if (started == -1 || !sdCardOK_global)
      return;

    unsigned long now = millis();
    if (now - lastSaveMillis < saveInterval)
      return; // aguarda próximo intervalo
    lastSaveMillis = now;

    int16_t rx, ry, rz;
    bool ok = readMPU(rx, ry, rz);
    float ax = 0, ay = 0, az = 0;
    if (ok)
    {
      ax = rx / 16384.0;
      ay = ry / 16384.0;
      az = rz / 16384.0;
    }
    else
    {
      Serial.println("Falha leitura MPU no writeDataIfNeeded");
      // tenta re-inicializar mas continua (não interrompe gravação do SD)
      initMPU();
    }

    int piezo = analogRead(PIEZO_PIN);

    // cria arquivo com cabeçalho se não existir
    if (!SD.exists(DATA_FILENAME))
    {
      File f = SD.open(DATA_FILENAME, FILE_WRITE);
      if (f)
      {
        f.println("Time(ms),Number,Pista,AX,AY,AZ,Vibracao");
        f.close();
        Serial.println("Arquivo criado com cabecalho");
      }
      else
      {
        Serial.println("Erro ao criar arquivo (cabecalho)");
        sdCardOK_global = false;
        return;
      }
    }

    File f = SD.open(DATA_FILENAME, FILE_APPEND);
    if (!f)
    {
      Serial.println("Erro ao abrir arquivo para escrita");
      sdCardOK_global = false;
      return;
    }
    unsigned long t = millis() - startTime;
    String line = String(t) + "," + String(number) + "," + optionText + "," +
                  String(ax, 2) + "," + String(ay, 2) + "," +
                  String(az, 2) + "," + String(piezo);
    f.println(line);
    f.close();
  }

  // Atualiza optionText com base em option
  void updateOptionText()
  {
    switch (option)
    {
    case 0:
      optionText = "Lisa";
      break;
    case 1:
      optionText = "Esburacada";
      break;
    case 2:
      optionText = "Paralelepipedo";
      break;
    case 3:
      optionText = "Placeholder";
      break;
    case 4:
      optionText = "Placeholder2";
      break;
    default:
      optionText = "Unknown";
      break;
    }
  }
};

// === Instância ===
UIManager ui;

// ================= Setup / Loop =================
void setup()
{
  Serial.begin(115200);
  delay(200);

  Serial.println("=== Inicializando sistema ===");

  // I2C
  Wire.begin(21, 22); // SDA=21, SCL=22 (padrões ESP32)
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Pinos
  pinMode(BUTTON_OPTIONS, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(PIEZO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // Inicializa MPU (usando sua implementação)
  Serial.println("Inicializando MPU6050...");
  if (!initMPU())
  {
    Serial.println("ERRO: MPU6050 NAO ENCONTRADO. Verifique conexoes I2C.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MPU6050 ERR");
    // Bloqueia para debug (pode ser alterado para continuar sem MPU)
    while (1)
    {
      delay(1000);
    }
  }
  else
  {
    Serial.println("MPU6050 inicializado.");
  }

  // SD (SPI)
  Serial.println("Inicializando SPI e SD...");
  SPI.begin(18, 19, 23, SD_CS_PIN); // SCK,MISO,MOSI,SS
  delay(10);
  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("Falha ao inicializar SD! Verifique conexoes e formatacao (FAT32/FAT16).");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro SD Card");
    lcd.setCursor(0, 1);
    lcd.print("Verificar cartao");
    sdCardOK = false;
    delay(2000);
    lcd.clear();
  }
  else
  {
    sdCardOK = true;
    uint8_t cardType = SD.cardType();
    Serial.print("SD iniciado. Tipo: ");
    if (cardType == CARD_MMC)
      Serial.println("MMC");
    else if (cardType == CARD_SD)
      Serial.println("SDSC");
    else if (cardType == CARD_SDHC)
      Serial.println("SDHC");
    else
      Serial.println("UNKNOWN");
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("Tamanho (MB): %llu\n", cardSize);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SD Card OK!");
    lcd.setCursor(0, 1);
    lcd.print(String(cardSize) + "MB");
    delay(1500);
    lcd.clear();
  }

  // inicializa UI manager
  ui.begin();
  ui.setSdOk(sdCardOK);

  Serial.println("Setup finalizado.");
}

void loop()
{
  ui.update();
  // loop não bloqueante
}
