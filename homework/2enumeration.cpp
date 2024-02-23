/**
 * enum-key enum-name : enumerator-type {};
 *
 * cannot compare two oject type enum
 */

enum { Red, Green, Blue };
//   0     1       2    implicit initialization

enum { Red = 1, Green = 2, Blue = 3 }; // explicit initialization
enum { Red = 1, Green, Blue };         // explicit/implicit initialization

enum { Red, Green, Blue };          // underlying type: int
enum { Red, Green, Blue = -32000 }; // underlying type: long

enum : uint8_t { Red, Green, Blue };   // underlying type: unsigned 8 bit int
enum : long long { Red, Green, Blue }; // underlying type: long long

// ==>should declare like this
enum Color : uint8_t { Red = 1, Green = 2, Blue = 3 };

#include <iostream>
#include <type_traits>
enum Color1 : int { Red = 1, Green = 2, Blue = 3 };

enum class Color2 : int { Red = 1, Green = 2, Blue = 3 };

int main() {

  std::cout << Color1::Red << std::endl;
  std::cout << static_cast<std::underlying_type<Color2>::type>(
      Color2::Red); // cannot print because Color2 is enum class

  return 0;
}

#include <iostream>

enum Color : uint8_t { Red = 1, Green = 2, Blue = 3 };

std::istream &operator>>(std::istream &is, Color &color) {
  std::underlying_type<Color>::type
      user_input; // Specify the underlying type explicitly
  is >> user_input;
  switch (user_input) {
  case Red:
  case Green:
  case Blue: {
    color = static_cast<Color>(user_input);
    break;
  }
  default: {
    color = Color::Red;
  }
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, const Color &c) {
  switch (c) {
  case Color::Red: {
    os << "Red";
    break;
  }
  case Color::Green: {
    os << "Green";
    break;
  }
  case Color::Blue: {
    os << "Blue";
    break;
  }
  }
  return os;
}

int main() {
  Color c;
  std::cin >> c;
  std::cout << c << std::endl;
  return 0;
}