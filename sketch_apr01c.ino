#define FASTLED_INTERNAL
#include <FastLED.h>


// Params for MATRIX_MATRIX_WIDTH and height
#define MATRIX_WIDTH 25
#define MATRIX_HEIGHT 25

#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)
CRGB leds[ NUM_LEDS ];

#define LAST_VISIBLE_LED 298

#define BRIGHTNESS 100

#define LED_PIN  6
#define COLOR_ORDER CRGB
#define CHIPSET     NEOPIXEL

/**
   Maps out the XY coordinates to the proper LED.
*/
uint16_t XY (uint16_t x, uint16_t y) {
  // any out of bounds address maps to the first hidden pixel
  if ( (x >= MATRIX_WIDTH) || (y >= MATRIX_HEIGHT) ) {
    return (LAST_VISIBLE_LED + 1);
  }

  const uint16_t XYTable[] = {
    302, 303, 304, 305, 306, 307, 308, 309, 219, 218, 187, 186, 137, 136, 95, 94, 68, 310, 311, 312, 313, 314, 315, 316, 317,
    318, 319, 320, 321, 322, 323, 324, 325, 220, 217, 188, 185, 138, 135, 96, 93, 69, 326, 327, 328, 329, 330, 331, 332, 333,
    334, 335, 336, 337, 338, 339, 340, 341, 221, 216, 189, 184, 139, 134, 97, 92, 70, 342, 343, 344, 345, 346, 347, 348, 349,
    231, 232, 233, 234, 235, 350, 351, 352, 222, 215, 190, 183, 140, 133, 98, 91, 71, 353, 354, 356, 63, 64, 65, 66, 67,
    357, 358, 359, 360, 361, 362, 363, 364, 223, 214, 191, 182, 141, 132, 99, 90, 72, 365, 366, 367, 368, 369, 370, 371, 372,
    240, 239, 238, 237, 236, 373, 374, 375, 224, 213, 192, 181, 142, 131, 100, 89, 73, 376, 377, 378, 62, 61, 60, 59, 58,
    379, 380, 381, 382, 383, 384, 385, 386, 225, 212, 193, 180, 143, 130, 101, 88, 74, 387, 388, 389, 390, 391, 392, 393, 394,
    395, 396, 397, 244, 245, 246, 398, 399, 226, 211, 194, 179, 144, 129, 102, 87, 75, 400, 401, 52, 53, 54, 402, 403, 404,
    241, 242, 243, 405, 406, 407, 408, 409, 227, 210, 195, 178, 145, 128, 103, 86, 76, 410, 411, 412, 413, 414, 55, 56, 57,
    415, 416, 417, 418, 248, 247, 419, 420, 228, 209, 196, 177, 146, 127, 104, 85, 77, 421, 422, 51, 50, 423, 424, 425, 426,
    427, 428, 250, 249, 429, 430, 431, 432, 229, 208, 197, 176, 147, 126, 105, 84, 78, 433, 434, 435, 436, 49, 48, 437, 438,
    252, 251, 439, 440, 257, 258, 441, 442, 230, 207, 198, 175, 148, 125, 106, 83, 79, 443, 444, 40, 41, 445, 446, 47, 46,
    447, 448, 255, 256, 449, 259, 450, 451, 452, 206, 199, 174, 149, 124, 107, 82, 453, 454, 455, 39, 456, 42, 43, 457, 458,
    253, 254, 459, 460, 260, 461, 462, 463, 464, 205, 200, 173, 150, 123, 108, 81, 465, 467, 468, 469, 38, 470, 471, 44, 45,
    472, 473, 474, 261, 475, 476, 270, 477, 478, 204, 201, 172, 151, 122, 109, 80, 479, 480, 28, 481, 482, 37, 483, 484, 485,
    486, 487, 262, 488, 489, 269, 271, 490, 491, 492, 202, 171, 152, 121, 110, 493, 494, 495, 27, 29, 496, 497, 36, 498, 499,
    500, 263, 501, 502, 268, 503, 272, 282, 504, 505, 203, 170, 153, 120, 111, 506, 507, 16, 26, 508, 30, 509, 510, 35, 511,
    264, 512, 513, 267, 514, 273, 515, 281, 283, 516, 517, 169, 154, 119, 518, 519, 15, 17, 520, 25, 521, 31, 522, 523, 34,
    524, 525, 266, 526, 527, 274, 280, 528, 284, 294, 529, 168, 155, 118, 530, 4, 14, 531, 18, 24, 532, 533, 32, 534, 535,
    536, 265, 537, 538, 275, 539, 279, 540, 285, 293, 541, 167, 156, 117, 542, 5, 13, 543, 19, 544, 23, 545, 546, 33, 547,
    548, 549, 550, 551, 276, 278, 552, 286, 553, 292, 554, 166, 157, 116, 555, 6, 556, 12, 557, 20, 22, 558, 559, 560, 561,
    562, 563, 564, 565, 566, 277, 567, 287, 291, 568, 295, 165, 158, 115, 3, 569, 7, 11, 570, 21, 571, 572, 573, 574, 575,
    576, 577, 578, 579, 580, 581, 582, 288, 290, 583, 296, 164, 159, 114, 2, 584, 8, 10, 585, 586, 587, 588, 589, 590, 591,
    592, 593, 594, 595, 596, 597, 598, 599, 289, 600, 297, 163, 160, 113, 1, 601, 9, 602, 603, 604, 605, 606, 607, 608, 609,
    610, 611, 612, 613, 614, 615, 616, 617, 618, 298, 619, 162, 161, 112, 620, 0, 621, 622, 623, 624, 625, 626, 627, 628, 629
  };

  uint16_t i = (y * MATRIX_WIDTH) + x;
  uint16_t j = XYTable[i];
  return j;
}

#include "Fire.h"

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );
}

unsigned long startTime = 0;

void loop()
{
    unsigned long loopTime;

    while ((loopTime = millis() - startTime) < 10000) {
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
    }

    Fire fire = Fire();
    while ((loopTime = millis() - startTime) < 20000) {
      fire.runPattern();
    }

    startTime = millis();
}

void DrawOneFrame( uint8_t startHue8, int8_t yHueDelta8, int8_t xHueDelta8)
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



/**
   Sets all LEDs in the mask to a colour.
*/
void full_mask (int color) {
  uint16_t i, j;

  for (i = 0; i <= MATRIX_WIDTH; i++) {
    for (j = 0; j <= MATRIX_HEIGHT; j++) {
      leds[XY(i, j)] = color;
    }
  }
}
