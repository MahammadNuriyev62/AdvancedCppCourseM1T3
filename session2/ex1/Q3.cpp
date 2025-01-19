#include <iostream>
#include <iterator>

template <typename T, size_t N>
struct Table {
    T data[N]; // Static array of N elements of type T

    // Constructor to initialize the array
    Table(const T (&arr)[N]) {
        for (size_t i = 0; i < N; ++i) {
            data[i] = arr[i];
        }
    }

    // Returns the size of the array
    constexpr size_t size() const {
        return N;
    }

    // Overload the operator[] for accessing elements
    T& operator[](size_t index) {
        return data[index];
    }

    // begin() and end() for iterators
    T* begin() {
        return std::begin(data);
    }

    T* end() {
        return std::end(data);
    }
};

// Test the Table structure
template <typename T, size_t N>
void printTable(Table<T, N>& table) {
    for (const T& val : table) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

int main() {
    // Initialize with some data
    double initial_data[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    Table<double, 10> table(initial_data);

    // Print the data
    printTable(table);

    // Test size()
    std::cout << "Size: " << table.size() << "\n";

    // Access and modify elements
    table[2] = 42.0;
    std::cout << "Modified third element: " << table[2] << "\n";

    // Test with another type and quantity
    int int_data[5] = {1, 2, 3, 4, 5};
    Table<int, 5> int_table(int_data);

    printTable(int_table);
    std::cout << "Size: " << int_table.size() << "\n";

    return 0;
}
