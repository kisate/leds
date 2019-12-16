
#include "FastLED.h"

const int PIN = 6;
const int MAT_X = 5;
const int MAT_Y = 5;
const int NUM_LEDS = MAT_X*MAT_Y;
const int CORNER = 0;
const int DIRECTION = 0;
const int EFFECT_NUM = 0;
class Picture 
{
public:
    int height;
    byte** pixels;
    CHSV* palette;
    Picture(byte** _pixels, CHSV* _palette, int _height) : height(_height), pixels(_pixels), palette(_palette) {}
};

class Parameters
{
public:
    int brightness;
    int delay;
    Parameters(int _brightness, int _delay) : brightness(_brightness), delay(_delay) {}
};

class Effect
{
public:
    Picture& picture;
    Parameters& params;
    Effect(Picture& _picture, Parameters& _params) : picture(_picture), params(_params) {}
    Effect& operator=(const Effect& other) 
    {
        picture = other.picture;
        params = other.params;
    }
};

CRGB leds[NUM_LEDS];
byte current_mat[MAT_X][MAT_Y];
Effect effects[EFFECT_NUM];

byte mat_1[7][MAT_X] = 
{
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1},
    {0, 1, 1, 1, 0}
};

void setup() {
    FastLED.addLeds<WS2811, PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    pinMode(13, OUTPUT);

    for (int i = 0; i < MAT_X; ++i) memset(current_mat[i], 0, MAT_Y*sizeof(byte));
    CHSV pal_1[] = {CHSV(0, 0, 0), CHSV(200, 255, 255)};
    Picture pic_1 = Picture((byte**) mat_1, pal_1, 7);
    Parameters parm_1 = Parameters(80, 30);
    effects[0] = Effect(pic_1, parm_1);
}

inline void set_led(int x, int y, CHSV color)
{
    int position = 0;
    if (CORNER == 0 && DIRECTION == 0)
    {
        if (y % 2 == 1) x = MAT_X - x - 1;
        position =  y*MAT_X + x;
    }
    else if(CORNER == 0 && DIRECTION == 1)
    {
        if (x % 2 == 1) y = MAT_Y - y - 1;
        position = x*MAT_Y + y;
    }
    else if(CORNER == 1 && DIRECTION == 0)
    {
        x = MAT_X - x - 1;
        if (x % 2 == 1) y = MAT_Y - y - 1;
        position = x*MAT_Y + y;
    }
    else if(CORNER == 1 && DIRECTION == 1)
    {
        if (y % 2 == 0) x = MAT_X - x - 1;
        position = y*MAT_X + x;
    }
    else if(CORNER == 2 && DIRECTION == 0)
    {
        y = MAT_Y - y - 1;
        if (y % 2 == 0) x = MAT_X - x - 1;
        position =  y*MAT_X + x;
    }
    else if(CORNER == 2 && DIRECTION == 1)
    {
        x = MAT_X - x - 1;
        if (x % 2 == 0) y = MAT_Y - y - 1;
        position = x*MAT_Y + y;
    }
    else if(CORNER == 3 && DIRECTION == 0)
    {
        if (x % 2 == 0) y = MAT_Y - y - 1;
        position = x*MAT_Y + y;
    }
    else if(CORNER == 3 && DIRECTION == 1)
    {
        y = MAT_Y - y - 1;
        if (y % 2 == 1) x = MAT_X - x - 1;
        position =  y*MAT_X + x;
    }
    leds[position] = color;
}

void move_image()
{
    for (int row = 1; row < MAT_Y; ++row)
        for (int col = 0; col < MAT_X; ++col) 
            current_mat[col][row] = current_mat[col][row-1];
}

void show_effect(Effect& effect)
{
    FastLED.setBrightness(effect.params.brightness);
    for (int row = effect.picture.height - 1; row >= 0; --row)
    {
        move_image();
        for (int col = 0; col < MAT_X; ++col)
        {
            current_mat[col][0] = effect.picture.pixels[row][col];
        }
        
        for (int x = 0; x < MAT_X; ++x)
            for (int y = 0; y < MAT_Y; ++y) 
                set_led(x, y, effect.picture.palette[current_mat[x][y]]);
        FastLED.show();
        delay(effect.params.delay);
    }
}

void loop() {
    while (true)
    {
        for (int i = 0; i < EFFECT_NUM; ++i)
        {
            show_effect(effects[i]);
        }
    }
    
}
