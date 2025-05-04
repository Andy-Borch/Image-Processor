NETID=aborch
#Used for naming your tar file
ASN=ImageProcessor
#Used for naming the executable
SOURCES=main.cpp Image.cpp ColorImage.cpp GrayscaleImage.cpp BinaryImage.cpp Pixel.cpp
#List any files you need to make for source files
HEADERS=Image.h ColorImage.h GrayscaleImage.h BinaryImage.h Pixel.h
#List any Header files
OBJECTS=main.o Image.o ColorImage.o GrayscaleImage.o BinaryImage.o Pixel.o
#List any Object files you need to create for your assignment
TARNAME=$(NETID)_$(ASN).tar

RM=rm
#Change to del if on a windows machine
#Used to create a standard tar file naming convention

#Required Content Do not Modify below this line
CXXFLAGS=-Wall -Werror -Wfatal-errors -O2

%.o: %.cpp
		g++ -c -g $(CXXFLAGS) $<

$(ASN): $(OBJECTS)
		g++ $(CXXFLAGS) -g -o $(ASN) $(OBJECTS)

tar:
		tar -cf $(TARNAME) $(SOURCES) $(HEADERS) Makefile

clean:
		$(RM) -f $(TARNAME) $(ASN) $(OBJECTS) *.gch *.gcov a.out
