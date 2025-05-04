#ifndef BINARY_IMAGE_H
#define BINARY_IMAGE_H

#include "Pixel.h"
#include "Image.h"

/** 
 * A binary image class that loads, normalizes, and converts binary images. It inhereits the Image class.
 */
class BinaryImage : public Image{
    public:
    BinaryImage(); /**< Binary image constructor */

    int loadImage(std::string filename) override; /**< Loads a binary image. Returns an error if the image is incorrectly formatted */

    int convertToGrayscale() override; /**< Converts a binary image to grayscale format */
    int convertToRGB() override; /**< Converts a binary image to color format */
    inline int convertToBinary() {return 0;} /**< Does nothing since converting binary to binary makes no changes */

    inline int regularize() {return 0;}; /**< Normalizes a binary image. Does nothing because binary images cannot be normalized */
};
#endif //BINARY_IMAGE_H