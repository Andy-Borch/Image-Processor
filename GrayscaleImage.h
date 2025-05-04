#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include "Pixel.h"
#include "Image.h"

#include <cmath>

/** 
 * A grayscale image class that loads, normalizes, and converts grayscale images. It inhereits the Image class.
 */
class GrayscaleImage : public Image{
    public:
    GrayscaleImage(); /**< Grayscale image constructor */

    int correlation(const GrayscaleImage& image1, const GrayscaleImage& Image2); /**< Calculates the correlation score of two grayscale images */

    inline int loadImage(std::string filename) {return 0;}

    int loadImageFast(std::string filename); /**< Optimized version of laodImage. Only for grayscale images. Returns an error if the image is incorrectly formatted.*/

    int regularize() override; /**< Normalizes a grayscale image */

    int convertToBinary() override; /**< Converts a grayscale image to binary format */
    int convertToRGB() override; /**< Converts a grayscale image to color format */
    inline int convertToGrayscale(){return 0;} /**< Does nothing since converting grayscale to grayscale makes no changes */

    private:
    double getAverageIntensity(const GrayscaleImage& i); /**< Calculates the average intesnity of a grayscale image. Used as a helper method for the correlation score calculation */
};
#endif //GRAYSCALE_IMAGE_H