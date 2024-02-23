/**
 * copy constructor: syntax: classname(const classname &)
 *  shallow copy: have the same address with input object
 *  deep copy: create new address and copy data of input object
 * move constructor:  "steal" the existing resources without additional allocations (of r-value reference) syntax: classname(classname &&)
 * 
 * copy assigment: input is l-value reference. return address of class after copy. syntax: classname &operator=(const classname &)
 * move assigment: input is r-value regerence. return address of class after copy. syntax: classname &operator=(const classname &&)
*/

#include <cstring>
#include <iostream>

using namespace std;

class Mystring {
private:
  char *str; // C-style string

public:
  // Default constructor
  Mystring() {
    this->str = (char *)malloc(sizeof(char));
    *(this->str) = '\0';
  }

  // Parameterized constructor
  Mystring(const char *str) {
    std::cout << "Constructor with parameter called" << std::endl;
    if (str == nullptr) {
      this->str = (char *)malloc(sizeof(char));
      *(this->str) = '\0';
    } else {
      this->str = (char *)malloc(sizeof(char) * (std::strlen(str) + 1));
      std::strcpy(this->str, str);
    }
  }

  // Destructor to free allocated memory
  ~Mystring() {
    std::cout << "Destructor called" << std::endl;
    free(this->str);
  }

  // Getter function to retrieve the C-style string
  const char *get_str() const {
    std::cout << "Size of this string is: " << std::strlen(this->str)
              << std::endl;
    return this->str;
  }

  // Copy constructor
  Mystring(const Mystring &str1) {
    std::cout << "Copy constructor called" << std::endl;
    this->str = (char *)malloc(sizeof(char) * (std::strlen(str1.str) + 1));
    std::strcpy(this->str, str1.str);
  }

  // Copy assignment
  Mystring &operator=(const Mystring &rhs) {
    std::cout << "Copy assignment called" << std::endl;
    if (this == &rhs) {
      return *this;
    }
    free(this->str);
    this->str = (char *)malloc(sizeof(char) * (std::strlen(rhs.str) + 1));
    std::strcpy(this->str, rhs.str);
    return *this;
  }

  // Move assignment
  Mystring &operator=(Mystring &&rhs) {
    std::cout << "Move assignment called" << std::endl;
    if (this == &rhs) {
      return *this;
    }
    free(this->str);
    this->str = rhs.str; // steal the pointer from rhs
    rhs.str = nullptr;
    return *this;
  }

  // Unary operator as member methods (++, --, -, !)
  /**
   * Number Number::operator-() const; a=-b;
   * Number Number::operator++(); pre-increment
   * Number Number::operator++(int); post-increment
   * bool Number::operator!() const;
   */

  // Operator -
  Mystring operator-() const {
    std::cout << "operator- is called" << std::endl;
    char *temp = (char *)malloc(sizeof(char) * (std::strlen(this->str) +
                                                1)); // allocate memory for temp
    std::strcpy(temp, this->str);                    // copy
    for (int i = 0; i < strlen(temp); i++) {
      temp[i] = std::tolower(temp[i]); // modify string
    }
    Mystring s{temp};
    free(temp);
    return s;
  }

  // Operator==
  bool operator==(const Mystring &rhs) const {
    std::cout << "operator== is called" << std::endl;
    if (std::strcmp(this->str, rhs.str) == 0) {
      return true;
    }
    return false;
  }

  // Operator+
  Mystring operator+(const Mystring &rhs) const {
    std::cout << "operator+ is called" << std::endl;
    size_t size = std::strlen(this->str) + std::strlen(rhs.str) + 1;
    char *temp = (char *)malloc(sizeof(char) * size);
    std::strcpy(temp, this->str);
    std::strcat(temp, rhs.str);
    Mystring result{temp};
    free(temp);
    return result;
  }

  // Binary operators as global functions (+,-,==,!=,<,>,etc...)
  /**
   * Number operator+(const Number &lhs, const Number &rhs);
   * Number operator-(const Number &lhs, const Number &rhs);
   * bool operator==(const Number &lhs, const Number &rhs);
   * bool operator<(const Number &lhs, const Number &rhs);
   */
  friend bool operator==(const Mystring &lhs, const Mystring &rhs);

  // Stream insertion and extraction operators (<<,>>)
    friend std::ostream &operator<<(std::ostream &os, const Mystring &rhs);
    friend std::istream &operator>>(std::ostream &in, Mystring &rhs);
};

std::ostream &operator<<(std::ostream &os, const Mystring &rhs){
    os << rhs.str;
    return os;
}

std::istream &operator>>(std::istream &in, Mystring &rhs){
    char *buff = new char[1000];
    in >> buff;
    rhs = Mystring{buff};
    delete [] buff;
    return in;
}

bool operator==(const Mystring &lhs, const Mystring &rhs) {
  std::cout << "operator== global is called" << std::endl;
  if (std::strcmp(lhs.str, rhs.str) == 0) {
    return true;
  }
  return false;
}

int main() {
  const char *b = "Hello";
  Mystring str{b}; // Constructor with parameter
  std::cout << str.get_str() << std::endl;

  Mystring cp{str}; // Copy constructor
  std::cout << cp.get_str() << std::endl;

  Mystring s1{"Frank"};
  Mystring s2 = s1; // NOT copy assignment (equal with Mystring s2{s1};)
  s2 = s1;          // Copy assignment

  Mystring s;
  s = "KAKA"; // s1.operator=("kaka"); call Constructor with parameter and then
              // call Move assignment/Copy assignment (priority move > copy)

  Mystring s2 = -s; // operator-

  std::cout << (s2 == s1) << std::endl; // operator==

  Mystring st = s1 + s2;
  std::cout << st.get_str() << std::endl;

  Mystring a{"Hello"};
  Mystring c{"Hello"};
  auto result = (a == c);
  std::cout << result << std::endl;
  // Summary: copy assignment lvalue = lvalue; move assignment lvalue = rvalue
  return 0;
}