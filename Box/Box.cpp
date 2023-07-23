#include "Box.h"

Box::Box(){
    width = 0;
    height = 0;
    length = 0;
}

Box::Box(int width, int height, int length) {
    setWidth(width);
    setHeight(height);
    setLength(length);
}

double Box::getWidth() const {
    return width;
}

void Box::setWidth(double width) {
    if (width < 0)
        throw "Negative Dimension";

    this->width = width;
}

double Box::getHeight() const {
    return height;
}

void Box::setHeight(double height) {
    // Check for bad value
    if (height < 0)
        throw "Negative Dimension";

    this->height = height;
}

double Box::getLength() const {
    return length;
}

void Box::setLength(double length) {
    if (length < 0)
        throw "Negative Dimension";

    this->length = length;
}

double Box::getSurfaceArea() const {
    return 2*(width*height + width*length + height*length);
}

double Box::getVolume() const {
    return width * length * height;
}

void Box::resize(double factor) {
    setWidth(factor * width);
    setHeight(factor * height);
    setLength(factor * length);
}
