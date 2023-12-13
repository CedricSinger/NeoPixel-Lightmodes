#ifndef NEOPIXEL_LIGHTMODES_H
#define NEOPIXEL_LIGHTMODES_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>

enum LEDMode {OFF, ONECOLOR, WAVE, PULSE, RAINBOW};

class NeoLM {
    public:
        void setMode(LEDMode NEW_MODE);
        void setColor1(byte red, byte green, byte blue);
        void setColor2(byte red, byte green, byte blue);
        void setColors(byte[2][3] newColors);
        void setSpeed(int SPEED);
        void setBrightness(int BRIGHTNESS);
        void updateState();
        void synchronize();
        void lightUp();

    private:
        int led_count;
        int led_pin;
        float periodic_state;
        float pulse_state;
        int periocic_speed;
        int brightness;
        byte[2][3] colors;
        LEDMode led_mode;
        Adafruit_NeoPixel strip;
    
        void onecolor();
        void wave();
        void pulse();
        void rainbow();
    };
    
#endif