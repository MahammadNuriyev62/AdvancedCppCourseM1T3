/*
  Exercise 2 - String manipulation

  Q1 - Construct a string variable containing 10 '#' symbols

  Q2 - Construct a string variable containing two '#' symbols
  separated by 8 spaces

  Q3 - Using the above variables, display the following pattern:

  ##########
  #        #
  #        #
  #        #
  ##########

  Q4 - With the help of the previous code, construct a string variable
  containing this pattern and display it.
*/

#include <iostream>
#include <string>

int main(int, char **) {
  // Q1
  std::string line10(10, '#');

  // Q2
  std::string sideHash = '#' + std::string(8, ' ') + '#';

  // Q3
  std::cout 
  << line10 << "\n" 
  << sideHash << "\n" 
  << sideHash << "\n" 
  << sideHash << "\n"
  << line10 << "\n";

  // Q4
  std::string pattern = line10
  + "\n" + sideHash
  + "\n" + sideHash 
  + "\n" + sideHash 
  + "\n" + line10;

  std::cout << pattern << "\n";

  return 0;
}