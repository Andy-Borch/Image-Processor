#ifndef PIXEL_H
#define PIXEL_H

#include <vector>

/**
 * A pixel enum that specifies the pixel type/
 */
enum class PixelType {
    RGB, GRAYSCALE, BINARY
};

/**
 * A Pixel class that creates various types of pixels. The value(s) of each pixel can be modified and accessed.
 * @return A pixel object
 */
class Pixel{  

    /**Private variables associated with the pixel */
    private:
    int redValue;
    int greenValue;
    int blueValue;
    int singleValue;
    PixelType type;

    public:
    Pixel();/**< Default pixel constructor that creates a color pixel */
    Pixel(int val, PixelType t);/**< Alternate pixel constructor that creates the pixel type specificed by the type parameter */

    inline int getRedValue() {return redValue;} /**< Accesor methods to access red value */
    inline int getGreenValue() {return greenValue;} /**< Accesor methods to access green value */
    inline int getBlueValue() {return blueValue;} /**< Accesor methods to access blue value */
    inline int getSingleValue() const {return singleValue;} /**< Accesor methods to access value of grayscale or binary pixel */
    inline PixelType getType() {return type;} /**< Accesor methods to access pixel type */

    inline void setRed(const int r) {redValue = r;} /**< Mutator methods to modify red pixel value */
    inline void setGreen(const int g) {greenValue = g;} /**< Mutator methods to modify green pixel value */
    inline void setBlue(const int b) {blueValue = b;} /**< Mutator methods to modify blue pixel value */
    inline void setValue(int v) {singleValue = v;} /**< Mutator methods to modify pixel value of grayscale or binary pixels */
    inline void setType(PixelType t){type = t;} /**< Mutator methods to modify pixel type */

    int pixelSum(); /**< Calculates the sum of all values in a given pixel */

};

#endif //PIXEL_H