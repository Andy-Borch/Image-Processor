#include "GrayscaleImage.h"

GrayscaleImage::GrayscaleImage(): Image(256, -1){}

int GrayscaleImage::loadImageFast(std::string imageFile){
    std::ifstream ifile(imageFile);
    if (!ifile.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return -1;
    }

    std::stringstream st;
    st << ifile.rdbuf();
    std::string fileContent = st.str();
    ifile.close();

    std::istringstream stream(fileContent);
    std::string value;

    stream >> value;
    if (value != "P2") {
        std::cerr << "Invalid grayscale image format" << std::endl;
        return -1;
    }

    stream >> value;
    if (value.find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Column value in grayscale file contains invalid characters" << std::endl;
        return -1;
    } else {
        cols = stoi(value);
    }

    stream >> value;
    if (value.find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Row value in grayscale file contains invalid characters" << std::endl;
        return -1;
    } else {
        rows = stoi(value);
    }

    stream >> value;
    if (value.find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Max pixel in grayscale file value not accepted" << std::endl;
        return -1;
    } else {
        maxPossibleVal = stoi(value);
    }

    imageData.resize(rows, std::vector<Pixel>(cols));

    int v = 0;
    int count = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (!(stream >> value)) {
                std::cerr << "Number of elements in grayscale file is less than what header specifies" << std::endl;
                return -1;
            }

            if (value.find_first_not_of("0123456789") != std::string::npos) {
                std::cerr << "Pixel in grayscale file contains invalid characters" << std::endl;
                return -1;
            }

            v = stoi(value);
            if (v < 0 || v > maxPossibleVal) {
                std::cerr << "Pixel in grayscale file value is out of range" << std::endl;
                return -1;
            }

            imageData.at(r).at(c).setValue(v);

            if(v > actualMaxVal) {
                actualMaxVal = v;
            }
            if(v < actualMinVal) {
                actualMinVal = v;
            }
            count++;
        }
    }

    if (stream >> value) {
        std::cerr << "Number of elements in grayscale file is greater than what header specifies" << std::endl;
        return -1;
    }

    return 0;
}

int GrayscaleImage::regularize(){
    if(actualMaxVal == actualMinVal){
        std::cerr << "Unable to regularize grayscale file" << std::endl;
        return -1;
    }
    
    int regularizedValue = 0;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            regularizedValue = std::round((imageData.at(r).at(c).getSingleValue() - actualMinVal) * (255.0 / (actualMaxVal - actualMinVal)));
            imageData.at(r).at(c).setValue(regularizedValue);
        }
    }
    return 0;
}

int GrayscaleImage::convertToBinary(){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if (imageData.at(r).at(c).getSingleValue() > 127.5){
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

int GrayscaleImage::convertToRGB(){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            int intensity = imageData.at(r).at(c).getSingleValue();
            imageData.at(r).at(c).setType(PixelType::RGB);
            imageData.at(r).at(c).setRed(intensity);
            imageData.at(r).at(c).setGreen(intensity);
            imageData.at(r).at(c).setBlue(intensity);     
        }
    }
    return 0;
}

/**The correlation is calculated using Pearsons correlation. The average intensity of an image is calculated in the helper method
 * getAverageIntensity(GrayscaleImage i). The numerator and denominator summations and multiplications with the average intensity
 * are calculated in a nested for loop, for every pixel in the image. 
 * The square root for the denominator is calculated outside the loop. 
 * A check is made at the end to ensure the result is a number between -1 and 1
 */
int GrayscaleImage::correlation(const GrayscaleImage& image1, const GrayscaleImage& image2){
    if(image1.rows != image2.rows || image1.cols != image2.cols){
        std::cerr << "Images of unequal dimensions cannot be correlated" << std::endl;
        return -1;
    }

    int rows = image1.rows;
    int cols = image1.cols;

    double image1Average = getAverageIntensity(image1);
    double image2Average = getAverageIntensity(image2);

    double numerator = 0.0;
    double image1SquaredPixelSum = 0.0;
    double image2SquaredPixelSum = 0.0;

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            double image1Value = image1.imageData.at(r).at(c).getSingleValue();
            double image2Value = image2.imageData.at(r).at(c).getSingleValue();

            //sums each (image1 pixel - image1 average) multiplied by (image2 pixel - image2 average)
            numerator += (image1Value - image1Average) * (image2Value - image2Average);

            //sums each (image1 pixel - image1 average) multiplied by (image2 pixel - image2 average) and squares them
            image1SquaredPixelSum += (image1Value - image1Average) * (image1Value - image1Average);
            image2SquaredPixelSum += (image2Value - image2Average) * (image2Value - image2Average);
        }
    }

    //Multiplies and square roots the squared variables for the denominator 
    double denominator = std::sqrt(image1SquaredPixelSum) * std::sqrt(image2SquaredPixelSum);

    double result = numerator / denominator;

    if(result > 1.00000000001 || result < -1.00000000001 || std::isnan(result)){
        std::cerr << "Error correlating images" << std::endl;
        return -1;
    }

    std::cout << result << std::endl;

    return 0;
}

//massing in reference here reduced it from 3.433 billion to 3.398 billion
double GrayscaleImage::getAverageIntensity(const GrayscaleImage& i){
    double intensitySum = 0.0;
    for(int r = 0; r < i.rows; r++){
        for(int c = 0; c < i.cols; c++){
            intensitySum += i.imageData.at(r).at(c).getSingleValue();
        }
    }
    double intensity = static_cast<double>(intensitySum) / (i.rows * i.cols);
    return intensity;
}