#include "FastLED.h"

#define NUM_LEDS 500
//Uses output 11 och 13 for data and clock
const int dataline = 11;
const int clockline = 13;
//const int dataline2 = 7;
//const int cloclline2 = 14;

// Information about the LED strip itself
#define CHIPSET     WS2801
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//In the array leds the adress is
//LED stripes 0-199
//Eyes 200-284
//Small mouths 285-359
//Big mouth 360-409 
//First text 410-430
//Second text 431-452


//The code that uses Brightness and temperature
//is copied and it is possible that it does not work
//as it should, but it do make a rainbow on the LEDs
#define BRIGHTNESS  128

#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky

// How many seconds to show each temperature before switching
#define DISPLAYTIME 60
// How many seconds to show black between switches
#define BLACKTIME   3

void setup() {
  LEDS.addLeds<WS2801, dataline, clockline, RGB, DATA_RATE_KHZ(800)>(leds, NUM_LEDS);

  delay( 3000 ); // power-up safety delay
  FastLED.setBrightness( BRIGHTNESS );
}
void loop() {
  
  //Loop forever
  while (1) {
    
    //Set every third LED to Red, Violed and Purple, in the LED stripes 
    for (int i = 0 ; i < 197 ; i++)
    {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(10);
      leds[i + 1] = CRGB::Violet;
      FastLED.show();
      delay(10);
      leds[i + 2] = CRGB::Purple;
      FastLED.show();
      delay(10);
      i = i + 2;
    }
    delay(3000);
    
    //--------------------------------------------------------------------
    //Set all LEDs in the LED stripes to blue
    for (int i = 0 ; i < 200 ; i++)
    {
      leds[i] = CRGB::Blue;
      FastLED.show();
      delay(10);
      //When the 120s LED is reached turn on the LEDs to the eyes
      //This can be seen in the loop and look like a bug when watching the LEDs
      if (i == 120)
      {
        for (int j = 200 ; j < 285 ; j++)
        {
          leds[j] = CRGB::Green;
          FastLED.show();
        }
      }
      //When the 130s LED is reached turn off the LEDs to the eyes
      if (i == 130)
      {
        for (int j = 200 ; j < 285 ; j++)
        {
          leds[j] = CRGB::Black;
          FastLED.show();
        }
      }
    }
    delay(1000);
    
    //--------------------------------------------------------------------
    //Set every LED in the LED stipes to puple
    for (int i = 0 ; i < 200 ; i++)
    {
      leds[i] = CRGB::Purple;
      FastLED.show();
      delay(10);
      if (i == 120)
      {
      //When the 130s LED is reached turn on the LEDs to the small mouths
        for (int i = 285 ; i < 360 ; i++)
        {
          leds[i] = CRGB::Yellow;
          FastLED.show();
        }
      }
      if (i == 130)
      {
      //When the 130s LED is reached turn off the LEDs to the small mouths
        for (int i = 285 ; i < 360 ; i++)
        {
          leds[i] = CRGB::Black;
          FastLED.show();
        }
      }
    }
    delay(1000);
    //--------------------------------------------------------------------
    //Set all LEDs in the LED stripes to red
    for (int i = 0 ; i < 200 ; i++)
    {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(10);
      if (i == 120)
      {
        //small mouths on
        for (int i = 360 ; i < 410 ; i++)
        {
          leds[i] = CRGB::Blue;
          FastLED.show();
        }
      }

      if (i == 160)
      {
        //small mouths off
        for (int i = 360 ; i < 410 ; i++)
        {
          leds[i] = CRGB::Black;
          FastLED.show();
        }
      }
    }
    delay(1000);
    
    //--------------------------------------------------------------------
    //Set eyes to Green
    for (int i = 200 ; i < 285 ; i++)
    {
      leds[i] = CRGB::Green;
      FastLED.show();
      //delay(10);
    }

    //Set small mouths to yellow
    for (int i = 285 ; i < 360 ; i++)
    {
      leds[i] = CRGB::Yellow;
      FastLED.show();
      //delay(10);
    }

    //Set big mouth to blue
    for (int i = 360 ; i < 410 ; i++)
    {
      leds[i] = CRGB::Blue;
      FastLED.show();
      delay(10);
    }
    //turn off big mouth
    for (int i = 360 ; i < 410 ; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }

    //Set first ligts 
    for (int i = 431 ; i > 410 ; i--)
    {
      leds[i] = CRGB::Purple;
      FastLED.show();
      delay(10);
    }
    //set second lights
    for (int i = 431 ; i < 452 ; i++)
    {
      leds[i] = CRGB::Purple;
      FastLED.show();
      delay(10);
    }
    delay(500);
    //--------------------------------------------------------------------
    //Turn off first ligts
    for (int i = 431 ; i > 410 ; i--)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    //Turn off second lights
    for (int i = 431 ; i < 452 ; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    delay(3000);

    //--------------------------------------------------------------------
    // draw a generic, no-name rainbow
    static uint8_t starthue = 0;
    //fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, 20);
    fill_rainbow( leds + 20, NUM_LEDS - 20, --starthue, 80);

    // Choose which 'color temperature' profile to enable.
    uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
    if ( secs < DISPLAYTIME) {
      FastLED.setTemperature( TEMPERATURE_1 ); // first temperature
      leds[0] = TEMPERATURE_1; // show indicator pixel
    } else {
      FastLED.setTemperature( TEMPERATURE_2 ); // second temperature
      leds[0] = TEMPERATURE_2; // show indicator pixel
    }

    // Black out the LEDs for a few secnds between color changes
    // to let the eyes and brains adjust
    if ( (secs % DISPLAYTIME) < BLACKTIME) {
      memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
    }

    FastLED.show();
    FastLED.delay(8);
    //--------------------------------------------------------------------


    //Turn off all LEDs
    for (int i = 0; i < 452 ; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }

    //Turn on all LEDs with the color Gold
    for (int i = 0; i < 452 ; i++)
    {
      leds[i] = CRGB::Gold;
      FastLED.show();
    }

    //Turn off all LEDs
    for (int i = 0; i < 452 ; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }

    //Wait a little while before the next round
    delay(3000);
  }
}
