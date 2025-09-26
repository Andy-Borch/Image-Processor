# C++ Image Processor

This project was developed as a part of my C++ course at Colorado State University. Over the course of the semester, we extended the functionality of the image processing program through a series of assignments, each building on the previous one.

All code is located in the ImageProcessor directory. HTML documentation generated using Doxygen can be found in the html directory. The only provided code was the makefile.

All methods are designed to gracefully exit and provide informative output if input files are missing, improperly formatted, or otherwise invalid. The program has been tested across a variety of inputs during development, but it has not been exhaustively tested, so certain edge cases may still cause unexpected behavior or crashes.

> **Note:** The run method was modified with each assignment to meet specific requirements. For example, Image.run() may take different arguments or call different methods depending on the assignment. It can be modified to perform all operations (e.g., load, compute checksums, write checksums, regularize, convert, write converted) by adjusting the expected number of input arguments and method calls.

## Assignments
---
### Assignment 0: File Validation

* Validates given files and reports any formatting or syntax errors.

* **Implemented Methods:**

    * `Image.imageFileIsValid(imageFile)`
    * `Image.providedFilesAreValid(rowChecksum, colChecksum)`
    * `Image.loadImage(imageFile)`
    * `Image.run(arg1, arg2, arg3)`
---

### Assignment 1: Checksum Comparison

* Compares a given .ppm image file with provided checksum files.

* **Note:** Code for this assignment was rewritten afterward and is not included.
---
### Assignment 2: Checksum Generation

* Generates row and column checksums for a given .ppm image file.

* **Implemented Methods:**

    * `Image.computeRowChecksums()`
    * `Image.computeColChecksums()`
    * `Image.writeRowChecksum(filename)`
    * `Image.writeColChecksum(filename)`
    * `Pixel.pixelSum()`
---
### Assignment 3: Image Regularization

* Regularizes the image based on pixel intensity.

* **Implemented Methods:**

    * `Image.regularize()`
    * `Image.writeRegularize(filename)`
---
### Assignment 4: Format Conversion and Polymorphism

* Regularizes and converts between RGB, Grayscale, and Binary image formats.

* **New Files:**

    * `ColorImage.cpp`
    * `GrayscaleImage.cpp`
    * `BinaryImage.cpp`
    * `PixelType.cpp (enum)`

* **Implemented Methods:**

    * `ColorImage.convertToBinary()`
    * `ColorImage.convertToGrayscale()`
    * `GrayscaleImage.convertToBinary()`
    * `GrayscaleImage.convertToRGB()`
    * `BinaryImage.convertToGrayscale()`
    * `BinaryImage.convertToRGB()`
    * `Image.getInputFormat(filename)`
    * `Image.writeImage(filename, PixelType)`

* Removed subclass-specific writeRegularized() methods to simplify writing logic:

    * `Image.writeImage()` now handles writing for all image types, whether regularized or not.

* Polymorphism used to share methods across subclasses:

    * `Image.imageFileIsValid()`
    * `Image.providedFilesAreValid()`
    * `Image.run()`
---
### Assignment 5: Documentation and Correlation

* Generated code documentation using Doxygen.

* Calculated correlation score between two grayscale images.

* **Implemented Methods:**

    * `GrayscaleImage.correlation(image1, image2)`
    * `GrayscaleImage.getAverageIntensity(image)`
---
### Assignment 6: Optimization with Valgrind

* Optimize correlation calculations from Assignment 5 using Valgrind profiler

* **Implemented Methods:**

    * `GrayscaleImage.loadImageFast(filename)`

* **Modified Methods**

    * `GrayscaleImage.correlation(image1, image2)`
    * `GrayscaleImage.get(averageIntensity(image)`
    * Passed in references to images into these methos instead of the image objects.

* **Total Improvment:**

    * With a 1920x1080 image, these methods reduce the instruction count from 3.48 billion to 3.38 billion instructions"
---
## Future Improvements

* Improve polymorphism and inheritance structure.
* Optimize further based on HW7
   * ~~Add multithreading~~ ✅ **COMPLETED**   
* ~~Parallelize operations such as regularization and conversion using OpenMP and/or CUDA.~~ ✅ **COMPLETED**
    * Add CUDA compile and run commands to makefile
* Refactor `Image.run()` method to dynamically determine actions based on user input.
    * Prompt user to submit correct number of files after choosing the operation to be performed
* Add a link to this README pointing to the generated Doxygen documentation.
* Improve error detection and messages
* Add unit tests

## OpenMP Parallelization

**NEW** - The image processing operations have been parallelized using OpenMP for improved performance on multi-core systems.

### Parallelized Operations

**GrayscaleImage:**
- `getAverageIntensity()` - parallel reduction for intensity sum calculation
- `correlation()` - parallel reduction for Pearson correlation computation
- `regularize()` - parallel pixel-wise intensity normalization
- `convertToBinary()` - parallel pixel-wise binary conversion
- `convertToRGB()` - parallel pixel-wise RGB conversion

**ColorImage:**
- `regularize()` - parallel pixel-wise RGB intensity normalization
- `convertToBinary()` - parallel pixel-wise binary conversion  
- `convertToGrayscale()` - parallel pixel-wise grayscale conversion

**Image (base class):**
- `computeRowChecksums()` - parallel row-wise checksum computation
- `computeColChecksums()` - parallel column-wise checksum computation

### Performance Improvements

Tested on a 4-core system with large grayscale images:
- **Single-threaded**: ~0.266s average
- **2 threads**: ~0.254s average (4.5% improvement)
- **4 threads**: ~0.251s average (5.6% improvement)

### Usage

The parallel code automatically detects available CPU cores. You can control the number of threads using the `OMP_NUM_THREADS` environment variable:

```bash
# Use 2 threads
export OMP_NUM_THREADS=2
./ImageProcessor image1.pgm image2.pgm

# Use all available cores (default)
unset OMP_NUM_THREADS
./ImageProcessor image1.pgm image2.pgm
```

### Performance Testing

Run the included performance test script:
```bash
./test_performance.sh
```

This script will test performance with 1, 2, and 4 threads and provide timing comparisons.
---
## Compiling and Running

Here are the commands to compile and run the program:

**To compile:**
```
make ImageProcessor
```

The Makefile now includes OpenMP support (`-fopenmp` flag) for parallel processing. OpenMP is supported by GCC 4.9+ and most modern compilers.

**To run:**
```
./ImageProcessor <argument(s)>
```
\* Replace `<argument(s)>` with the appropriate input files or flags for the specific assignment or functionality you want to use. The number and type of arguments will vary depending on the program's mode of operation.

**Current Usage (correlation calculation):**
```
./ImageProcessor image1.pgm image2.pgm
```

**To control parallel threads:**
```
export OMP_NUM_THREADS=2
./ImageProcessor image1.pgm image2.pgm
```

**To test performance:**
```
./test_performance.sh
```

**To create a tar archive:**
```
make tar
```
**To extract a tar archive:**
```
tar -xf ImageProcessor.tar
```
**To generate Doxygen documentation:**

1.  Generate a Doxyfile (if you haven't already):

    ```
    doxygen -g
    ```

2.  Run Doxygen:

    ```
    doxygen Doxyfile
    ```

    This will generate the HTML documentation in the `html` directory.
---
## Documentation

\[Link to html documentation\]
