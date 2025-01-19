#pragma once

#include <array>
#include <cstddef>

// -------------------------------------------------------------
// Throughout this assignment, please implement convincing tests
// to verify that your program is running as it should.
// (in the main.cpp function)

// You can either use the cmake, or compile and run with :
// g++ matvec.cpp -o matvec -O3 -std=c++17 -Wall -Wextra && ./matvec
// (g++ can be replaced by the name or path of your favourite compiler)
// -------------------------------------------------------------

// Type vec(tor)
// A fixed-size vector storing data in a std::array.

template <typename T, std::size_t N> 
struct vec {
    // Internal storage using std::array
    std::array<T, N> data;

    // Non-const operator[] for element access
    T& operator[](std::size_t i) {
        return data[i];
    }

    // Const operator[] for element access
    const T& operator[](std::size_t i) const {
        return data[i];
    }

    // Returns the fixed size of the vector
    std::size_t size() const {
        return N;
    }
};


// Type mat(rix)
// A fixed-size matrix storing data in a single std::array (row-major order).

template <typename T, std::size_t M, std::size_t N> 
struct mat {
    std::array<T, M*N> data;

    // Number of rows
    std::size_t m() const { 
        return M; 
    }
    
    // Number of columns
    std::size_t n() const { 
        return N; 
    }

    // Non-const element access by (row, col)
    T& operator()(std::size_t i, std::size_t j) {
        return data[i * N + j];
    }

    // Const element access by (row, col)
    const T& operator()(std::size_t i, std::size_t j) const {
        return data[i * N + j];
    }

    // Extract a column j as a vec<T, M>
    vec<T, M> col(std::size_t j) const {
        vec<T, M> result{};
        for(std::size_t i = 0; i < M; ++i) {
            result[i] = (*this)(i,j);
        }
        return result;
    }

    // Extract a row i as a vec<T, N>
    vec<T, N> row(std::size_t i) const {
        vec<T, N> result{};
        for(std::size_t j = 0; j < N; ++j) {
            result[j] = (*this)(i,j);
        }
        return result;
    }
};


// Dot product between two vectors
template <typename T, std::size_t N>
T dot(const vec<T,N>& v1, const vec<T,N>& v2) {
    T sum = T{};  // Initialize sum to zero/default
    for(std::size_t i = 0; i < N; ++i) {
        sum += v1[i] * v2[i];
    }
    return sum;
}


// Dyadic product: vec * vec -> mat
// result(i, j) = u[i] * v[j].
template <typename T, std::size_t M, std::size_t N>
mat<T, M, N> operator*(const vec<T, M>& u, const vec<T, N>& v) {
    mat<T, M, N> result{};
    for(std::size_t i = 0; i < M; ++i) {
        for(std::size_t j = 0; j < N; ++j) {
            result(i, j) = u[i] * v[j];
        }
    }
    return result;
}


// Vector-scalar product
// v * scalar
template <typename T, std::size_t N>
vec<T, N> operator*(const vec<T, N>& v, const T& scalar) {
    vec<T, N> result{};
    for(std::size_t i = 0; i < N; ++i) {
        result[i] = v[i] * scalar;
    }
    return result;
}

// scalar * v
template <typename T, std::size_t N>
vec<T, N> operator*(const T& scalar, const vec<T, N>& v) {
    return v * scalar;  // reuse the previous operator
}


// Matrix-vector product
// (M x N) * (N) = (M)
template <typename T, std::size_t M, std::size_t N>
vec<T, M> operator*(const mat<T, M, N>& m, const vec<T, N>& v) {
    vec<T, M> result{};
    for(std::size_t i = 0; i < M; ++i) {
        result[i] = dot(m.row(i), v);
    }
    return result;
}


// Vector-matrix product
// (M) * (M x N) = (N)
template<typename T, std::size_t M, std::size_t N>
vec<T, N> operator*(const vec<T, M>& v, const mat<T, M, N>& m) {
    vec<T, N> result{};
    for(std::size_t j = 0; j < N; ++j) {
        result[j] = dot(m.col(j), v);
    }
    return result;
}


// Matrix-matrix product
// (M x N) * (N x P) = (M x P)
template<typename T, std::size_t M, std::size_t N, std::size_t P>
mat<T, M, P> operator*(const mat<T, M, N>& m1, const mat<T, N, P>& m2) {
    mat<T, M, P> result{};
    for(std::size_t i = 0; i < M; ++i) {
        for(std::size_t j = 0; j < P; ++j) {
            // Dot the i-th row of m1 with the j-th column of m2
            result(i, j) = dot(m1.row(i), m2.col(j));
        }
    }
    return result;
}

