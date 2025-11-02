#include <iostream>
#include <vector>
#include <chrono>
#include <numeric> // For std::iota


constexpr int MATRIX_SIZE = 10000;

long long friendly(const std::vector<std::vector<int>>& matrix);

long long unfriendly(std::vector<std::vector<int>>& matrix);


void cacheLevelCompare();


void compare();