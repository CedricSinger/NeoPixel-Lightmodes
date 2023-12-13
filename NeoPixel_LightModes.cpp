#include "NeoPixel_LightModes.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>

NeoLM::NeoLM(int LED_COUNT, int LED_PIN){
    led_count = LED_COUNT;
    led_pin = LED_PIN;
    periodic_state = 0.0;
    pulse_state = 0.0;
    periocic_speed = 100;
    brightness = 100;
    colors = {0,0,0,0,0,0}
    led_mode = OFF;
    strip = new Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
}

void NeoLM::setMode(LEDMode NEW_MODE){
    led_mode = NEW_MODE;
}

void NeoLM::setColor1(byte RED, byte GREEN, byte BLUE){
    colors[0][0] = RED;
    colors[0][1] = GREEN;
    colors[0][2] = BLUE;
}

void NeoLM::setColor2(byte RED, byte GREEN, byte BLUE){
    colors[1][0] = RED;
    colors[1][1] = GREEN;
    colors[1][2] = BLUE;
}

void NeoLM::setColors(byte[2][3] newColors){
    colors = newColors;
}

void NeoLM::setSpeed(int SPEED){
    periodic_speed = SPEED;
}

void NeoLM::setBrightness(int BRIGHTNESS){
    brightness = BRIGHTNESS;
}

void NeoLM::updateState(){
    if (periodic_state < led_count / 2){
      periodic_state = periodic_state + 0.01 * periodic_speed;
    }
    else{
      periodic_state = 0.0;
    }

    if (pulse_state < 1){
      pulse_state = pulse_state + 0.0001 * periodic_speed;
    }
    else{
      pulse_state = 0.0;
    }
}

void NeoLM::synchronize(){
    periodic_state = 0.0;
    pulse_state = 0.0;
}

void NeoLM::lightUp(){
    switch(mode){
        case OFF:{
            strip.clear();
            strip.show();
            break;
        }
        case ONECOLOR:{
            onecolor();
        }
        case WAVE:{
            wave();
        }
        case PULSE:{
            pulse();
        }
        case RAINBOW:{
            rainbow();
        }
    }
}



void NeoLM::onecolor(){
    uint32_t color = strip.Color(colors[0][0], colors[0][1], colors[0][2]);
    strip.fill(color, 0); 
    strip.show();
}

void NeoLM::wave(){
    for(int i = 0; i < led_count; i++){
        strip.setPixelColor(i, (int)(((sin((i + periodic_state) * PI / (led_count / 4)) + 1) * colors[0][0] + (cos((i + periodic_state) * PI / (led_count / 4) + 0.5 * PI) + 1) * colors[1][0]) / 2), 
                                (int)(((sin((i + periodic_state) * PI / (led_count / 4)) + 1) * colors[0][1] + (cos((i + periodic_state) * PI / (led_count / 4) + 0.5 * PI) + 1) * colors[1][1]) / 2), 
                                (int)(((sin((i + periodic_state) * PI / (led_count / 4)) + 1) * colors[0][2] + (cos((i + periodic_state) * PI / (led_count / 4) + 0.5 * PI) + 1) * colors[1][2]) / 2));
    } 
  strip.show();
}

void NeoLM::pulse(){
  uint32_t resultColor = (0, 0, 0);
  
  if(periodic_state <= 0.25)
  {
    resultColor = strip.Color((int)(((cos(pulse_state * PI * 2 + PI) + 1) * colors[0][0] + (cos(pulse_state * PI * 2)) * colors[1][0]) / 2), 
                              (int)(((cos(pulse_state * PI * 2 + PI) + 1) * colors[0][1] + (cos(pulse_state * PI * 2)) * colors[1][1]) / 2), 
                              (int)(((cos(pulse_state * PI * 2 + PI) + 1) * colors[0][2] + (cos(pulse_state * PI * 2)) * colors[1][2]) / 2));
    strip.fill(resultColor, 0);
  }
  else
  {
    resultColor = strip.Color((int)(((cos(((pulse_state - 0.25) * 4 / 3) * PI) + 1) / 2 * colors[0][0] + (cos(((pulse_state - 0.25) * 4 / 3) * PI + PI) + 1) / 2 * colors[1][0]) / 2), 
                              (int)(((cos(((pulse_state - 0.25) * 4 / 3) * PI) + 1) / 2 * colors[0][1] + (cos(((pulse_state - 0.25) * 4 / 3) * PI + PI) + 1) / 2 * colors[1][1]) / 2),
                              (int)(((cos(((pulse_state - 0.25) * 4 / 3) * PI) + 1) / 2 * colors[0][2] + (cos(((pulse_state - 0.25) * 4 / 3) * PI + PI) + 1) / 2 * colors[1][2]) / 2));
    strip.fill(resultColor, 0);
  }  
  strip.show();
}

void NeoLM::rainbow(){

}