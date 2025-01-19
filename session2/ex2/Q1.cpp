#include <iostream>
#include <functional>

// Q1: Implement a 'compose' template function

template <typename F, typename G>
auto compose(F f, G g) {
    return [f, g](auto x) {
        return f(g(x));
    };
}

// Example usage
int main() {
    auto square = [](int x) { return x * x; };
    auto increment = [](int x) { return x + 1; };

    auto squareThenIncrement = compose(increment, square);

    std::cout << "Result: " << squareThenIncrement(3) << std::endl; // Output: 10

    return 0;
}
