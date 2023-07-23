#include "ImageMaker.h"


ImageMaker::ImageMaker() {
    this->width = 0;
    this->height = 0;
    this->magic = "P3";

    SetPenRed(0);
    SetPenGreen(0);
    SetPenBlue(0);

    ColorImage(255);
}

ImageMaker::ImageMaker(string filename) {
    // Initialize the variable image to be white
    ColorImage(255);

    // Set the pen to black
    SetPenRed(0);
    SetPenGreen(0);
    SetPenBlue(0);

    LoadImage(filename);

}

void ImageMaker::LoadImage(string filename) {
    ifstream file(filename);
    // Check if opening the file succeeded
    if (file.fail() || !file.is_open()) {
        throw "File failed to open";
    }

    // Get magic number
    string magic_number;
    file >> magic_number;

    //Check the magic number
    if (magic_number != "P3")
        throw "Bad magic number";
    // Set magic string of the object to P3 if the exception hasn't been thrown
    this->magic = "P3";

    //Get width and height
    int Width, Height;
    file >> Width >> Height;

    // Set the width and height. The functions already check if they are acceptable
    SetWidth(Width);
    SetHeight(Height);

    // Get the maximum RGB color value
    int max_color_value;
    file >> max_color_value;

    // Check if max_color_value is within the acceptable value
    if (max_color_value != MAX_COLOR)
        throw "Max color range not 255";

    // Iterate through each pixel and store the RGB values into the image[MAX_WIDTH][MAX_HEIGHT][3] array
    int R, G, B;
    for (int x = 0; x < GetHeight(); x++)
    {
        for (int y = 0; y < GetWidth(); y++)
        {
            file >> R >> G >> B;

            // Check for an invalid color value
            if (R < 0 || R > MAX_COLOR || G < 0 || G > MAX_COLOR || B < 0 || B > MAX_COLOR)
                throw "Color value invalid";

            this->image[y][x][RED] = R;
            this->image[y][x][GREEN] = G;
            this->image[y][x][BLUE] = B;
        }
    }
}

void ImageMaker::SaveImage(string filename) {
    if (GetHeight() <= 0 || GetWidth() <= 0)
        throw "Image must have non-zero dimensions";

    ofstream file;
    file.open(filename);
    if (file.fail()) {
        throw "Could not open file";
    }

    // Write the header
    file << this->magic << endl;
    file << GetWidth() << " " << GetHeight() << endl;
    file << MAX_COLOR << endl;

    // Write the body
    for (int x = 0; x < GetHeight(); x++){
        for (int y = 0; y < GetWidth(); y++)
        {
            file << this->image[y][x][RED] << " " << this->image[y][x][GREEN] << " " << this->image[y][x][BLUE] << " ";
            // New lines only at the end of each row
            if (y == (GetWidth() - 1))
                file << endl;
        }
    }

    // Save file
    file.close();
}

int ImageMaker::GetWidth() {
    return this->width;
}

int ImageMaker::GetHeight() {
    return this->height;
}

void ImageMaker::SetWidth(int width) {
    if (width < 0 || width > MAX_WIDTH)
        throw "Width out of bounds";

    this->width = width;
}

void ImageMaker::SetHeight(int height) {
    if (height < 0 || height > MAX_HEIGHT)
        throw "Height out of bounds";

    this->height = height;
}

int ImageMaker::GetPenRed() {
    return this->pen_red;
}

int ImageMaker::GetPenGreen() {
    return this->pen_green;
}

int ImageMaker::GetPenBlue() {
    return this->pen_blue;
}

void ImageMaker::SetPenRed(int newR) {
    if (newR < 0 || newR > MAX_COLOR)
        throw "Color value invalid";

    this->pen_red = newR;
}

void ImageMaker::SetPenGreen(int newG) {
    if (newG < 0 || newG > MAX_COLOR)
        throw "Color value invalid";

    this->pen_green = newG;
}

void ImageMaker::SetPenBlue(int newB) {
    if (newB < 0 || newB > MAX_COLOR)
        throw "Color value invalid";

    this->pen_blue = newB;
}

void ImageMaker::DrawPixel(int x, int y) {
    if (!PointInBounds(x, y))
        throw "Point out of bounds";

    this->image[x][y][RED] = GetPenRed();
    this->image[x][y][GREEN] = GetPenGreen();
    this->image[x][y][BLUE] = GetPenBlue();
}

void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2) {
    DrawLine(x1, y1, x2, y1);
    DrawLine(x2, y1, x2, y2);
    DrawLine(x2, y2, x1, y2);
    DrawLine(x1, y2, x1, y1);
}

void ImageMaker::DrawLine(int x1, int y1, int x2, int y2) {
    if (!PointInBounds(x1, y1) && !PointInBounds(x2,y2))
    {
        throw "Point out of bounds";
    }

    // If both pairs are equal, draw one pixel and exit
    if ((x1 == x2) && (y1 == y2)){
        DrawPixel(x1, y1);
        return;
    }
    else
    {
        // Draw the second pixel/point
        DrawPixel(x1, y1);
        DrawPixel(x2, y2);
    }

    int start, finish;

    // Check for a horizontal line
    if (y1 == y2) {
        // DrawLine(2, 3, 6, 4) and DrawLine(6, 4, 2, 3) should both produce the same line
        if (x1 > x2)
        {
            start = x2;
            finish = x1;
        }
        else{
            start = x1;
            finish = x2;
        }

        for (int x = start; x < finish; x++)
            DrawPixel(x, y1);
        return;
    }

    // Check for a vertical line
    if (x1 == x2)
    {
        // DrawLine(2, 3, 6, 4) and DrawLine(6, 4, 2, 3) should both produce the same line
        if (y1 > y2)
        {
            start = y2;
            finish = y1;
        }
        else{
            start = y1;
            finish = y2;
        }
        for (int y = start; y < finish; y++)
            DrawPixel(x1, y);
        return;
    }


    double y, m, b;
    // Cast m as a double or else we loose precision and incorrectly draw pixels when passing DrawLine(x1, y1, x2, y2)
    // or DrawLine(x2, y2, x1, y1)
    m = (double)(y2 - y1) / (x2 - x1);
    b = y1 - (m * x1);

    // DrawLine(2, 3, 6, 4) and DrawLine(6, 4, 2, 3) should both produce the same line
    if (x1 > x2)
    {
        start = x2;
        finish = x1;
    }
    else{
        start = x1;
        finish = x2;
    }

    for (int x = start; x < finish; x++)
    {
        y = round(m*x + b);
        // Cast the y value as an int
        DrawPixel(x, (int)y);
    }
}

bool ImageMaker::PointInBounds(int x, int y) {
    if ((x < 0 || x >= GetWidth()) || (y < 0 || y >= GetHeight()))
        return false;
    return true;
}

void ImageMaker::ColorImage(short color) {
    if (color < 0 || color > MAX_COLOR)
        throw "Color value invalid";

    for (int x = 0; x < MAX_WIDTH; x++)
        for(int y = 0; y < MAX_HEIGHT; y++)
        {
            this->image[x][y][RED] = color;
            this->image[x][y][GREEN] = color;
            this->image[x][y][BLUE] = color;
        }
}
