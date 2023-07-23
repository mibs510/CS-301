//
// Created by we7289 on 5/31/2021.
//

#ifndef BOX_H
#define BOX_H


class Box {
public:
    Box();
    Box(int width, int height, int length);

    double getWidth() const;
    void setWidth(double width);

    double getHeight() const;
    void setHeight(double height);

    double getLength() const;
    void setLength(double length);

    double getSurfaceArea() const;
    double getVolume() const;

    void resize(double factor);

private:
    double width;
    double height;
    double length;
};
#endif // BOX_H