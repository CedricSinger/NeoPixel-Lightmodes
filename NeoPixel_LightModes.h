#ifndef NEOPIXEL_LIGHTMODES_H
#define NEOPIXEL_LIGHTMODES_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <util.h>

class NeoLM {
    public:
        NeoLM(int LED_COUNT, int LED_PIN);
        void setMode(LEDMode NEW_MODE);
        void setColor1(byte red, byte green, byte blue);
        void setColor2(byte red, byte green, byte blue);
        void setColors(byte newColors[2][3]);
        void setSpeed(int SPEED);
        void setBrightness(int BRIGHTNESS);
        void setData(LEDData data);
        void updateState();
        void synchronize();
        void lightUp();

    private:
        int led_count;
        int led_pin;
        float periodic_state;
        float pulse_state;
        int periodic_speed;
        int brightness;
        byte colors[2][3];
        LEDMode led_mode;
        Adafruit_NeoPixel strip;
    
        void onecolor();
        void wave();
        void pulse();
        void rainbow();
    };
    
#endif