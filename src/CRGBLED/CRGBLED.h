#ifndef SRC_CRGBLED_H
#define SRC_CRGBLED_H


#include <Arduino.h>


class CRGBLED {
public:
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        Color(uint8_t _red, uint8_t _green, uint8_t _blue);

        Color();

        void update(uint8_t _red, uint8_t _green, uint8_t _blue);
    };

    CRGBLED(uint8_t _red_pin, uint8_t _green_pin, uint8_t _blue_pin);

    void setColor(const Color &_color);

    void setColor(uint8_t _red, uint8_t _green, uint8_t _blue);

    Color getColor();

private:
    Color color_;

    uint8_t red_pin_;
    uint8_t green_pin_;
    uint8_t blue_pin_;

    void writeColor();
};



#endif //SRC_CRGBLED_H
