#include "BinaryImage.h"

BinaryImage::BinaryImage(): Image(2, -1){}

int BinaryImage::loadImage(std::string imageFile){
    std::ifstream ifile(imageFile);

    std::string st = "";
    ifile >> st;
    if(st != "P1"){
        std::cerr << "Invalid binary image format" << std::endl;
        return -1;
    }

    ifile >> st;
    if(st.find_first_not_of("0123456789") != std::string::npos){
        std::cerr << "Column value in binary file contains invalid characters" << std::endl;
        return -1;
    } else {
        cols = stoi(st);
    }

    ifile >> st;
    if(st.find_first_not_of("0123456789") != std::string::npos){
        std::cerr << "Row value in binary file contains invalid characters" << std::endl;
        return -1;
    } else {
        rows = stoi(st);
    }
    
    ifile >> st;
    if(st.find_first_not_of("01") != std::string::npos){
        std::cerr << "Max pixel in binary file value not accepted" << std::endl;
        return -1;
    } else {
        maxPossibleVal = stoi(st);
    }

    imageData.resize(rows, std::vector<Pixel>(cols));

    int c = 0;
    int r = 0;
    int stNum = 0;
    int numElements = 0;

    while(ifile >> st){
        numElements++;
        if(numElements > rows * cols){
            std::cerr << "Number of elements in binary file is greater than what header specifies" << std::endl;
            return -1;
        }

        if(st.find_first_not_of("01") != std::string::npos){
            std::cerr << "Pixel in binary file contains invalid characters" << std::endl;
            return -1;
        }

        stNum = stoi(st);

        if(stNum < 0 || stNum > maxPossibleVal){
            std::cerr << "Pixel value in binary file is out of range" << std::endl;
            return -1;
        }

        imageData.at(r).at(c).setValue(stNum);
        int v = imageData.at(r).at(c).getSingleValue();

        if(v > actualMaxVal){
            actualMaxVal = v;
        }

        if(v < actualMinVal){
            actualMinVal = v;
        }

        c = (c + 1) % cols;
        if (c == 0){
            r++;
        }
    }

    if(numElements < rows * cols){
        std::cerr << "Number of elements in binary file is less than what header specifies" << std::endl;
        return -1;
    }

    return 0;
}

int BinaryImage::convertToGrayscale(){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            int pixel = imageData.at(r).at(c).getSingleValue();
            imageData.at(r).at(c).setType(PixelType::GRAYSCALE);
            imageData.at(r).at(c).setValue(pixel * 255);
        }
    }
    return 0;
}

int BinaryImage::convertToRGB(){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            int pixel = imageData.at(r).at(c).getSingleValue();
            imageData.at(r).at(c).setType(PixelType::RGB);
            imageData.at(r).at(c).setRed(pixel * 255);
            imageData.at(r).at(c).setGreen(pixel * 255);
            imageData.at(r).at(c).setBlue(pixel * 255);
        }
    }
    return 0;
}