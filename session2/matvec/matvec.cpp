#include "matvec.hpp"

#include <iostream>
#include <cassert>

// Helper functions to print vectors and matrices:
// (For quick debugging / demonstration.)
template <typename T, std::size_t N>
void print_vec(const vec<T, N>& v, const char* label = nullptr) {
    if (label) std::cout << label << " = ";
    std::cout << "[ ";
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << v[i];
        if (i + 1 < N) std::cout << ", ";
    }
    std::cout << " ]\n";
}

template <typename T, std::size_t M, std::size_t N>
void print_mat(const mat<T, M, N>& m, const char* label = nullptr) {
    if (label) std::cout << label << " =\n";
    for (std::size_t i = 0; i < M; ++i) {
        std::cout << "  [ ";
        for (std::size_t j = 0; j < N; ++j) {
            std::cout << m(i, j);
            if (j + 1 < N) std::cout << ", ";
        }
        std::cout << " ]\n";
    }
}

// Test for dot product
void test_dot_product() {
    std::cout << "\n=== Test: dot product ===\n";
    vec<double, 3> v1 = {1.0, 2.0, 3.0};
    vec<double, 3> v2 = {4.0, 5.0, 6.0};

    double d = dot(v1, v2);
    std::cout << "dot([1,2,3], [4,5,6]) = " << d << "\n";
    assert(d == (1.0*4.0 + 2.0*5.0 + 3.0*6.0));  // 32.0
}

// Test for vector-scalar product
void test_vector_scalar() {
    std::cout << "\n=== Test: vector-scalar product ===\n";
    vec<int, 3> v = {1, 2, 3};
    int scalar = 10;

    auto v_times_scalar = v * scalar;
    std::cout << "v = [1,2,3]\n";
    std::cout << "scalar = 10\n";
    print_vec(v_times_scalar, "v * scalar");
    
    // Check correctness
    assert(v_times_scalar[0] == 10);
    assert(v_times_scalar[1] == 20);
    assert(v_times_scalar[2] == 30);

    auto scalar_times_v = scalar * v;
    print_vec(scalar_times_v, "scalar * v");

    // Should be the same
    assert(scalar_times_v[0] == v_times_scalar[0]);
    assert(scalar_times_v[1] == v_times_scalar[1]);
    assert(scalar_times_v[2] == v_times_scalar[2]);
}

// Test for dyadic product: vec * vec -> mat
void test_dyadic_product() {
    std::cout << "\n=== Test: dyadic product ===\n";
    vec<double, 2> a = {2.0, 3.0};
    vec<double, 3> b = {4.0, 5.0, 6.0};

    // a is 2D, b is 3D => result is a 2x3 matrix
    auto m = a * b; 
    std::cout << "a = [2, 3]\n";
    std::cout << "b = [4, 5, 6]\n";
    print_mat(m, "m = a*b");

    // Check some elements
    // result(0,0) = 2*4 = 8
    // result(1,2) = 3*6 = 18
    assert(m(0,0) == 8.0);
    assert(m(1,2) == 18.0);
}

// Test matrix-vector product
void test_matrix_vector_product() {
    std::cout << "\n=== Test: matrix-vector product ===\n";
    // 2x3 matrix
    mat<double, 2, 3> M = {
        1.0, 2.0, 3.0, // row 0
        4.0, 5.0, 6.0  // row 1
    };
    // 3D vector
    vec<double, 3> v = {10.0, 20.0, 30.0};

    auto result = M * v;  // Should yield a 2D vector
    std::cout << "M =\n";
    print_mat(M);
    print_vec(v, "v");
    print_vec(result, "M * v");

    // Check correctness:
    // row0 dot v = 1*10 + 2*20 + 3*30 = 10 + 40 + 90 = 140
    // row1 dot v = 4*10 + 5*20 + 6*30 = 40 + 100 + 180 = 320
    assert(result[0] == 140.0);
    assert(result[1] == 320.0);
}

// Test vector-matrix product
void test_vector_matrix_product() {
    std::cout << "\n=== Test: vector-matrix product ===\n";
    vec<double, 2> v = {2.0, 3.0};
    
    // 2x4 matrix
    mat<double, 2, 4> M = {
        1.0, 2.0, 3.0, 4.0, // row 0
        10.0, 20.0, 30.0, 40.0  // row 1
    };

    auto result = v * M;  // Should yield a 4D vector
    std::cout << "v = [2, 3]\n";
    print_mat(M, "M");
    print_vec(result, "v * M");

    // Check correctness by columns:
    // result[j] = dot( col_j(M), v ) = M(0,j)*v[0] + M(1,j)*v[1]
    // For j=0 => (1)*2 + (10)*3 = 2 + 30 = 32
    // For j=1 => (2)*2 + (20)*3 = 4 + 60 = 64
    // For j=2 => (3)*2 + (30)*3 = 6 + 90 = 96
    // For j=3 => (4)*2 + (40)*3 = 8 + 120=128
    assert(result[0] == 32.0);
    assert(result[1] == 64.0);
    assert(result[2] == 96.0);
    assert(result[3] == 128.0);
}

// Test matrix-matrix product
void test_matrix_matrix_product() {
    std::cout << "\n=== Test: matrix-matrix product ===\n";
    // M1 is 2x3
    mat<int, 2, 3> A = {
         1,  2,  3,
         4,  5,  6
    };
    // M2 is 3x2
    mat<int, 3, 2> B = {
         10, 100,
         20, 200,
         30, 300
    };

    // A (2x3) * B (3x2) = (2x2)
    auto C = A * B;

    std::cout << "A =\n";
    print_mat(A);
    std::cout << "B =\n";
    print_mat(B);
    std::cout << "C = A * B =\n";
    print_mat(C);

    // Check correctness:
    // C(0,0) = A.row(0) dot B.col(0) 
    //         = (1,2,3) dot (10,20,30) = 1*10 + 2*20 + 3*30 = 140
    // C(0,1) = A.row(0) dot B.col(1)
    //         = (1,2,3) dot (100,200,300) = 100 + 400 + 900 = 1400
    // C(1,0) = (4,5,6) dot (10,20,30) = 4*10 + 5*20 + 6*30 = 40 + 100 + 180 = 320
    // C(1,1) = (4,5,6) dot (100,200,300) = 400 + 1000 + 1800 = 3200
    assert(C(0,0) == 140);
    assert(C(0,1) == 1400);
    assert(C(1,0) == 320);
    assert(C(1,1) == 3200);
}

// Demonstrate row and col extraction
void test_row_col_extraction() {
    std::cout << "\n=== Test: row/col extraction ===\n";
    mat<int, 3, 4> M = {
        1,  2,  3,  4,
        10, 20, 30, 40,
        100,200,300,400
    };
    std::cout << "M =\n";
    print_mat(M);

    auto row1 = M.row(1);
    print_vec(row1, "row(1)");
    // row1 = [10, 20, 30, 40]

    auto col2 = M.col(2);
    print_vec(col2, "col(2)");
    // col2 = [3, 30, 300]

    // Basic checks
    assert(row1[0] == 10);
    assert(row1[1] == 20);
    assert(col2[2] == 300);
}

int main() 
{
    // Run each test separately for clarity
    test_dot_product();
    test_vector_scalar();
    test_dyadic_product();
    test_matrix_vector_product();
    test_vector_matrix_product();
    test_matrix_matrix_product();
    test_row_col_extraction();

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}
