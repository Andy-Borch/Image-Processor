#include "ColorImage.h"

ColorImage::ColorImage(): Image(256, -1){}

int ColorImage::loadImage(std::string imageFile){
    std::ifstream ifile(imageFile);

    std::string st = "";
    ifile >> st;
    if(st != "P3"){
        std::cerr << "Invalid RGB image format" << std::endl;
        return -1;
    }

    ifile >> st;
    if(st.find_first_not_of("0123456789") != std::string::npos){
        std::cerr << "Column value in RGB file contains invalid characters" << std::endl;
        return -1;
    } else {
        cols = stoi(st);
    }

    ifile >> st;
    if(st.find_first_not_of("0123456789") != std::string::npos){
        std::cerr << "Row value in RGB file contains invalid characters" << std::endl;
        return -1;
    } else {
        rows = stoi(st);
    }
    
    ifile >> st;
    if(st.find_first_not_of("0123456789") != std::string::npos){
        std::cerr << "Max pixel in RGB file value not accepted" << std::endl;
        return -1;
    } else {
        maxPossibleVal = stoi(st);
    }

    imageData.resize(rows, std::vector<Pixel>(cols));

    int c = 0;
    int r = 0;
    int p = 0;
    int stNum = 0;
    int numElements = 0;

    while(ifile >> st){
        numElements++;
        if(numElements > rows * cols * 3){
            std::cerr << "Number of elements in RGB file is greater than what header specifies" << std::endl;
            return -1;
        }

        if(st.find_first_not_of("0123456789") != std::string::npos){
            std::cerr << "Pixel in RGB file contains invalid characters" << std::endl;
            return -1;
        }

        stNum = stoi(st);

        if(stNum < 0 || stNum > maxPossibleVal){
            std::cerr << "Pixel value in RGB file is out of range" << std::endl;
            return -1;
        }


        if(p == 0){
            imageData.at(r).at(c).setRed(stNum);
        } else if (p == 1){
            imageData.at(r).at(c).setGreen(stNum);
        } else {
            imageData.at(r).at(c).setBlue(stNum);
        
            int red = imageData.at(r).at(c).getRedValue();
            int green = imageData.at(r).at(c).getGreenValue();
            int blue = imageData.at(r).at(c).getBlueValue();

            if (red < actualMinVal) {
                actualMinVal = red;
            }
            if (green < actualMinVal) {
                actualMinVal = green;
            }
            if (blue < actualMinVal) {
                actualMinVal = blue;
            }

            if (red > actualMaxVal) {
                actualMaxVal = red;
            }
            if (green > actualMaxVal) {
                actualMaxVal = green;
            }
            if (blue > actualMaxVal) {
                actualMaxVal = blue;
            }
        }

        if(p == 2){
            if(c == cols - 1){
                r++;
            }
            c = (c + 1) % cols;
        }

        p = (p + 1) % 3;
    }

    if(numElements < rows * cols * 3){
        std::cerr << "Number of elements in RGB file is less than what header specifies" << std::endl;
        return -1;
    }

    return 0;
}

int ColorImage::regularize(){
    if(actualMaxVal == actualMinVal){
        std::cerr << "Unable to regularize RGB file" << std::endl;
        return -1;
    }
    
    int regularizedRed = 0;
    int regularizedGreen = 0;
    int regularizedBlue = 0;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            regularizedRed = std::round((imageData.at(r).at(c).getRedValue() - actualMinVal) * (255.0 / (actualMaxVal - actualMinVal)));
            regularizedGreen = std::round((imageData.at(r).at(c).getGreenValue() - actualMinVal) * (255.0 / (actualMaxVal - actualMinVal)));
            regularizedBlue = std::round((imageData.at(r).at(c).getBlueValue() - actualMinVal) * (255.0 / (actualMaxVal - actualMinVal)));

            imageData.at(r).at(c).setRed(regularizedRed);
            imageData.at(r).at(c).setGreen(regularizedGreen);
            imageData.at(r).at(c).setBlue(regularizedBlue);
        }
    }
    return 0;
}

int ColorImage::convertToBinary(){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if (imageData.at(r).at(c).pixelSum() > 382.5){
                imageData.at(r).at(c).setType(PixelType::BINARY);
                imageData.at(r).at(c).setValue(1);

            } else{
                imageData.at(r).at(c).setType(PixelType::BINARY);
                imageData.at(r).at(c).setValue(0);
            }
        }
    }
    return 0;
}

int ColorImage::convertToGrayscale(){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            int sum = imageData.at(r).at(c).pixelSum();
            imageData.at(r).at(c).setType(PixelType::GRAYSCALE);
            imageData.at(r).at(c).setValue(round(sum / 3));
        }
    }
    return 0;
}