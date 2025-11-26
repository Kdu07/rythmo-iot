#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <math.h>

// ================= UBIDOTS / MQTT ======================
#include <WiFi.h>
#include <UbidotsEsp32Mqtt.h>

const char *WIFI_SSID = "Inteli.Iot";
const char *WIFI_PASS = "";

const char *UBIDOTS_TOKEN = "";
const char *DEVICE_LABEL = "esp32_t15_grupo3";

const char *VARIABLE_LABEL1 = "acelerometro-x";
const char *VARIABLE_LABEL2 = "acelerometro-y";
const char *VARIABLE_LABEL3 = "acelerometro-z";
const char *VARIABLE_LABEL4 = "piezoeletrico";

const char *CLIENT_ID = "grupo3";
Ubidots ubidots(UBIDOTS_TOKEN, CLIENT_ID);

// Timer MQTT
unsigned long lastPublish = 0;
const int MQTT_INTERVAL = 1000;

// ===== HARDWARE =====
#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_LINES 2

#define BUTTON_OPTIONS 14
#define BUTTON_SELECT 17
#define BUTTON_RESET 12
#define BUTTON_START 16

#define PIEZO_PIN 34
#define LED_RED 2
#define LED_GREEN 15

#define SD_CS_PIN 5
const char *DATA_FILENAME = "/dados.csv";

const int MPU_ADDR = 0x68;

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

bool sdCardOK = false;

// =============================================================================
// MPU FUNCTIONS
// =============================================================================
bool initMPU()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  return (Wire.endTransmission() == 0);
}

bool readMPU(int16_t &ax_raw, int16_t &ay_raw, int16_t &az_raw)
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0)
    return false;
  if (Wire.requestFrom(MPU_ADDR, 6, true) != 6)
    return false;
  ax_raw = Wire.read() << 8 | Wire.read();
  ay_raw = Wire.read() << 8 | Wire.read();
  az_raw = Wire.read() << 8 | Wire.read();
  return true;
}

// =============================================================================
// MQTT CALLBACK
// =============================================================================
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensagem MQTT: ");
  for (int i = 0; i < length; i++)
    Serial.print((char)payload[i]);
  Serial.println();
}

// =============================================================================
// FUNÇÃO DE ENVIO PARA UBIDOTS (CHAMADA SOMENTE DURANTE A MEDIÇÃO)
// =============================================================================
void sendToUbidots(float ax, float ay, float az, float piezo)
{
  if (!ubidots.connected())
    ubidots.reconnect();

  if (millis() - lastPublish < MQTT_INTERVAL)
    return;

  ubidots.add(VARIABLE_LABEL1, ax);
  ubidots.add(VARIABLE_LABEL2, ay);
  ubidots.add(VARIABLE_LABEL3, az);
  ubidots.add(VARIABLE_LABEL4, piezo);

  ubidots.publish(DEVICE_LABEL);
  lastPublish = millis();

  Serial.println("Dados enviados ao Ubidots!");
}

// =============================================================================
// UI MANAGER
// =============================================================================
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
    lastLedMillis = 0;
    lastSaveMillis = 0;

    updateOptionText();
  }

  void setSdOk(bool v) { sdCardOK_global = v; }

  void update()
  {
    readButtons();
    updateLEDs();
    updateLCD();
    writeDataIfNeeded();
  }

