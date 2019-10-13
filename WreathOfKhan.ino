//
//  Star Trek - Wreath Of Khan
//  WS2812 LED holiday wreath
//
//


#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NumberOfPixels 20

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NumberOfPixels, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  SparkleColor(1000,50);
  FadeEyesUp(5);
  Sparkle(strip.Color(128,0,0),200,10);
  FadeEyesDown(5);
  rainbow(25);
  rainbow(25);
  rainbowCycle(10,5);
}

//fade red eyes
void FadeEyesUp(uint8_t wait) {
  for(uint8_t color=0; color<255; color++){
    strip.setPixelColor(18,strip.Color(color,0,0));
    strip.setPixelColor(19,strip.Color(color,0,0));
    strip.show();
    delay(wait);
  }
}

void FadeEyesDown(uint8_t wait) {
  for(uint8_t color=255; color>0; color--){
    strip.setPixelColor(18,strip.Color(color,0,0));
    strip.setPixelColor(19,strip.Color(color,0,0));
    strip.show();
    delay(wait);
  }
}

//Fade from one color to another, range of pixels
//void FadeRange(StartingColor, EndingColor, Delay, StartPixel, EndPixel) {
//  for(uint8_t pixel=StartPixel; pixel<=EndPixel ; pixel++) {
//    strip.setPixelColor(pixel,
//  }
//}

// random sparkle
void Sparkle(uint32_t color, uint32_t count, uint8_t wait) {
  for(uint8_t i=0; i<NumberOfPixels-2; i++) {
    strip.setPixelColor(i,strip.Color(0,0,0));
  }
  for (uint32_t j=0; j<count; j++) {
    int sparkle=random(NumberOfPixels-2);
    strip.setPixelColor(sparkle, color);
    strip.show();
    delay(20);
    strip.setPixelColor(sparkle, strip.Color(0,0,0));
    strip.show();
    delay(20);
  }
}

void SparkleColor(uint32_t count, uint8_t wait){
  for (uint32_t j=0; j<count; j++) {
    int sparkle=random(NumberOfPixels-2);
    int red=random(255);
    int green=random(255);
    int blue=random(255);
    strip.setPixelColor(sparkle, strip.Color(red,green,blue));
    strip.show();
    delay(20);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels()-2; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels()-2; i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t cycles, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*cycles; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels()-2; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

