#include "CRGBLED.h"


CRGBLED::CRGBLED(uint8_t _red_pin, uint8_t _green_pin, uint8_t _blue_pin)
        : color_() {
    red_pin_ = _red_pin;
    green_pin_ = _green_pin;
    blue_pin_ = _blue_pin;
}

void CRGBLED::setColor(const CRGBLED::Color &_color) {
    color_ = _color;
    writeColor();
}

void CRGBLED::setColor(uint8_t _red, uint8_t _green, uint8_t _blue) {
    color_.red = _red;
    color_.green = _green;
    color_.blue = _blue;
    writeColor();
}

CRGBLED::Color CRGBLED::getColor() {
    return color_;
}

void CRGBLED::writeColor() {
    analogWrite(red_pin_, color_.red);
    analogWrite(green_pin_, color_.green);
    analogWrite(blue_pin_, color_.blue);
}

CRGBLED::Color::Color(uint8_t _red, uint8_t _green, uint8_t _blue) {
    red = _red;
    green = _green;
    blue = _blue;
}

CRGBLED::Color::Color() : Color{0, 0, 0} {

}

void CRGBLED::Color::update(uint8_t _red, uint8_t _green, uint8_t _blue) {
    red = _red;
    green = _green;
    blue = _blue;
}


