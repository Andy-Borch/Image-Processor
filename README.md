# C++ Image Processor

This project was developed as a part of my C++ course at Colorado State University. Over the course of the semester, we extended the functionality of the image processing program through a series of assignments, each building on the previous one.

All code is located in the `ImageProcessor` directory. HTML documentation generated using Doxygen can be found in the `html` directory. The only provided code was the makefile.

All methods are designed to gracefully exit and provide informative output if input files are missing, improperly formatted, or otherwise invalid. The program has been tested across a variety of inputs during development, but it has not been exhaustively tested, so certain edge cases may still cause unexpected behavior or crashes.

> **Note:** The `run` method was modified with each assignment to meet specific requirements. For example, `Image.run()` may take different arguments or call different methods depending on the assignment. It can be modified to perform all operations (e.g., load, compute checksums, write checksums, regularize, convert, write converted) by adjusting the expected number of input arguments and method calls.

---

## Assignments

### Assignment 0: File Validation

- Validates given files and reports any formatting or syntax errors.
- **Implemented Methods:**
  - `Image.imageFileIsValid(imageFile)`
  - `Image.providedFilesAreValid(rowChecksum, colChecksum)`
  - `Image.loadImage(imageFile)`
  - `Image.run(arg1, arg2, arg3)`

---

### Assignment 1: Checksum Comparison

- Compares a given `.ppm` image file with provided checksum files.
- **Note:** Code for this assignment was rewritten afterward and is not included.

---

### Assignment 2: Checksum Generation

- Generates row and column checksums for a given `.ppm` image file.
- **Implemented Methods:**
  - `Image.computeRowChecksums()`
  - `Image.computeColChecksums()`
  - `Image.writeRowChecksum(filename)`
  - `Image.writeColChecksum(filename)`
  - `Pixel.pixelSum()`

---

### Assignment 3: Image Regularization

- Regularizes the image based on pixel intensity.
- **Implemented Methods:**
  - `Image.regularize()`
  - `Image.writeRegularize(filename)`

---

### Assignment 4: Format Conversion and Polymorphism

- Regularizes and converts between RGB, Grayscale, and Binary image formats.
- **New Files:**
  - `ColorImage.cpp`
  - `GrayscaleImage.cpp`
  - `BinaryImage.cpp`
  - `PixelType.cpp` (enum)

- **Implemented Methods:**
  - `ColorImage.convertToBinary()`
  - `ColorImage.convertToGrayscale()`
  - `GrayscaleImage.convertToBinary()`
  - `GrayscaleImage.convertToRGB()`
  - `BinaryImage.convertToGrayscale()`
  - `BinaryImage.convertToRGB()`
  - `Image.getInputFormat(filename)`
  - `Image.writeImage(filename, PixelType)`

- Removed subclass-specific `writeRegularized()` methods to simplify writing logic:
  - `Image.writeImage()` now handles writing for all image types, whether regularized or not.

- Polymorphism used to share methods across subclasses:
  - `Image.imageFileIsValid()`
  - `Image.providedFilesAreValid()`
  - `Image.run()`

---

### Assignment 5: Documentation and Correlation

- Generated code documentation using Doxygen.
- Calculated correlation score between two grayscale images.
- **Implemented Methods:**
  - `GrayscaleImage.correlation(image1, image2)`
  - `GrayscaleImage.getAverageIntensity(image)`

---

### Assignment 6: Optimization with Valgrind

- Optimize correlation calculations from Assignment 5 using Valgrind profiler
  - Reduced number of operations performed by reading in file all at once, which reduced the number of calls the standard inpput file stream.
- **Implemented Methods:**
  - `GrayscaleImage.loadImageFast(filename)` 

---

## Future Improvements

- Improve polymorphism and inheritance structure.
- Parallelize operations such as regularization and conversion using OpenMP and/or CUDA.
  - Add cuda compile and run commands to makefile
- Refactor `Image.run()` method to dynamically determine actions based on user input.
    - Prompt user to submit correct number of files after choosing the operation to be performed
- Add a link to this README pointing to the generated Doxygen documentation.
- Improve error detection and messages
- Add unit tests

---

## Documentation

[Link to html documentation]

