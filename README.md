# C++ Image Processor
This image processor project was the basis for my C++ class at CSU. Every 2 weeks, we would get an assignment that builds off of the previous assignments. All of the code can be found in the `ImageProcessor` directory, which includes an `html` directory for code documentation. 

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
    - Implemented:
         - `ColorImage.convertToBinary()`
      - `ColorImage.convertToGrayscale()`
      - `GrayscaleImage.convertToBinary()`
      - `GrayscaleImage.convertToRGB()`
      - `BinaryImage.convertToGrayscale()`
      - `BinaryImage.convertToRGB()`
      - `Image.getInputFormat(filename)`
      - `Image.writeImage(filename, PixelType)`
    - Removed `ColorImage.writeRegulairzed(filename)`, `GrayscaleImage.writeRegulairzed(filename)`, `BinaryImage.writeRefularized(filename)`

        - To make code cleaner, `Image.writeImage(filename, PixelType)` can write any type of image, regularized or not, so it is used for all image writing
    - Slightly modified methods like `load()` and `regularize()` in each sublass
    - Reused methods via inheritance like `Image.imageFileIsValid(imageFile)`, `Image.providedFilesAreValid(rowChecksum, colChecksum)`, and `Image.run()`
 
## Assignment 5
- Generate Doxygen comments and documentation
- Calculate correlation between 2 grayscale images
- Implemented:
     - `GrayscaleImage.correlation(image1, image2)`
     - `GrayscaleImage.getAverageIntensity(image)`
- Added comments to document code using doxygen
 
## Future Improvements
- Improve polymorphism and inheritance
- Parallelize regularize and conversion methods with OpenMP and/or CUDA
  - And any others that might benefit from parallelization
- Make the run method compute certain things based on input args so user can decide what the program does
- Add a link in this readme to the documentation page

          
