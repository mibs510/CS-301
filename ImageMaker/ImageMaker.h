//
// Assignment Created by Varick Erickson
//

#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstring>

const int MAX_WIDTH = 800;
const int MAX_HEIGHT = 800;
const int MAX_COLOR = 255;
enum COLOR { RED, GREEN, BLUE };

using namespace std;

//  Please put your pre and post comments in this file. See page 139 in the textbook.

class ImageMaker
{
public:
    /*
    * Function:
    * The default constructor that creates a blank black image.
    *
    * Precondition:
    * No preconditions needed to invoke this default constructor.
    *
    * Postcondition:
    * The function does not return anything. It creates an image with 0 width and 0 height, and sets the initial pen
    * color to black (0, 0, 0). The "image" variable is initialized to be white.
    */
    ImageMaker();

    /*
    * Function:
    * The second constructor that opens an image and loads the entire contents for editing.
    *
    * Precondition:
    * An absolute or relative path to a file is needed to invoke this constructor.
    *
    * Postcondition:
    * The constructor does not return anything. It initializes the "image" matrix to be white (255, 255,255).
    * The default pen color is then set to black. And finally, the constructor invokes ImageMaker::LoadImage(filename).
    */
    ImageMaker(string filename);

    // Opens image with filename and stores information into

    /*
    * Function:
    * This function opens a ppm file and loads it into memory.
    *
    * Precondition:
    * An absolute or relative path to a file is needed to invoke this constructor.
    *
    * Postcondition:
    * This function does not return anything. Firstly it checks to see if the file is opened and if either the badbit or
    * failbit is set by ifstream. If these conditions are met, a "File failed to open" exception is thrown.
    * It then begins to import the header into memory which includes the magic number, dimensions, and maximum color
    * value. These values are checked and exceptions are thrown if these do not meet the scope of the application.
    * For instance, the magic number must be "P3" or a "Bad magic number" exception is thrown. Both SetWidth() and
    * SetHeight() functions throw a "" exception if the width or height are not between 0 - MAX_WIDTH/MAX_HEIGHT.
    * The maximum color value must be 255 otherwise a "Max color range not 255" exception is thrown.
    * Lastly it imports the body of the ppm file into image[MAX_WIDTH][MAX_HEIGHT][3]. While traversing through the ppm
    * file, the function checks the RGB values. All RGB values must be between 0 - 255 or else a "Color value invalid"
    * exception is thrown.
    */
    void LoadImage(string filename);

    /*
    * Function:
    * This function opens a ppm file and loads it into memory.
    *
    * Precondition:
    * An absolute or relative path to a file is needed to invoke this constructor.
    *
    * Postcondition:
    * This function does not return anything. Firstly it checks to see if the file is opened and if either the badbit or
    * failbit is set by ifstream. If these conditions are met, a "File failed to open" exception is thrown.
    * It then begins to import the header into memory which includes the magic number, dimensions, and maximum color
    * value. These values are checked and exceptions are thrown if these do not meet the scope of the application.
    * For instance, the magic number must be "P3" or a "Bad magic number" exception is thrown. Both SetWidth() and
    * SetHeight() functions throw a "" exception if the width or height are not between 0 - MAX_WIDTH/MAX_HEIGHT.
    * The maximum color value must be 255 otherwise a "Max color range not 255" exception is thrown.
    * Lastly it imports the body of the ppm file into image[MAX_WIDTH][MAX_HEIGHT][3]. While traversing through the ppm
    * file, the function checks the RGB values. All RGB values must be between 0 - 255 or else a "Color value invalid"
    * exception is thrown.
    */
    void SaveImage(string filename);

    // Size functions

    /*
    * Function:
    * Get the width of the image.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the width of the image as an integer.
    */
    int GetWidth();

    /*
    * Function:
    * Get the height of the image.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the height of the image as an integer.
    */
    int GetHeight();

    /*
    * Function:
    * Set the width of the image to a specified size in pixels.
    *
    * Precondition:
    * An integer between 0 - MAX_WIDTH is required for this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Width out of bounds" exception if the integer passed is not
    * between 0 - MAX_WIDTH. If the exception is not thrown, the function will reassign the variable width to the
    * integer passed.
    */
    void SetWidth(int width);

