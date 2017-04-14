#include "Color.h"

const Color Color::BLACK = { 0.0, 0.0, 0.0 };
const Color Color::WHITE = { 1.0, 1.0, 1.0 };
const Color Color::RED =   { 1.0, 0.0, 0.0 };
const Color Color::GREEN = { 0.0, 1.0, 0.0 };
const Color Color::BLUE =  { 0.0, 0.0, 1.0 };

Color::Color() {

}

Color::Color(float red, float green, float blue, float alpha) :
    red(red), green(green), blue(blue), alpha(alpha) {

}
