#include "Image.h"

int main(int argc, char* argv[]){
    if(argc != 3){
        std::cerr <<"Error: Incorrect number of arguments provided" << std::endl;
        return -1;
    }

    if(Image::run(argv[1], argv[2]) >= 0){
        return 0;
    }
    return -1;
}