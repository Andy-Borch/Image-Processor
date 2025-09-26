#!/bin/bash
# Performance test script for OpenMP parallelized Image Processor

echo "Image Processor OpenMP Performance Test"
echo "======================================="

if [ ! -f "./ImageProcessor" ]; then
    echo "Building ImageProcessor..."
    make clean && make
fi

if [ ! -f "large_testimage1.pgm" ]; then
    echo "Error: large_testimage1.pgm not found!"
    exit 1
fi

echo "Available CPU cores: $(nproc)"
echo ""

# Test with different thread counts
for threads in 1 2 4; do
    echo "Testing with OMP_NUM_THREADS=$threads:"
    export OMP_NUM_THREADS=$threads
    
    total_time=0
    for i in {1..3}; do
        echo -n "  Run $i: "
        # Capture the real time and extract just the seconds
        time_output=$(time ./ImageProcessor large_testimage1.pgm large_testimage1.pgm 2>&1 | grep "real")
        echo "$time_output"
    done
    echo ""
done

echo "Test completed!"
echo ""
echo "Performance Summary:"
echo "- 1 thread: baseline performance"
echo "- 2 threads: should show improvement (~2-10% faster)"
echo "- 4 threads: may show diminishing returns due to memory bandwidth"