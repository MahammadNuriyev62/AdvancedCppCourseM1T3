#include <iostream>
#include <iterator>

struct Table {
    double data[10]; // Static array of 10 doubles

    // Constructor to initialize the array
    Table(const double (&arr)[10]) {
        for (int i = 0; i < 10; ++i) {
            data[i] = arr[i];
        }
    }

    // Returns the size of the array
    constexpr size_t size() const {
        return 10;
    }

    // Overload the operator[] for accessing elements
    double& operator[](size_t index) {
        return data[index];
    }

    // begin() and end() for iterators
    double* begin() {
        return std::begin(data);
    }

    double* end() {
        return std::end(data);
    }
};

// Test the Table structure
int main() {
    // Initialize with some data
    double initial_data[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    Table table(initial_data);

    // Print the data
    for (double val : table) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Test size()
    std::cout << "Size: " << table.size() << "\n";

    // Access and modify elements
    table[2] = 42.0;
    std::cout << "Modified third element: " << table[2] << "\n";

    return 0;
}