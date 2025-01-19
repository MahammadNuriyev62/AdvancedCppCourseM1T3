#include <iostream>
#include <functional>

// Q2: Implement a 'set1st' function template
template <typename F>
auto set1st(F f) {
    return [f](auto x) {
        return f(0, x);
    };
}

// Example usage
int main() {
    // Example two-parameter function
    auto add = [](int a, int b) { return a + b; };

    // Freeze the first parameter at 0
    auto addWithZero = set1st(add);

    std::cout << "Result: " << addWithZero(5) << std::endl; // Output: 5

    return 0;
}
