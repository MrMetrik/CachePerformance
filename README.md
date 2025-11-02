# CPU Cache Performance Benchmarks (C++)

A C++ project designed to illustrate the massive performance impact of CPU caching and memory access patterns. This repository contains two core benchmarks:

Cache Locality Test: Compares fast Row-Major (cache-friendly) matrix traversal against slow Column-Major (cache-unfriendly) traversal.
Cache Latency Test: Measures access latency (in nanoseconds) across different working set sizes (1KB to 64MB) to reveal the speed of the L1, L2, L3 caches, and RAM.

🏗️ Building and Running
This project requires a C++11 or later compiler. Compile with optimizations (-O3) for the most realistic timing results.

# Example compilation command
g++ main.cpp -o cache_benchmark -std=c++17 -O3 

# Run the benchmark
./cache_benchmark
# Output Example
![Screenshot of an Output for my system after running this program.](https://github.com/MrMetrik/CachePerformance/blob/master/Output.png)
