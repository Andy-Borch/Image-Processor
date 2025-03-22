# C++ Image Processor
This image processor project was the basis for my C++ class at CSU

- Note: The run method was altered every assignment due to assignment requirements. For example, `Image.run()` was changed to take a different number of arguments, call different methods, etc.

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
        - `Image.writeRegularize()` 
          
