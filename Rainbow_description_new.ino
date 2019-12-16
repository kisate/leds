// пример с "бегущей радугой" для библиотеки FastLED

#define NUM_LEDS 200
#include "FastLED.h"
#define PIN 6
CRGB leds[NUM_LEDS];
unsigned short counter;

void setup() {
  FastLED.addLeds<WS2811, PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);
  pinMode(13, OUTPUT);
}


void loop() {
    if (counter > 400)
    {
        for (int i = 0; i < NUM_LEDS; i++ ) 
        { 
            leds[i] = CHSV(counter % 256, 255, 255); //ставим цвет counter, если counter > 400
        }
    }
    else 
    {
        for (int i = 0; i < NUM_LEDS; i++ ) 
        { 
            leds[i] = CHSV(counter % 256 + i, 255, 255); //ставим цвет counter, если counter > 400
        }
    }

    counter++;     
    if (counter > 800) counter = 0;   // counter теперь short, поэтому его значение может быть довольно большим, что нам не очень нужно
    FastLED.show();
    delay(1);         // скорость движения радуги
}
