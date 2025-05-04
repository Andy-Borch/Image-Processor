#include "Pixel.h"

Pixel::Pixel():
    redValue(-1),
    greenValue(-1),
    blueValue(-1),
    singleValue(-1),
    type(PixelType::RGB) {
    std::vector<int> pixelValues;
}

Pixel::Pixel(int val, PixelType t) :
    singleValue(-1),
    type(t) {
    std::vector<int> pixelValues;
}

int Pixel::pixelSum(){
    return redValue + greenValue + blueValue;
}
