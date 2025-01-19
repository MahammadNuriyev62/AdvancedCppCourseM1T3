/*
  Exercice 2 - Higher-order function

  Q1 - Implement a 'compose' template function allowing you to construct
  the composition of two arbitrary one-parameter functions.

  Q2 - Implement a 'set1st' function template to construct
  from a two-parameter function, a single-parameter function
  by freezing the value of the initial function's first parameter at 0.
  So set1st(f)(x) is equivalent to f(0,x).

  Q3 - Implement a 'set2nd' function template to build
  from a two-parameter function, a single-parameter function
  by freezing the value of the initial function's second parameter at 0.
  So set2nd(f)(x) is equivalent to f(x,0).

  Q4 - Modify set1st and set2nd to let you to choose the value of the
  frozen parameter. Thus set1st(f, 8)(x) is equivalent to f(8,x)

*/

#include <functional>
#include <iostream>

// typename vs class: https://stackoverflow.com/questions/2023977/what-is-the-difference-between-typename-and-class-template-parameters

template <typename Fun1, typename Fun2> auto compose(Fun1 f, Fun2 g) {
  auto lambda = [&f, &g](auto a) { return f(g(a)); };
  return lambda;
}

template <typename Fun> auto set1st(Fun f, int x) {
  return [&f, x](int y) { return f(x, y); };
}

template <typename Fun> auto set2nd(Fun f, int y) {
  return [&f, y](int x) { return f(x, y); };
}

int main(int, char **) {
  auto f  = [](int x) { return x + 1; };
  auto g  = [](int x) { return x * 10; };
  auto fg = compose(f, g);

  std::cout << fg(2) << " = 21" << std::endl;

  std::function<int(int, int)> sum  = [](int x, int y) { return x + y; };
  std::function<int(int, int)> diff = [](int x, int y) { return x - y; };

  auto sum4       = set1st(sum, 4);
  auto four_minus = set1st(diff, 4);
  auto sum4_bis   = set2nd(sum, 4);
  auto minus4     = set2nd(diff, 4);

  std::cout << "4 + (y=2)  = " << sum4(2)       << std::endl << "===\n";
  std::cout << "(x=2) + 4  = " << sum4_bis(2)   << std::endl << "===\n";
  std::cout << "4 - (y=2)  = " << four_minus(2) << std::endl << "===\n";
  std::cout << "(x=2) - 4  = " << minus4(2)     << std::endl << "===\n";
}