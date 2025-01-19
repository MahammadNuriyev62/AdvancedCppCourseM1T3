#include <iostream>
#include <functional>

// Q3: Implement a 'set2nd' function template
template <typename F>
auto set2nd(F f) {
    return [f](auto x) {
        return f(x, 0);
    };
}

// Example usage
int main() {
    // Example two-parameter function
    auto multiply = [](int a, int b) { return a * b; };

    // Freeze the second parameter at 0
    auto multiplyWithZero = set2nd(multiply);

    std::cout << "Result: " << multiplyWithZero(5) << std::endl; // Output: 0

    return 0;
}
