#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
#define BUTTON_OPTIONS 5
#define BUTTON_SELECT 17
#define BUTTON_RESET 18

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

class Display{
  private:
  int option = 0;
  int selected = -1;
  const String textOption = "Select Pista:";
  String textSelect = "Lisa";
  int lastState = 0;
  const String textSelected ="Selected Pista:";

  public:

  bool alreadySelected(){
    if (selected != -1){
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
        textSelect = "Molestada";
      return textSelect;
      case 4:
        textSelect = "Molestada2.0";
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
    } else {
      if(lastState != option){
        lastState = option;
        lcd.clear();
      }
      lcd.setCursor(0,0);
      lcd.print(textSelected);
      lcd.setCursor(0,1);
      lcd.print(textSelect);
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

  void reset(){
    int value = digitalRead((BUTTON_RESET));
    if (value == LOW){
      selected = -1;
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
  // // Print something
  // lcd.setCursor(3, 0);
  // lcd.print("Hello, world!");
  // lcd.setCursor(2, 1);
  // lcd.print("Wokwi Online");


}


void loop() {
    display.text();
    display.options();
    display.select();
    display.reset();
}

