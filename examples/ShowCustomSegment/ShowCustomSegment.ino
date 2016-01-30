#include <AM50288H.h>

const int lePin = 11;
const int dinPin = 9;
const int sckPin = 12;

AM50288H lcd(lePin, dinPin, sckPin);

// AM50288H-SLY-DJKの購入時に付属している簡易資料に記載されている
// "ビット位置と表示セグメントの関係"を参考にして、各セグメントの表示/非表示を
// アルファベット順に配列で定義する(A, B, C, D, E, F, G1, G2, J, K, L, M, N, P)。
// 簡易資料: http://www.kyohritsu.jp/eclib/DIGIT/JNK/am50288hsly.pdf

// 数字 1
const byte segment1[14] = {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 数字 2
const byte segment2[14] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0};

// 数字 3
const byte segment3[14] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0};

// 数字 4
const byte segment4[14] = {0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0};

// 数字 5
const byte segment5[14] = {1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0};

// 数字 6
const byte segment6[14] = {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

// 数字 7
const byte segment7[14] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 数字 8
const byte segment8[14] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  lcd.begin();

  // すべて消灯する
  lcd.clear();
  lcd.refresh();
  delay(1000);
}

void loop() {
  // 1桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(0, segment1);

  // 2桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(1, segment2);

  // 3桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(2, segment3);

  // 4桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(3, segment4);

  // 5桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(4, segment5);

  // 6桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(5, segment6);

  // 7桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(6, segment7);

  // 8桁目の14セグメントの表示内容を設定
  lcd.setSegmentBits(7, segment8);

  // 設定した表示内容をLCDに反映
  lcd.refresh();

  delay(3000);
}

