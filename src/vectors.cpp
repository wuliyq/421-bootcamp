/**
 * @file vectors.cpp
 * @author Abigale Kim (abigalek)
 * @brief Tutorial code for C++ Standard Library (STL) vectors.
 */

// The C++ STL contains a container library, which is a generic collection of
// data structure and algorithm implementations that allow users to manipulate
// data structures like stacks, queues, and hash tables easily. Each container
// has its own header and usage. In the C++ standard (up to C++ 23), there are
// currently 20 containers, which is far too many to cover here well. In this
// file, we will introduce the container std::vector. The std::vector container
// is essentially a generic dynamic array (or unbounded array). We won't be
// able to cover every function in this container, but we will try to cover the
// basics of using this container.

// There is documentation on all the other functions, and other containers on
// https://en.cppreference.com/w/cpp/container. You will definitely need this
// resource as you complete the assignments in this class, so you should check
// it out!

// Includes std::cout (printing) for demo purposes.
#include <iostream>
// Includes the vector container library header.
#include <vector>

// Basic point class. (Will use later)
class Point {
public:
  Point() : x_(0), y_(0) {
    std::cout << "Default constructor for the Point class is called.\n";
  }

  Point(int x, int y) : x_(x), y_(y) {
    std::cout << "Custom constructor for the Point class is called.\n";
  }

  inline int GetX() const { return x_; }
  inline int GetY() const { return y_; }
  inline void SetX(int x) { x_ = x; }
  inline void SetY(int y) { y_ = y; }
  void PrintPoint() const {
    std::cout << "Point value is (" << x_ << ", " << y_ << ")\n";
  }

private:
  int x_;
  int y_;
};

// A utility function to print the elements of an int vector. The code for this
// should be understandable and similar to the code iterating through elements
// of a vector in the main function.
void print_int_vector(const std::vector<int> &vec) {
  for (const int &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

int main() {
  // We can declare a Point vector with the following syntax.
  std::vector<Point> point_vector;

  // It is also possible to initialize the vector via an initializer list.
  std::vector<int> int_vector = {0, 1, 2, 3, 4, 5, 6};

  // There are two functions for appending data to the back of the vector. They
  // are push_back and emplace_back. Generally, emplace_back is slightly faster,
  // since it forwards the constructor arguments to the object's constructor and
  // constructs the object in place, while push_back constructs the object, then
  // moves it to the memory in the vector. We can see this here where we add two
  // Point objects to our vector.
  std::cout << "Appending to the point_vector via push_back:\n";
  point_vector.push_back(Point(35, 36));
  std::cout << "Appending to the point_vector via emplace_back:\n";
  point_vector.emplace_back(37, 38);

  // Let's just add more items to the back of our point_vector.
  point_vector.emplace_back(39, 40);
  point_vector.emplace_back(41, 42);

  // There are many ways to iterate through a vector. For instance, we can
  // iterate through it's indices via the following for loop. Note that it is
  // good practice to use an unsigned int type for array or vector indexes.
  std::cout << "Printing the items in point_vector:\n";
  for (size_t i = 0; i < point_vector.size(); ++i) {
    point_vector[i].PrintPoint();
  }

  // We can also iterate through it via a for-each loop. Note that I use
  // references to iterate through it so that the items we iterate through are
  // the items in the original vector. If we iterate through references of the
  // vector elements, we can also modify the data in the vector.
  for (Point &item : point_vector) {
    item.SetY(445);
  }

  // Let's see if our changes went through. Note that I use the const reference
  // syntax to ensure that the data I'm accessing is read only.
  for (const Point &item : point_vector) {
    item.PrintPoint();
  }

  // int_vector was built from an initializer list above; let's print it using
  // our helper function.
  std::cout << "Printing the elements of int_vector:\n";
  print_int_vector(int_vector);

  // This file only covers the basics of std::vector. For iterators, erasing
  // elements, and a tour of the other STL containers (list, map, set, queue,
  // stack, and more), see stl_concepts.cpp. We also discuss more stylistic and
  // readable ways of iterating through STL containers in auto.cpp!

  return 0;
}
