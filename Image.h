#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

#include "Pixel.h"

/** \brief An image class for Images.
 * 
 * An Image class for validating input, writing new images, and running the program. 
 * It contains methods for conversions from one image type to another that is overriden in each image type subclass. 
 */
class Image{
    public:
    Image(int highest, int lowest); /**< Constructor that takes in a min and max value */

    int rows; /**< Number of rows in the image */
    int cols; /**< Number of columns in the image */
    int maxPossibleVal; /**< Highest allowed pixel value in the image */
    int actualMaxVal; /**< Highest pixel value found in the image */
    int actualMinVal; /**< Lowest pixel value found in the image */

    std::vector<std::vector<Pixel>> imageData; /**< 2 dimensional vectors that store the pixel value data of the image */

    std::vector<int> colChecksumVec; /**< 1 dimensional array that stores the checksum value for a column*/
    std::vector<int> rowChecksumVec; /**< 1 dimensional array that stores the checksum value for a row*/

    int imageFileIsValid(std::string imageFile); /**< Checks image file validity*/
    int providedFilesAreValid(std::string rowChecksum, std::string colChecksum); /**< Checks additional file's validity*/

    int computeRowChecksums(); /**< Computes checksum for each row of an image*/
    int computeColChecksums(); /**< Computes checksum for each column of an image*/
    int writeRowChecksum(std::string rowChecksum); /**< Writes the row checksums to an output file*/
    int writeColChecksum(std::string colChecksum); /**< Writes the column checksums to an output file*/

    /**Writes an image file. It determines what type of image to write based on the pixel type parameter*/
    int writeImage(std::string filename, PixelType type); 

    virtual int loadImage(std::string imageFile) = 0; /**< Loads an image into memory. Ensures image format matches what is specifiyed by the user */
    virtual int regularize() = 0; /**< Intensity normalizes an image */
  
    virtual int convertToBinary() = 0; /**< Converts an image to binary format (.pbm) */
    virtual int convertToGrayscale() = 0; /**< Converts an image to grayscale format (.pgm) */
    virtual int convertToRGB() = 0; /**< Converts an image to color format (.ppm) */
    
    static int run(std::string arg1, std::string arg2); /**< Driver method, called in main class. Changes based on what operations are required */

    private:
    static std::string getInputFormat(std::string& filename); /**< Reads header of a given file to determine initial format.  */

    //Currently not comparing to a provided checksum like in HW2, maybe add later.
};

#endif //IMAGE_H