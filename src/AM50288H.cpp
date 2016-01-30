#include "Arduino.h"

#include "AM50288H.h"

// 142ビットの表示データでON/OFFが切り替えられる要素とビット位置を対応付けた定数
// 参考: http://www.kyohritsu.jp/eclib/DIGIT/JNK/am50288hsly.pdf
#define BIT_1J        0000
#define BIT_1G2       0001
#define BIT_1P        0002
#define BIT_1N        0003
#define BIT_1M        0004
#define BIT_1L        0005
#define BIT_1K        0006
#define BIT_2J        0007
#define BIT_2G2       0010
#define BIT_2P        0011
#define BIT_2N        0012
#define BIT_2M        0013
#define BIT_2L        0014
#define BIT_2K        0015
#define BIT_3J        0016
#define BIT_3G2       0017
#define BIT_3P        0020
#define BIT_3N        0021
#define BIT_3M        0022
#define BIT_3L        0023
#define BIT_3K        0024
#define BIT_4J        0025
#define BIT_4G2       0026
#define BIT_4P        0027
#define BIT_4N        0030
#define BIT_4M        0031
#define BIT_4L        0032
#define BIT_4K        0033
#define BIT_5J        0034
#define BIT_5G2       0035
#define BIT_5P        0036
#define BIT_5N        0037
#define BIT_5M        0040
#define BIT_5L        0041
#define BIT_5K        0042
#define BIT_6J        0043
#define BIT_6G2       0044
#define BIT_6P        0045
#define BIT_6N        0046
#define BIT_6M        0047
#define BIT_6L        0050
#define BIT_6K        0051
#define BIT_7J        0052
#define BIT_7G2       0053
#define BIT_7P        0054
#define BIT_7N        0055
#define BIT_7M        0056
#define BIT_7L        0057
#define BIT_7K        0060
#define BIT_8J        0061
#define BIT_8G2       0062
#define BIT_8P        0063
#define BIT_8N        0064
#define BIT_8M        0065
#define BIT_8L        0066
#define BIT_8K        0067
// 0070は未使用
#define BIT_ASTERISK  0071
#define BIT_DIAMOND   0072
#define BIT_SQUARE    0073
#define BIT_ANNTENA   0074
#define BIT_BATTERY   0075
// 0076は未使用
// 0077は未使用
// 0100は未使用
// 0101は未使用
// 0102は未使用
// 0103は未使用
// 0104は未使用
// 0105は未使用
// 0106は未使用
// 0107は未使用
// 0110は未使用
// 0111は未使用
// 0112は未使用
// 0113は未使用
// 0114は未使用
// 0115は未使用
// 0116は未使用
// 0117は未使用
#define BIT_1F        0120
#define BIT_1G1       0121
#define BIT_1E        0122
#define BIT_1D        0123
#define BIT_1C        0124
#define BIT_1B        0125
#define BIT_1A        0126
#define BIT_2F        0127
#define BIT_2G1       0130
#define BIT_2E        0131
#define BIT_2D        0132
#define BIT_2C        0133
#define BIT_2B        0134
#define BIT_2A        0135
#define BIT_3F        0136
#define BIT_3G1       0137
#define BIT_3E        0140
#define BIT_3D        0141
#define BIT_3C        0142
#define BIT_3B        0143
#define BIT_3A        0144
#define BIT_4F        0145
#define BIT_4G1       0146
#define BIT_4E        0147
#define BIT_4D        0150
#define BIT_4C        0151
#define BIT_4B        0152
#define BIT_4A        0153
#define BIT_5F        0154
#define BIT_5G1       0155
#define BIT_5E        0156
#define BIT_5D        0157
#define BIT_5C        0160
#define BIT_5B        0161
#define BIT_5A        0162
#define BIT_6F        0163
#define BIT_6G1       0164
#define BIT_6E        0165
#define BIT_6D        0166
#define BIT_6C        0167
#define BIT_6B        0170
#define BIT_6A        0171
#define BIT_7F        0172
#define BIT_7G1       0173
#define BIT_7E        0174
#define BIT_7D        0175
#define BIT_7C        0176
#define BIT_7B        0177
#define BIT_7A        0200
#define BIT_8F        0201
#define BIT_8G1       0202
#define BIT_8E        0203
#define BIT_8D        0204
#define BIT_8C        0205
#define BIT_8B        0206
#define BIT_8A        0207
#define BIT_NEXT      0210
#define BIT_BELL      0211
#define BIT_CYCLE     0212
// 0213は未使用
#define BIT_NOTE      0214
#define BIT_SPEAKER   0215
// 0216は未使用
// 0217は未使用

