# C++ Image Processor
This image processor project was the basis for my C++ class at CSU. Every 2 weeks, we would get an assignment that builds off of the previous assignments.

- Note: The run method was altered every assignment due to assignment requirements. For example, `Image.run()` was changed to take a different number of arguments, call different methods, etc.
     - It could be modified to do everything (load, compute checksums, write checksums, regularize, convert, write converted) by changing expected number of input args and adding method calls, but each assignment only needed some of that functionality. 

## Assignment 0
- Validate given files and report any errors in format or syntax
    - Implemented:
        - `Image.imageFileIsValid(imageFile)`
        - `Image.providedFilesAreValid(rowChecksum, colChecksum)`
        - `Image.loadImage(imageFile)`
        - `Image.run(arg1, arg2, arg3)`

## Assignment 1
- Compare given .ppm file to given checksum files
    - Code not shown due to rewriting program after this assignment was due. 

## Assignment 2
- Generate row and column checksums for given .ppm file
    - Implemented:
        - `Image.computeRowChecksums()`
        - `Image.computeColChecksums()`
        - `Image.writeRowChecksum(filename)`
        - `Image.writeColChecksum(filename)`
        - `Pixel.pixelSum()`

## Assignment 3
- Regularize given .ppm file by pixel value intensity
    - Implemented:
        - `Image.regularize()`
        - `Image.writeRegularize(filename)`
     
## Assignment 4
- Regulairze and convert RGB, Grayscale, and Binary images to other image types
    - Created sub classes `ColorImage.cpp`, `GrayscaleImage.cpp`, `BinaryImage.cpp`
    - Created enum `PixelType.cpp`
    - Implemented `ColorImage.convertToBinary()`
    - Implemented `ColorImage.convertToGrayscale()`
    - Implemented `GrayscaleImage.convertToBinary()`
    - Implemented `GrayscaleImage.convertToRGB()`
    - Implemented `BinaryImage.convertToGrayscale()`
    - Implemented `BinaryImage.convertToRGB()`
    - Implemented `Image.getInputFormat(filename)`
    - Implemented `Image.getOutputFormat(filename)`
    - Implemented `Image.writeImage(filename, PixelType)`
    - Removed `ColorImage.writeRegulairzed(filename)`, `GrayscaleImage.writeRegulairzed(filename)`, `BinaryImage.writeRefularized(filename)`

        - To make code cleaner, `Image.writeImage(filename, PixelType)` can write any type of image, regularized or not, so it is used for all image writing
    - Slightly modified methods like `load()` and `regularize()` in each sublass
    - Reused methods via inheritance like `Image.imageFileIsValid(imageFile)`, `Image.providedFilesAreValid(rowChecksum, colChecksum)`, and `Image.run()`
          
