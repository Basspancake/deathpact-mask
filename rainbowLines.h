#include "Arduino.h"
class rainbowLines {
  public:
    rainbowLines();
    bool runPattern(uint16_t loopTime);
  private:
    void DrawOneFrame(uint8_t startHue8, int8_t yHueDelta8, int8_t xHueDelta8);
};


rainbowLines::rainbowLines() {
}

  bool rainbowLines::runPattern(uint16_t loopTime) {
      int32_t yHueDelta32 = ((int32_t)cos16( loopTime * (27/1) ) * (350 / MATRIX_WIDTH));
      int32_t xHueDelta32 = ((int32_t)cos16( loopTime * (39/1) ) * (310 / MATRIX_HEIGHT));
      DrawOneFrame( loopTime / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
      if( loopTime < 5000 ) {
        FastLED.setBrightness( scale8( BRIGHTNESS, (loopTime * 256) / 5000));
      }
      else {
        FastLED.setBrightness(BRIGHTNESS);
      }
      FastLED.show();
      return true;
    }

  void rainbowLines::DrawOneFrame(uint8_t startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
      {
        uint8_t lineStartHue = startHue8;
        for( uint8_t y = 0; y < MATRIX_HEIGHT; y++) {
          lineStartHue += yHueDelta8;
          uint8_t pixelHue = lineStartHue;      
          for( uint8_t x = 0; x < MATRIX_WIDTH; x++) {
            pixelHue += xHueDelta8;
            leds[ XY(x, y)]  = CHSV ( pixelHue, 255, 255);
          }
        }
      }