#define DISP_DATA_BIT_COUNT       142

// 桁ごとに表示セグメントのビット位置を対応付けした配列
static uint8_t segmentBitPosList[AM50288H_DIGIT_COUNT][AM50288H_SEGMENT_COUNT] = {
  // A, B, C, D, E, F, G1, G2, J, K, L, M, N, P
  {BIT_1A, BIT_1B, BIT_1C, BIT_1D, BIT_1E, BIT_1F, BIT_1G1, BIT_1G2, BIT_1J, BIT_1K, BIT_1L, BIT_1M, BIT_1N, BIT_1P},
  {BIT_2A, BIT_2B, BIT_2C, BIT_2D, BIT_2E, BIT_2F, BIT_2G1, BIT_2G2, BIT_2J, BIT_2K, BIT_2L, BIT_2M, BIT_2N, BIT_2P},
  {BIT_3A, BIT_3B, BIT_3C, BIT_3D, BIT_3E, BIT_3F, BIT_3G1, BIT_3G2, BIT_3J, BIT_3K, BIT_3L, BIT_3M, BIT_3N, BIT_3P},
  {BIT_4A, BIT_4B, BIT_4C, BIT_4D, BIT_4E, BIT_4F, BIT_4G1, BIT_4G2, BIT_4J, BIT_4K, BIT_4L, BIT_4M, BIT_4N, BIT_4P},
  {BIT_5A, BIT_5B, BIT_5C, BIT_5D, BIT_5E, BIT_5F, BIT_5G1, BIT_5G2, BIT_5J, BIT_5K, BIT_5L, BIT_5M, BIT_5N, BIT_5P},
  {BIT_6A, BIT_6B, BIT_6C, BIT_6D, BIT_6E, BIT_6F, BIT_6G1, BIT_6G2, BIT_6J, BIT_6K, BIT_6L, BIT_6M, BIT_6N, BIT_6P},
  {BIT_7A, BIT_7B, BIT_7C, BIT_7D, BIT_7E, BIT_7F, BIT_7G1, BIT_7G2, BIT_7J, BIT_7K, BIT_7L, BIT_7M, BIT_7N, BIT_7P},
  {BIT_8A, BIT_8B, BIT_8C, BIT_8D, BIT_8E, BIT_8F, BIT_8G1, BIT_8G2, BIT_8J, BIT_8K, BIT_8L, BIT_8M, BIT_8N, BIT_8P}
};

// マークの定数とビット位置を対応付けした配列
static uint8_t markBitPosList[AM50288H_MARK_COUNT] = {
  BIT_BATTERY,  // MARK_BATTERY
  BIT_SPEAKER,  // MARK_SPEAKER
  BIT_ANNTENA,  // MARK_ANNTENA
  BIT_NOTE,     // MARK_NOTE
  BIT_SQUARE,   // MARK_SQUARE
  BIT_CYCLE,    // MARK_CYCLE
  BIT_DIAMOND,  // MARK_DIAMOND
  BIT_BELL,     // MARK_BELL
  BIT_ASTERISK, // MARK_ASTERISK
  BIT_NEXT      // MARK_NEXT
};

AM50288H::AM50288H(uint8_t lePin, uint8_t dinPin, uint8_t sckPin, uint8_t ledA1Pin, uint8_t ledA2Pin, uint8_t ledKPin) {
  _lePin = lePin;
  _dinPin = dinPin;
  _sckPin = sckPin;
  _ledA1Pin = ledA1Pin;
  _ledA2Pin = ledA2Pin;
  _ledKPin = ledKPin;
}

AM50288H::AM50288H(uint8_t lePin, uint8_t dinPin, uint8_t sckPin) {
  _lePin = lePin;
  _dinPin = dinPin;
  _sckPin = sckPin;
  _ledA1Pin = 255;
  _ledA2Pin = 255;
  _ledKPin = 255;
}

