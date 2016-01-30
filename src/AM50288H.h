#ifndef AM50288_h
#define AM50288_h

#include "Arduino.h"

// 表示データのバイト数
#define AM50288H_DISP_BUFFER_LENGTH  18

// 表示マークの個数
#define AM50288H_MARK_COUNT          10

// 14セグメントの桁数
#define AM50288H_DIGIT_COUNT         8

// 1桁のセグメントの個数
#define AM50288H_SEGMENT_COUNT       14

// メソッドの引数で指定するマークの定数
#define MARK_BATTERY      0
#define MARK_SPEAKER      1
#define MARK_ANNTENA      2
#define MARK_NOTE         3
#define MARK_SQUARE       4
#define MARK_CYCLE        5
#define MARK_DIAMOND      6
#define MARK_BELL         7
#define MARK_ASTERISK     8
#define MARK_NEXT         9

class AM50288H {
  private:
    uint8_t _lePin;
    uint8_t _dinPin;
    uint8_t _sckPin;
    uint8_t _ledA1Pin;
    uint8_t _ledA2Pin;
    uint8_t _ledKPin;
    uint8_t _dispBuffer[AM50288H_DISP_BUFFER_LENGTH];

    void setBit(uint8_t dispBitIndex, uint8_t value);
    void toggleBit(uint8_t dispBitIndex);

  public:
    AM50288H(uint8_t lePin, uint8_t dinPin, uint8_t sckPin, uint8_t ledA1Pin, uint8_t ledA2Pin, uint8_t ledKPin);
    AM50288H(uint8_t lePin, uint8_t dinPin, uint8_t sckPin);
    void begin();
    void refresh();
    void clear();
    void setAllBit(uint8_t value);
    void setMarkBit(uint8_t mark, uint8_t value);
    void setSegmentBits(uint8_t digitIndex, const uint8_t (&segmentBits)[AM50288H_SEGMENT_COUNT]);
    void clearSegmentBits(uint8_t digitIndex);
};

#endif
