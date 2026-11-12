
# Student Record Search Optimization

## Project Description

This project compares two methods of searching for student records in C.

The baseline version uses a linked list and linear search.
The optimized version uses a sorted array and binary search.

The goal is to compare their performance and understand how data structures and memory access affect execution time.

## Compilation Instructions

Compile the baseline version:

```bash
gcc -O2 -Wall baseline.c -o baseline
```

Compile the optimized version:

```bash
gcc -O2 -Wall optimized.c -o optimized
```

## Running the Programs

Run the baseline:

```bash
./baseline
```

Run the optimized version:

```bash
./optimized
```

## Benchmark Instructions

To run the baseline five times:

```bash
for i in 1 2 3 4 5; do
    ./baseline
done
```

To run the optimized version five times:

```bash
for i in 1 2 3 4 5; do
    ./optimized
done
```

The median execution time from five runs is used to compare performance.

## Expected Output

Each program prints the input size, total search time in milliseconds, and the last student ID found.

Example:

```text
Size: 1000 | Time: 0.698 ms | Found ID: 990
```

Execution times will vary depending on the computer.

## Performance Comparison

The baseline uses O(n) linear search.

The optimized version uses O(log n) binary search.

Both programs test 1,000, 10,000, 100,000, and 500,000 student records, performing 1,000 searches per input size.

Each version frees its dynamically allocated memory after testing.
