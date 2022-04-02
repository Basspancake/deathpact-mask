// Based on the fire effect from Doom.
// Adapted from https://github.com/z1c0/LedMatrix/blob/master/Fire.ino
// and https://fabiensanglard.net/doom_fire_psx/

#include "Arduino.h"

DEFINE_GRADIENT_PALETTE( firePal_gp ) {
  0,    0,    0,    0,      //black
  100,  100,  0,    0,      //dark red
  128,  255,  0,    0,      //red
  220,  255,  255,  0,      //yellow
  255,  255,  255,  255 };  //white

class Fire {
  public:
    Fire();
    bool runPattern();
  private:
    long previousTime;
    void setBottomRow(uint16_t col);
    void doFire();
    void spreadFire(uint16_t src);
    uint8_t firePixels[NUM_LEDS];
    CRGBPalette16 _currentPalette = firePal_gp;

};

Fire::Fire() {
  // Set bottom row to highest index in palette (white)
  setBottomRow(MATRIX_HEIGHT);
}

bool Fire::runPattern() {
  doFire();
  for (int y = 0; y < MATRIX_HEIGHT; y++){ 
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      int index = firePixels[MATRIX_WIDTH * y + x];
      // Index goes from 0 -> MATRIX_HEIGHT, palette goes from 0 -> 255 so need to scale it
      uint8_t indexScale = 255 / MATRIX_HEIGHT;
      leds[XY(x,y)] = ColorFromPalette(_currentPalette, constrain(index * indexScale, 0, 255), 255, LINEARBLEND);
    }
  }
  
  FastLED.show();
  return true;
}

void Fire::doFire() {
  for(uint16_t x = 0 ; x < MATRIX_WIDTH; x++) {
    for (uint16_t y = 1; y < MATRIX_HEIGHT; y++) {
      spreadFire(y * MATRIX_WIDTH + x);
    }
  }
}

void Fire::spreadFire(uint16_t src) {
  if(firePixels[src] == 0) {
    firePixels[src - MATRIX_WIDTH] = 0;
  } else {
    // Commented lines moves fire sideways as well as up, but doesn't look good on low res matrix:
    // int16_t dst = src - rand + 1;
    // firePixels[dst - MATRIX_WIDTH] = firePixels[src] - random8(1);
    firePixels[src - MATRIX_WIDTH] = firePixels[src] - random8(3);
  }
}

void Fire::setBottomRow(uint16_t col) {
  for (uint16_t i = 0; i < MATRIX_WIDTH; i++) {
    firePixels[(MATRIX_HEIGHT - 1) * MATRIX_WIDTH + i] = col;
  }
}
