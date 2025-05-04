#include "Image.h"
#include "ColorImage.h"
#include "GrayscaleImage.h"
#include "BinaryImage.h"

#include <sstream>

Image::Image(int highest, int lowest): 
    rows(-1),
    cols(-1),
    maxPossibleVal(-1),
    actualMaxVal(lowest),
    actualMinVal(highest){
}

int Image::run(std::string arg1, std::string arg2){
    std::string inputFormat = getInputFormat(arg1);
   
    if (inputFormat != "P2"){
        std::cerr << "Unknown input file format" << std::endl;
        return -1;
    }

    GrayscaleImage image1 = GrayscaleImage();
    GrayscaleImage image2 = GrayscaleImage();

    if(image1.imageFileIsValid(arg1) < 0 || image1.loadImageFast(arg1) < 0 ||
       image2.imageFileIsValid(arg2) < 0 || image2.loadImageFast(arg2) < 0){
        std::cerr << "One of the input files is invalid" << std::endl;
        return -1;
    }

    int result = image1.correlation(image1, image2);

    if(result >= 0){
        return result;
    } else {
        return -1;
    }

}

int Image::providedFilesAreValid(std::string rowChecksumFile, std::string colChecksumFile){
    std::ifstream rowFile(rowChecksumFile);
    std::ifstream colFile(colChecksumFile);

    if(!rowFile.is_open() or !colFile.is_open()){
        std::cerr << "Error opening one of the image files" << std::endl;
        return -1;
    }

    return 0;
}

int Image::imageFileIsValid(std::string imageFile){
    std::ifstream ifile(imageFile);

    if(!ifile.is_open()){
        std::cerr << "Error opening image file" << std::endl;
        return -1;
    }

    if(ifile.peek() == std::ifstream::traits_type::eof()){
        std::cerr << "Image file is empty" << std::endl;
        return -1;
    }
    return 0;
}

std::string Image::getInputFormat(std::string& filename){
    std::ifstream input(filename);
    if(!input.is_open()){
        std::cerr << "Could not open input file" << std::endl;
        return "Unknown";
    }
    std::string header;
    input >> header;
    return header;
}

int Image::computeRowChecksums(){
    int sum;
    for(int r = 0; r < rows; r++){
        sum = 0;
        for(int c = 0; c < cols; c++){
            sum += imageData.at(r).at(c).pixelSum();
        }
        rowChecksumVec.push_back(sum);
    }
    return 0;
}

int Image::computeColChecksums(){
    int sum;
    for(int c = 0; c < cols; c++){
        sum = 0;
        for(int r = 0; r < rows; r++){
            sum += imageData.at(r).at(c).pixelSum();
        }
        colChecksumVec.push_back(sum);
    }
    return 0;
}

int Image::writeRowChecksum(std::string rowChecksum){
    std::ofstream rowCheck(rowChecksum);
    for(int i = 0; i < rows; i++){
        rowCheck << rowChecksumVec.at(i) << std::endl;
    }
    if(rowCheck.fail()){
        std::cerr << "Error writing to row checksum file" << std::endl;
        return -1;
    }
    return 0;
}

int Image::writeColChecksum(std::string colChecksum){
    std::ofstream colCheck(colChecksum);
    for(int i = 0; i < cols; i++){
        colCheck << colChecksumVec.at(i) << std::endl;
    }
    if(colCheck.fail()){
        std::cerr << "Error writing to column checksum file" << std::endl;
        return -1;
    }
    return 0;
}

int Image::writeImage(std::string filename, PixelType type){
    std::ofstream output(filename);

    if(!output){
        std::cerr << "Cannot open output file" << std::endl;
    }

    std::string format;
    int maxVal = 255;

    if(type == PixelType::BINARY){
        format = "P1";
        maxVal = 1;
    } else if (type == PixelType::GRAYSCALE){
        format = "P2";
    } else if (type == PixelType::RGB){
        format = "P3";
    } else {
        std::cerr << "Invalid format prevented writing image file" << std::endl;
        return -1;
    }

    output << format << " " << cols << " " << rows << " " << maxVal << "\n";

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if(type == PixelType::RGB){
                output << imageData.at(r).at(c).getRedValue() << ' ' <<
                          imageData.at(r).at(c).getGreenValue() << ' ' <<
                          imageData.at(r).at(c).getBlueValue() << "\n";
            } else {
                output << imageData.at(r).at(c).getSingleValue() << "\n";
            }
        }
    }

    if(output.fail()){
        std::cerr << "Error writing to file" << std::endl;
        return -1;
    }

    return 0;
}