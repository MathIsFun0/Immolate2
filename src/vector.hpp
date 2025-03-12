// Defines a wrapper class for working with SIMD vectors for AVX2 and AVX-512.
#include <immintrin.h>
#include <initializer_list>
#include <iostream>
#include <string>

class Vector {
    public:
        alignas(64) double data[8];
        __m512d avx512_data;
        __m256d avx2_data[2];
        Vector() {
            Vector({0,0,0,0,0,0,0,0});
        }
        Vector(const double* data) {
            for (int i = 0; i < 8; ++i) {
                std::copy(data, data + 8, this->data);
            }
            #ifdef __AVX512F__
                avx512_data = _mm512_load_pd(data);
            #elif __AVX2__
                avx2_data[0] = _mm256_load_pd(data);
                avx2_data[1] = _mm256_load_pd(data + 4);
            #endif
        };
        Vector(std::initializer_list<double> init) {
            std::copy(init.begin(), init.end(), data);
            #ifdef __AVX512F__
                avx512_data = _mm512_load_pd(data);
            #elif __AVX2__
                avx2_data[0] = _mm256_load_pd(data);
                avx2_data[1] = _mm256_load_pd(data + 4);
            #endif
        };

        std::string to_string() {
            // Parse back to data array
            #ifdef __AVX512F__
                _mm512_storeu_pd(data, avx512_data);
            #elif __AVX2__
                _mm256_storeu_pd(data, avx2_data[0]);
                _mm256_storeu_pd(data + 4, avx2_data[1]);
            #endif
            std::string result = "[";
            for (int i = 0; i < 8; ++i) {
                result += std::to_string(data[i]);
                if (i < 7) {
                    result += ", ";
                }
            }
            result += "]";
            return result;
        };

