#include "CacheCompare.hpp"
#include <random>


long long friendly(std::vector<std::vector<int>>& matrix) {

    long long sum = 0;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

long long unfriendly(std::vector<std::vector<int>>& matrix) {
    
    long long sum = 0;
    for (int j = 0; j < MATRIX_SIZE; ++j) {
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            sum += matrix[i][j];
        }
    }

    return sum;


}


void compare() {

    
	std::vector<std::vector<int>> matrix(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE));

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        // Fills the row with sequential numbers 0, 1, 2, ...
        std::iota(matrix[i].begin(), matrix[i].end(), 0);
    }


    /* Cache Friendly - Row Major Traversal*/

    std::cout << "Starting cache-friendly (row-major) traversal..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    
    long long sumA = friendly(matrix);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> row_major_time = end - start;
    std::cout << "Row-major sum: " << sumA << std::endl;
    std::cout << "Time taken: " << row_major_time.count() << " ms\n" << std::endl;


    /* Cache Unfriendly - Column Major Traversal*/

    std::cout << "Starting cache-unfriendly (column-major) traversal..." << std::endl;

    start = std::chrono::high_resolution_clock::now();

    long long sumB = unfriendly(matrix);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> column_major_time = end - start;
    std::cout << "Column-major sum: " << sumB << std::endl;
    std::cout << "Time taken: " << column_major_time.count() << " ms\n" << std::endl;

    std::cout << "The cache-unfriendly version was approximately "
        << column_major_time.count() / row_major_time.count()
        << " times slower!" << std::endl;
}


void cacheLevelCompare() {

    // Large Buffer to work with - larger than most L3 cache
    const size_t MAX_BUFFER_SIZE = static_cast<size_t>(64 * 1024) * 1024; // 64 MB
    std::vector<char> data(MAX_BUFFER_SIZE);

    std::fill(data.begin(), data.end(), 1);

    const int ACCESS_COUNT = 10000000; // Count of access requests per test size

    std::cout << "--- Cache Latency Benchmark ---" << std::endl;
    std::cout << std::left << std::setw(15) << "Test Size" << std::setw(20) << "Total Time (ms)" << "Avg. Latency (ns)" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());

    /* Test size ranging between 1KB (1024) and 32MB (32 * 1024 * 1024) */
    for (size_t size = 1024; size <= MAX_BUFFER_SIZE; size *= 2) {
        std::vector<size_t> randomIndices(ACCESS_COUNT);

        std::uniform_int_distribution<int> dist(1, size - 1);

        for (int i = 0; i < ACCESS_COUNT; ++i)
            randomIndices[i] = dist(engine);

        /* Performance Test Loop Start */
        auto start = std::chrono::high_resolution_clock::now();
        volatile char tst = 0;
        for (int i = 0; i < ACCESS_COUNT; ++i) {
            tst = data[randomIndices[i]];
        }

        auto end = std::chrono::high_resolution_clock::now();
        /* Performance Test Loop End */

        std::chrono::duration<double, std::milli> total_time_ms = end - start;
        double nanoseconds_per_access = (total_time_ms.count() * 1000000.0) / ACCESS_COUNT;

        std::string size_str;
        if (size < static_cast<size_t>(1024 * 1024)) {
            size_str = std::to_string(size / 1024) + " KB";
        }
        else {
            size_str = std::to_string(size / static_cast<size_t>(1024 * 1024)) + " MB";
        }
           

        std::cout 
            << std::left << std::setw(15) << size_str 
            << std::fixed << std::setprecision(2) << std::setw(20) << total_time_ms.count() 
            << std::setprecision(2) << nanoseconds_per_access << std::endl;

    }


}