/*
  Exercice 1 - Make templates great again

    Q1 - Implement a table structure that contains a static quantity of
    double in the form of a double[10]. This structure must behave
    like an array of 10 doubles. The operations to be provided are :

    - a means of constructing a table from 10 doubles
    - a size() member function that returns the size of the object (i.e. 10)
    - the appropriate operator[] overloads to access the stored elements
    - begin() and end() member functions returning a pointer to the beginning
      and end of data

  Q2 - Use templates to transform table into a structure template
  that lets you choose the type of data stored in table.

  Q3 - Use templates to transform table into a structure template
  that allows you to choose the type of data stored in table AND its quantity.

  Q4 - Discuss the case of table<double,0>; should it be handled in a special way?
*/

#include <iostream>

struct table_1_t {
  double data[10];

  // table_1_t(double a) {
  //   data[0] = 0;
  // }

  int size() { return 10; }

  double *begin() { return &data[0]; }
  double *end() { return &data[10]; }

  // double &operator[](const std::size_t i) { return data[i]; }
  double &operator[](const std::size_t i) const { return (double&) data[i]; }
};

template <typename T> struct table_2_t {
  T data[10];

  int size() { return 10; }

  T *begin() { return &data[0]; }
  T *end() { return &data[10]; }

  T &operator[](const std::size_t i) { return data[i]; }
};

template <class T, int N> struct table_3_t {
  T data[N];

  int size() { return N; }

  T *begin() { return &data[0]; }
  T *end() { return &data[N]; }

  T &operator[](const std::size_t i) { return data[i]; }
};

template <class T> struct table_3_t<T, 0> {
  int size() { return 0; }

  // Solution 1 nullptr
  // T * begin(){return nullptr;}
  // T * end(){return nullptr;}
  // T& operator[] (const std::size_t i){return reinterpret_cast<T*>(this);}

  // Solution 2 Good solution
  T *begin() { return reinterpret_cast<T *>(this); }
  T *end() { return reinterpret_cast<T *>(this); }
  T &operator[](const std::size_t i) { return reinterpret_cast<T *>(this); }

  // Solution 3 : bad solution ! Similar to std::array<T, N=0>
  // T data[1];  // avoid sizeof(table_3_t<T, 0>) == 0
  // T * begin(){return &data[0];}
  // T * end(){return &data[0];}
  // T& operator[] (const std::size_t i){return data[i];}
};

template <typename T> void print_table(T tab) {
  std::cout << "[ ";
  for (auto e : tab) {
    std::cout << e << ", ";
  }
  std::cout << " ]( size = " << tab.size() << " )\n";
}

struct empty {};

int main(int, char **) {

  table_1_t tab1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print_table(tab1);

  table_2_t<int> tab2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print_table(tab2);

  table_3_t<int, 5> tab3{1, 2, 3, 4, 5};
  print_table(tab3);

  std::cout << sizeof(table_3_t<int, 0>) << std::endl;
  std::cout << sizeof(empty) << std::endl;

  // table_3_t<table_3_t<double, 3>, 2> tabtab;
  // table_3_t<table_3_t<double, 3>, 0> tabzero;
}