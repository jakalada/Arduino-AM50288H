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
  // 各マークを順に表示する

  // バッテリーを表示
  lcd.setMarkBit(MARK_BATTERY, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_BATTERY, LOW);

  // スピーカーを表示
  lcd.setMarkBit(MARK_SPEAKER, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_SPEAKER, LOW);

  // アンテナを表示
  lcd.setMarkBit(MARK_ANNTENA, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_ANNTENA, LOW);

  // 音符を表示
  lcd.setMarkBit(MARK_NOTE, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_NOTE, LOW);

  // 四角形を表示
  lcd.setMarkBit(MARK_SQUARE, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_SQUARE, LOW);

  // サイクルを表示
  lcd.setMarkBit(MARK_CYCLE, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_CYCLE, LOW);

  // ダイヤを表示
  lcd.setMarkBit(MARK_DIAMOND, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_DIAMOND, LOW);

  // ベルを表示
  lcd.setMarkBit(MARK_BELL, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_BELL, LOW);

  // アスタリスクを表示
  lcd.setMarkBit(MARK_ASTERISK, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_ASTERISK, LOW);

  // >を表示
  lcd.setMarkBit(MARK_NEXT, HIGH);
  lcd.refresh();
  delay(1000);
  lcd.setMarkBit(MARK_NEXT, LOW);

  lcd.clear();
  lcd.refresh();
  delay(1000);
}