        //Regular old operators
        Vector operator+(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_add_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_add_pd(avx2_data[0], other.avx2_data[0]);
                result.avx2_data[1] = _mm256_add_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] + other.data[i];
                }
            #endif
            return result;
        }

        Vector operator-(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_sub_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_sub_pd(avx2_data[0], other.avx2_data[0]);
                result.avx2_data[1] = _mm256_sub_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] - other.data[i];
                }
            #endif
            return result;
        }
        
        Vector operator*(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_mul_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_mul_pd(avx2_data[0], other.avx2_data[0]);
                result.avx2_data[1] = _mm256_mul_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] * other.data[i];
                }
            #endif
            return result;
        }

        Vector operator/(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_div_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_div_pd(avx2_data[0], other.avx2_data[0]);
                result.avx2_data[1] = _mm256_div_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] / other.data[i];
                }
            #endif
            return result;
        }

        Vector operator=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = other.avx512_data;
            #elif __AVX2__
                avx2_data[0] = other.avx2_data[0];
                avx2_data[1] = other.avx2_data[1];
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] = other.data[i];
                }
            #endif
            return *this;
        }

        Vector operator+=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = _mm512_add_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                avx2_data[0] = _mm256_add_pd(avx2_data[0], other.avx2_data[0]);
                avx2_data[1] = _mm256_add_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] += other.data[i];
                }
            #endif
            return *this;
        }

        Vector operator-=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = _mm512_sub_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                avx2_data[0] = _mm256_sub_pd(avx2_data[0], other.avx2_data[0]);
                avx2_data[1] = _mm256_sub_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] -= other.data[i];
                }
            #endif
            return *this;
        }

        Vector operator*=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = _mm512_mul_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                avx2_data[0] = _mm256_mul_pd(avx2_data[0], other.avx2_data[0]);
                avx2_data[1] = _mm256_mul_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] *= other.data[i];
                }
            #endif
            return *this;
        }

        Vector operator/=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = _mm512_div_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                avx2_data[0] = _mm256_div_pd(avx2_data[0], other.avx2_data[0]);
                avx2_data[1] = _mm256_div_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] /= other.data[i];
                }
            #endif
            return *this;
        }

        //Bitwise operators
        Vector operator&(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_and_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_and_pd(avx2_data[0], other.avx2_data[0]);
                result.avx2_data[1] = _mm256_and_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = (long long)data[i] & (long long)other.data[i];
                }
            #endif
            return result;
        }

        Vector operator|(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_or_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_or_pd(avx2_data[0], other.avx2_data[0]);
                result.avx2_data[1] = _mm256_or_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = (long long)data[i] | (long long)other.data[i];
                }
            #endif
            return result;
        }

        Vector operator^(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_xor_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_xor_pd(avx2_data[0], other.avx2_data[0]);
                result.avx2_data[1] = _mm256_xor_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = (long long)data[i] ^ (long long)other.data[i];
                }
            #endif
            return result;
        }

        Vector operator&=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = _mm512_and_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                avx2_data[0] = _mm256_and_pd(avx2_data[0], other.avx2_data[0]);
                avx2_data[1] = _mm256_and_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] = (long long)data[i] & (long long)other.data[i];
                }
            #endif
            return *this;
        }

        Vector operator|=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = _mm512_or_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                avx2_data[0] = _mm256_or_pd(avx2_data[0], other.avx2_data[0]);
                avx2_data[1] = _mm256_or_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] = (long long)data[i] | (long long)other.data[i];
                }
            #endif
            return *this;
        }

        Vector operator^=(const Vector& other) {
            #ifdef __AVX512F__
                avx512_data = _mm512_xor_pd(avx512_data, other.avx512_data);
            #elif __AVX2__
                avx2_data[0] = _mm256_xor_pd(avx2_data[0], other.avx2_data[0]);
                avx2_data[1] = _mm256_xor_pd(avx2_data[1], other.avx2_data[1]);
            #else
                for (int i = 0; i < 8; ++i) {
                    data[i] = (long long)data[i] ^ (long long)other.data[i];
                }
            #endif
            return *this;
        }

        //Comparison operators
        Vector operator==(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_cmp_pd_mask(avx512_data, other.avx512_data, _CMP_EQ_OQ);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_cmp_pd(avx2_data[0], other.avx2_data[0], _CMP_EQ_OQ);
                result.avx2_data[1] = _mm256_cmp_pd(avx2_data[1], other.avx2_data[1], _CMP_EQ_OQ);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] == other.data[i];
                }
            #endif
            return result;
        }

        Vector operator!=(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_cmp_pd_mask(avx512_data, other.avx512_data, _CMP_NEQ_OQ);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_cmp_pd(avx2_data[0], other.avx2_data[0], _CMP_NEQ_OQ);
                result.avx2_data[1] = _mm256_cmp_pd(avx2_data[1], other.avx2_data[1], _CMP_NEQ_OQ);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] != other.data[i];
                }
            #endif
            return result;
        }

        Vector operator<(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_cmp_pd_mask(avx512_data, other.avx512_data, _CMP_LT_OQ);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_cmp_pd(avx2_data[0], other.avx2_data[0], _CMP_LT_OQ);
                result.avx2_data[1] = _mm256_cmp_pd(avx2_data[1], other.avx2_data[1], _CMP_LT_OQ);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] < other.data[i];
                }
            #endif
            return result;
        }

        Vector operator<=(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_cmp_pd_mask(avx512_data, other.avx512_data, _CMP_LE_OQ);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_cmp_pd(avx2_data[0], other.avx2_data[0], _CMP_LE_OQ);
                result.avx2_data[1] = _mm256_cmp_pd(avx2_data[1], other.avx2_data[1], _CMP_LE_OQ);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] <= other.data[i];
                }
            #endif
            return result;
        }

        Vector operator>(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_cmp_pd_mask(avx512_data, other.avx512_data, _CMP_GT_OQ);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_cmp_pd(avx2_data[0], other.avx2_data[0], _CMP_GT_OQ);
                result.avx2_data[1] = _mm256_cmp_pd(avx2_data[1], other.avx2_data[1], _CMP_GT_OQ);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] > other.data[i];
                }
            #endif
            return result;
        }

        Vector operator>=(const Vector& other) const {
            Vector result;
            #ifdef __AVX512F__
                result.avx512_data = _mm512_cmp_pd_mask(avx512_data, other.avx512_data, _CMP_GE_OQ);
            #elif __AVX2__
                result.avx2_data[0] = _mm256_cmp_pd(avx2_data[0], other.avx2_data[0], _CMP_GE_OQ);
                result.avx2_data[1] = _mm256_cmp_pd(avx2_data[1], other.avx2_data[1], _CMP_GE_OQ);
            #else
                for (int i = 0; i < 8; ++i) {
                    result.data[i] = data[i] >= other.data[i];
                }
            #endif
            return result;
        }
};