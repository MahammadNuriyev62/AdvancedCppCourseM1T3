/*
  Exercise 1 - Base type

  The following program calculates the average of 10 numerical values.
  The result is then displayed.

  Q1 - Is the result correct?

  Q2 - What is the source of the error?

  Q3 - Correct the code to obtain the correct result.
  
*/

#include <iostream>

int main(int, char **) {
  double moyenne = 0.0;  // use double instead of int

  moyenne = moyenne + 3;
  moyenne = moyenne + 5;
  moyenne = moyenne + 1;
  moyenne = moyenne + 9;
  moyenne = moyenne + 4;
  moyenne = moyenne + 2;
  moyenne = moyenne + 8;
  moyenne = moyenne + 17;
  moyenne = moyenne + 9;
  moyenne = moyenne + 11;

  moyenne = moyenne / 10;  // now correct (floating-point) division
  std::cout << "La moyenne est: " << moyenne << "\n";

    return 0;
}