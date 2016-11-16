#include <Arduino.h>

#ifndef TWODIGIT7SEGMENTDISPLAYMINI
#define TWODIGIT7SEGMENTDISPLAYMINI

class TwoDigit7SegmentDisplayMini
{
  private:
    int8_t vDataPin;
    int8_t vClockPin;
    int8_t vLatchPin;
    int8_t vTransistorPin;

    /* 7 Segment Led display consist of 7 different segments numbered from a-g as shown below...
         a
       -----
    f |     | b
      |  g  |
       -----
    e |     | c
      |  d  |
       -----
  So each bit in a byte represent the above segments. O means the segment is on and 1 means the segment is off (For, Common Anode).
  To display an digit on this display, we will enable & disable the respective "bits" in a byte.
  Below is the byte format that will be sent to 74HC595 to display digit on the display...

            MSB                                       LSB
            Bit7  Bit6  Bit5  Bit4  Bit3  Bit2  Bit1  Bit0
  Segment   g     f     e     d     c     b     a     dot

    */

    int8_t vDigit0 = 0b10000001;
    int8_t vDigit1 = 0b11110011;
    int8_t vDigit2 = 0b01001001;
    int8_t vDigit3 = 0b01100001;
    int8_t vDigit4 = 0b00110011;
    int8_t vDigit5 = 0b00100101;
    int8_t vDigit6 = 0b00000101;
    int8_t vDigit7 = 0b11110001;
    int8_t vDigit8 = 0b00000001;
    int8_t vDigit9 = 0b00100001;
    int8_t vRefreshRate = 10;
    void twoDigitInt2Str(int8_t pDigit);
    void sendDigitBits(int8_t pDigit);

  public:
    TwoDigit7SegmentDisplayMini();
    ~TwoDigit7SegmentDisplayMini();
    TwoDigit7SegmentDisplayMini(int8_t pDataPin, int8_t pClockPin, int8_t pLatchPin, int8_t pTransistorPin);

    void setup(int8_t pDataPin, int8_t pClockPin, int8_t pLatchPin, int8_t pTransistorPin);
    void print(char *pBuffer);
    void print(int8_t pDigit);
    int8_t getRefreshRate(void);
    void setRefreshRate(int8_t pValue);
};

#endif
