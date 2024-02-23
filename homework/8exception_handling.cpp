#include <iostream>

using namespace std;

int main() {
  int x = 5, y = 0;
  double r;
  try {
    if (y == 0) {
      throw 0; // throw int, object, ...
    }
    r = x / y;
    std::cout << r << std::endl;
  } catch (int &ex) { // catch from throw
    std::cerr << "devided by zero " << std::endl;
  }
  std::cout << "the program is continue" << std::endl;

  return 0;
}

#include <iostream>

using namespace std;
double caculate(const int &x, const int &y) {
  if (y == 0) {
    throw 0;
  }
  if (x < 0 && y < 0) {
    throw std::string("Nagative value error");
  }
  return static_cast<double>(x) / y;
}

int main() {
  int x = -5, y = -1;
  double r;

  try {
    caculate(x, y);
  } catch (int &ex) { // catch from throw
    std::cerr << "devided by zero " << std::endl;
  } catch (std::string &ex) {
    std::cerr << "Nagative value error " << std::endl;
  } catch (...) {
    std::cerr << "Any error" << std::endl;
  }
  std::cout << "the program is continue" << std::endl;

  return 0;
}

// also define own exception
#include <iostream>
using namespace std;
class DevidedByZero : public std::exception {
public:
  DevidedByZero() noexcept = default;
  ~DevidedByZero() noexcept = default;
  virtual const char *what() const noexcept { return "Devided by zero"; }
};
class NagativeValue {};
double caculate(const int &x, const int &y) {
  if (y == 0) {
    throw DevidedByZero();
  }
  if (x < 0 && y < 0) {
    throw NagativeValue();
  }
  return static_cast<double>(x) / y;
}

int main() {
  int x = -5, y = -1;
  double r;

  try {
    caculate(x, y);
  } catch (DevidedByZero &ex) { // catch from throw
    std::cout << ex.what() << std::endl;
  } catch (NagativeValue &ex) {
    std::cerr << "Nagative value error " << std::endl;
  } catch (...) {
    std::cerr << "Any error" << std::endl;
  }
  std::cout << "the program is continue" << std::endl;

  return 0;
}

// exception also throw from within a class (do not throw exception in
// destructor) std::exception is the base class, all subclasses implement the
// what() virtual function