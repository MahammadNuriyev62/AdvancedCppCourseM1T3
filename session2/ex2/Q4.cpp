#include <iostream>
#include <functional>

// Q4: Modify set1st and set2nd to let you choose the value of the frozen parameter

template <typename F>
auto set1st(F f, auto fixedValue) {
    return [f, fixedValue](auto x) {
        return f(fixedValue, x);
    };
}

template <typename F>
auto set2nd(F f, auto fixedValue) {
    return [f, fixedValue](auto x) {
        return f(x, fixedValue);
    };
}

// Example usage
int main() {
    // Example two-parameter function
    auto add = [](int a, int b) { return a + b; };

    // Freeze the first parameter at 8
    auto addWithEightFirst = set1st(add, 8);
    std::cout << "Result of set1st: " << addWithEightFirst(5) << std::endl; // Output: 13

    // Freeze the second parameter at 10
    auto addWithTenSecond = set2nd(add, 10);
    std::cout << "Result of set2nd: " << addWithTenSecond(5) << std::endl; // Output: 15

    return 0;
}