void AM50288H::begin() {
  for (int8_t i = 0; i < AM50288H_DISP_BUFFER_LENGTH; i++) {
    _dispBuffer[i] = 0x00;
  }

  pinMode(_lePin, OUTPUT);
  digitalWrite(_lePin, LOW);

  pinMode(_dinPin, OUTPUT);
  digitalWrite(_dinPin, LOW);

  pinMode(_sckPin, OUTPUT);
  digitalWrite(_sckPin, HIGH);

  if (_ledA1Pin != 255) {
    pinMode(_ledA1Pin, OUTPUT);
    digitalWrite(_ledA1Pin, LOW);
  }

  if (_ledA2Pin != 255) {
    pinMode(_ledA2Pin, OUTPUT);
    digitalWrite(_ledA2Pin, LOW);
  }

  if (_ledKPin != 255) {
    pinMode(_ledKPin, OUTPUT);
    digitalWrite(_ledKPin, LOW);
  }
}

void AM50288H::refresh() {
  delayMicroseconds( 1 );
  for (int8_t i = AM50288H_DISP_BUFFER_LENGTH - 1; i >= 0; i--) {
    uint8_t val = _dispBuffer[i];
    for (int8_t j = 0; j < 8; j++)  {
      digitalWrite(_sckPin, LOW);
      delayMicroseconds( 1 );

      digitalWrite(_dinPin, !!(val & (1 << j)));
      delayMicroseconds( 1 );

      digitalWrite(_sckPin, HIGH);
      delayMicroseconds( 1 );
    }
  }

  delayMicroseconds( 1 );
  digitalWrite(_lePin, HIGH);
  delayMicroseconds( 1 );
  digitalWrite(_lePin, LOW);
}

void AM50288H::clear() {
  for (int8_t i = 0; i < AM50288H_DISP_BUFFER_LENGTH; i++) {
    _dispBuffer[i] = 0x00;
  }
}

void AM50288H::setAllBit(uint8_t value) {
  uint8_t b = 0x00;
  if (value) {
    b = 0xFF;
  } else {
    b = 0x00;
  }
  for (int8_t i = 0; i < AM50288H_DISP_BUFFER_LENGTH; i++) {
    _dispBuffer[i] = b;
  }
}

void AM50288H::setMarkBit(uint8_t mark, uint8_t value) {
  if (mark >= AM50288H_MARK_COUNT) {
    return;
  }

  uint8_t dispBitIndex = markBitPosList[mark];
  setBit(dispBitIndex, value);
}

void AM50288H::setSegmentBits(uint8_t digitIndex, const uint8_t (&segmentBits)[AM50288H_SEGMENT_COUNT]) {
  if (digitIndex >= AM50288H_DIGIT_COUNT) {
    return;
  }

  for (int i = 0; i < AM50288H_SEGMENT_COUNT; i++) {
    setBit(segmentBitPosList[digitIndex][i], segmentBits[i]);
  }
}

void AM50288H::clearSegmentBits(uint8_t digitIndex) {
  if (digitIndex >= AM50288H_DIGIT_COUNT) {
    return;
  }

  for (int i = 0; i < AM50288H_SEGMENT_COUNT; i++) {
    setBit(segmentBitPosList[digitIndex][i], 0);
  }
}

void AM50288H::setBit(uint8_t dispBitIndex, uint8_t value) {
  if (dispBitIndex >= DISP_DATA_BIT_COUNT) {
    return;
  }

  uint8_t byteIndex = dispBitIndex / 8;
  uint8_t bitIndex = (7 - dispBitIndex % 8);

  uint8_t b = _dispBuffer[byteIndex];
  if (value) {
    b = b | (1 << bitIndex);
  } else {
    b = b & ~(1 << bitIndex);
  }
  _dispBuffer[byteIndex] = b;
}

void AM50288H::toggleBit(uint8_t dispBitIndex) {
  if (dispBitIndex >= DISP_DATA_BIT_COUNT) {
    return;
  }

  uint8_t byteIndex = dispBitIndex / 8;
  uint8_t bitIndex = (7 - dispBitIndex % 8);

  uint8_t b = _dispBuffer[byteIndex];
    b = b ^ (1 << bitIndex);
  _dispBuffer[byteIndex] = b;
}