private:
  int option = 0;
  int selected = -1;
  int started = -1;
  int number = 1;

  String optionText = "Lisa";
  static const int NUM_OPTIONS = 5;

  unsigned long lastLCDUpdate;
  unsigned long lcdUpdateInterval;

  unsigned long lastLedMillis;
  unsigned long ledBlinkInterval = 550;

  unsigned long startTime = 0;
  unsigned long lastSaveMillis;
  const unsigned long saveInterval = 200;

  bool sdCardOK_global = false;

  int lastState = -99;

  // ---------------------------------------------------------------
  // BOTÕES
  // ---------------------------------------------------------------
  void readButtons()
  {
    if (buttonPressed(BUTTON_OPTIONS))
    {
      option = (option + 1) % NUM_OPTIONS;
      updateOptionText();
    }

    if (buttonPressed(BUTTON_SELECT))
    {
      if (selected == -1)
        selected = option;
    }

    if (buttonPressed(BUTTON_START))
    {
      if (selected != -1 && started == -1)
      {
        lcd.clear();
        started = selected;
        startTime = millis();
        Serial.println(">>> MEDIÇÃO INICIADA <<<");
      }
    }

    if (buttonPressed(BUTTON_RESET, false))
    {
      if (started != -1)
        number++;

      selected = -1;
      started = -1;
      option = 0;

      updateOptionText();
      lcd.clear();
    }
  }

  bool buttonPressed(uint8_t pin, bool debounce = true)
  {
    static unsigned long lastDebounce = 0;
    const unsigned long debounceDelay = 250;

    int val = digitalRead(pin);
    unsigned long now = millis();

    if (val == LOW)
    {
      if (!debounce || (now - lastDebounce > debounceDelay))
      {
        lastDebounce = now;
        return true;
      }
    }
    return false;
  }

  // ---------------------------------------------------------------
  // LCD
  // ---------------------------------------------------------------
  void updateLCD()
  {
    unsigned long now = millis();

    if (selected == -1)
    {
      if (lastState != option)
      {
        lastState = option;
        lastDisplayedState = 1;
        lcd.clear();
      }

      if (now - lastLCDUpdate > lcdUpdateInterval)
      {
        lcd.clear();
        lastLCDUpdate = now;
        lcd.setCursor(0, 0);
        lcd.print("Select Pista:");
        lcd.setCursor(0, 1);
        lcd.print(optionText + "    ");
      }
    }
    else if (started == -1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Selected Pista:");
      lcd.setCursor(0, 1);
      lcd.print(optionText + "    ");
    }
    else
    {
      if (now - lastLCDUpdate > lcdUpdateInterval)
      {

        lastLCDUpdate = now;

        int16_t rx, ry, rz;
        readMPU(rx, ry, rz);

        float ax = rx / 16384.0;
        float ay = ry / 16384.0;
        float az = rz / 16384.0;

        int piezo = analogRead(PIEZO_PIN);

        lcd.setCursor(0, 0);
        lcd.print("X:");
        lcd.print(ax, 2);
        lcd.setCursor(8, 0);
        lcd.print("Y:");
        lcd.print(ay, 2);

        lcd.setCursor(0, 1);
        lcd.print("Z:");
        lcd.print(az, 2);
        lcd.setCursor(8, 1);
        lcd.print("V:");
        lcd.print(piezo);

        sendToUbidots(ax, ay, az, piezo);
      }
    }
  }

  // ---------------------------------------------------------------
  // LED
  // ---------------------------------------------------------------
  void updateLEDs()
  {
    if (started == -1)
    {
      if (millis() - lastLedMillis > ledBlinkInterval)
      {
        lastLedMillis = millis();
        digitalWrite(LED_RED, !digitalRead(LED_RED));
      }
    }
    else
    {
      digitalWrite(LED_RED, LOW);
    }

    digitalWrite(LED_GREEN, started != -1 ? HIGH : LOW);
  }

  // ---------------------------------------------------------------
  // SD
  // ---------------------------------------------------------------
  void writeDataIfNeeded()
  {
    if (started == -1 || !sdCardOK_global)
      return;

    if (millis() - lastSaveMillis < saveInterval)
      return;

    lastSaveMillis = millis();

    int16_t rx, ry, rz;
    readMPU(rx, ry, rz);

    float ax = rx / 16384.0;
    float ay = ry / 16384.0;
    float az = rz / 16384.0;
    int piezo = analogRead(PIEZO_PIN);

    // ====== SALVA NO SD ======
    if (!SD.exists(DATA_FILENAME))
    {
      File f = SD.open(DATA_FILENAME, FILE_WRITE);
      f.println("Time,Number,Pista,AX,AY,AZ,PIEZO");
      f.close();
    }

    File f = SD.open(DATA_FILENAME, FILE_APPEND);
    unsigned long t = millis() - startTime;

    f.printf("%lu,%d,%s,%.2f,%.2f,%.2f,%d\n",
             t, number, optionText.c_str(), ax, ay, az, piezo);

    f.close();
  }

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
    }
  }
};

UIManager ui;

// =============================================================================
// SETUP
// =============================================================================
void setup()
{
  Serial.begin(115200);
  delay(200);

  // LCD + I2C
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  // Botões / LEDs
  pinMode(BUTTON_OPTIONS, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(PIEZO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // MPU
  if (!initMPU())
  {
    lcd.print("MPU ERROR");
    while (true)
      ;
  }

  // SD
  SPI.begin(18, 19, 23, SD_CS_PIN);
  sdCardOK = SD.begin(SD_CS_PIN);

  // UBIDOTS MQTT
  ubidots.setDebug(true);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  ui.begin();
  ui.setSdOk(sdCardOK);
}

// =============================================================================
// LOOP
// =============================================================================
void loop()
{
  ubidots.loop();
  ui.update();
}
