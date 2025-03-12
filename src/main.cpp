// For right now, this is just me tinkering with SIMD, trying to understand how it works.
#include "vector.hpp"
#include <iostream>
#include <chrono>

int main() {
    // Add two vectors
    Vector a({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});
    Vector b({8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0});
    Vector _add = a + b;
    Vector _sub = a - b;
    Vector _mul = a * b;
    Vector _div = a / b;
    Vector _and = a & b;
    Vector _or = a | b;
    Vector _xor = a ^ b;
    Vector _eq = a == b;
    Vector _neq = a != b;
    Vector _lt = a < b;
    Vector _gt = a > b;
    Vector _lte = a <= b;
    Vector _gte = a >= b;
    std::cout << "a = " << a.to_string() << std::endl;
    std::cout << "b = " << b.to_string() << std::endl;
    std::cout << "a + b = " << _add.to_string() << std::endl;
    std::cout << "a - b = " << _sub.to_string() << std::endl;
    std::cout << "a * b = " << _mul.to_string() << std::endl;
    std::cout << "a / b = " << _div.to_string() << std::endl;
    std::cout << "a & b = " << _and.to_string() << std::endl;
    std::cout << "a | b = " << _or.to_string() << std::endl;
    std::cout << "a ^ b = " << _xor.to_string() << std::endl;
    std::cout << "a == b = " << _eq.to_string() << std::endl;
    std::cout << "a != b = " << _neq.to_string() << std::endl;
    std::cout << "a < b = " << _lt.to_string() << std::endl;
    std::cout << "a > b = " << _gt.to_string() << std::endl;
    std::cout << "a <= b = " << _lte.to_string() << std::endl;
    std::cout << "a >= b = " << _gte.to_string() << std::endl;

    // Speed test, add 1M vectors and time it
    Vector c({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});
    Vector d({8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0});
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000000; ++i) {
        c += d;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "8B additions took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms (SIMD)" << std::endl;
    std::cout << "c = " << c.to_string() << std::endl;

    //Compare with just numbers
    double e[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    double f[] = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000000; ++i) {
        for (int j = 0; j < 8; ++j) {
            e[j] += f[j];
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "8B additions took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms (basic)" << std::endl;
    std::cout << "e = [";
    for (int i = 0; i < 8; ++i) {
        std::cout << e[i];
        if (i < 7) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}
