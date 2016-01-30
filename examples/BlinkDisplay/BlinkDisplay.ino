#include <AM50288H.h>

const int lePin = 11;
const int dinPin = 9;
const int sckPin = 12;

AM50288H lcd(lePin, dinPin, sckPin);

void setup() {
  Serial.begin(9600);
  lcd.begin();

  // すべて消灯する
  lcd.clear();
  lcd.refresh();
  delay(1000);
}

void loop() {
  delay(1000);

  // すべて点灯
  lcd.setAllBit(HIGH);
  lcd.refresh();

  delay(1000);

  // すべて消灯
  lcd.setAllBit(LOW);
  lcd.refresh();
}

