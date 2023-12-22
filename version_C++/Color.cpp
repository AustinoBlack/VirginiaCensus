#include "Color.h"

Color::Color( double r, double g, double b){
    red = r;
    green = g;
    blue = b;
}

std::string Color::asString() {
    return "<path fill=\"rgb(" + std::to_string((red/100)*255) + "," + std::to_string((green/100)*255) + ","+ std::to_string((blue/100)*255) + ")\" ";
}