    /*
    * Function:
    * Set the height of the image to a specified size in pixels.
    *
    * Precondition:
    * An integer between 0 - MAX_HEIGHT is required for this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Height out of bounds" exception if the integer passed is
    * not between 0 - MAX_HEIGHT. If the exception is not thrown, the function will reassign the variable height to the
    * integer passed.
    */
    void SetHeight(int height);

    // Color functions

    /*
    * Function:
    * Get the value of the red pen.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the 8-bit value (0-255) of the variable pen_red as an integer.
    */
    int GetPenRed();

    /*
    * Function:
    * Get the value of the green pen.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the 8-bit value (0-255) of the variable pen_green as an integer.
    */
    int GetPenGreen();

    /*
    * Function:
    * Get the value of the blue pen.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the 8-bit value (0-255) of the variable pen_blue as an integer.
    */
    int GetPenBlue();

    /*
    * Function:
    * Set the value of the red pen.
    *
    * Precondition:
    * An integer between 0 - 255 is required for this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Color value invalid" exception if the integer passed is
    * not between 0 - 255. If the exception is not thrown, the function reassigns the pen_red variable.
    */
    void SetPenRed(int newR);

    /*
    * Function:
    * Set the value of the green pen.
    *
    * Precondition:
    * An integer between 0 - 255 is required for this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Color value invalid" exception if the integer passed is
    * not between 0 - 255. If the exception is not thrown, the function reassigns the pen_green variable.
    */
    void SetPenGreen(int newG);

    /*
    * Function:
    * Set the value of the blue pen.
    *
    * Precondition:
    * An integer between 0 - 255 is required for this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Color value invalid" exception if the integer passed is
    * not between 0 - 255. If the exception is not thrown, the function reassigns the pen_blue variable.
    */
    void SetPenBlue(int newB);

    // Drawing methods
    // These methods will use the current red, green, blue values of the pen

    /*
    * Function:
    * Set the value of the blue pen.
    *
    * Precondition:
    * An integer between 0 - 255 is required for this function. The correct color intended to be used for drawing the
    * pixel must be set before invoking this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Color value invalid" exception if the integer passed is
    * not between 0 - 255. If the exception is not thrown, the function reassigns the pen_blue variable.
    */
    void DrawPixel(int x, int y);

    /*
    * Function:
    * Draw a rectangle with two diagonal points (x1, y1) and (x2, y2) or vice versa.
    *
    * Precondition:
    * Two pairs of coordinates need to be passed to the function. Additionally, the correct color intended to be used
    * for drawing the rectangle must be set before invoking this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Point out of bounds" exception for any of the two pairs of
    * coordinates that are out of bound (GetHeight() & GetWidth()).
    */
    void DrawRectangle(int x1, int y1, int x2, int y2);

    /*
    * Function:
    * Draw a line from point A (x1, y1) to point B (x2, y2) or vice versa.
    *
    * Precondition:
    * Two pairs of coordinates need to be passed to the function. Additionally, the correct color intended to be used
    * for drawing the pixel must be set before invoking this function.
    *
    * Postcondition:
    * The function does not return anything but will throw a "Point out of bounds" exception for any of the two pairs of
    * coordinates that are out of bound (GetHeight() & GetWidth()).
    */
    void DrawLine(int x1, int y1, int x2, int y2);

private:
    string magic;
    int width;
    int height;
    int pen_red;    // Used by draw functions
    int pen_green;  // Used by draw functions
    int pen_blue;   // Used by draw functions

    /*
    * Function:
    * This function checks if one pair of coordinates are within the dimensions of the image.
    *
    * Precondition:
    * Two integers are required for this function passed in the (x, y) format.
    *
    * Postcondition:
    * This function returns a boolean and does not throw exceptions. The function normally returns true unless
    * if the x integer is < 0 or >= GetWidth(), then it returns false. The function also returns false if the y integer
    * is < 0 or >= GetHeight().
    */
    bool PointInBounds(int x, int y);  // Not a bad idea to implement

               //   x          y
    short image[MAX_WIDTH][MAX_HEIGHT][3];

    // Custom functions

    /*
    * Function:
    * This function changes all three RGB vales for each pixel of the variable image array to the color value specified.
    *
    * Precondition:
    * An short integer between 0 - 255 is required for this function.
    *
    * Postcondition:
    * The function does not return anything. The function throws an exception "Color value invalid" if the color short
    * int passed is not between 0 and 255. Otherwise, the RGB values for all pixels are overwritten to the color short
    * int passed.
    */
    void ColorImage(short color);
};

#endif //IMAGEMAKER_H
