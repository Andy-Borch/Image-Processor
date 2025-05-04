#ifndef COLOR_IMAGE_H
#define COLOR_IMAGE_H

#include "Pixel.h"
#include "Image.h"

/** 
 * A color image class that loads, normalizes, and converts color images. It inhereits the Image class.
 */
class ColorImage : public Image{
    public:
    ColorImage(); /**< Color image constructor */

    int loadImage(std::string filename) override; /**< Loads a color image. Returns an error if given image is incorrectly formatted */

    int regularize() override; /**< Normalizes a color image */

    int convertToBinary() override; /**< Converts a color image to binary format */
    int convertToGrayscale() override; /**< Converts a color image to grayscale format */
    inline int convertToRGB(){return 0;} /**< Does nothing since converting color to color makes no changes */

};
#endif //COLOR_IMAGE_H