// Header
//     iostream : provides definitions for formatted input and output from/to
//     streams fstream : provides definitions for formatted input and output
//     from/to file streams iomanip : provides definitions for manipulators used
//     to format stream I/O

// Class
// ios : provides basic support for formatted and unformatted I/O operattions.
// Base class most other classes ifstream : provides for high-level input
// operations on file based streams ofstream : provides for high-level output
// operations on file based streams fstream : provides for high-level I/O
// operations on file based. Derived from ofstream and ifstream stringstream :
// Provided for high-level I/O operations on memory based strings. Derived from
// istringstream and ostringstream

// Global stream object (initialized before main executes)
// cin : standard input stream - by default 'connected' to the standard input
// device (keyboard) instance of istream cout : standard output stream - by
// default 'connected' to the standard output device (console) instance of
// ostream cerr : standard error stream - by default 'connected' to the standard
// error device (console) instance of ostream (unbuffered) clog : standard log
// stream - by default 'connected' to the standard log device (console) instance
// of ostream (unbuffered)

// Some method common
// std::ios::boolalpha;
// std::ios::noboolalpha;
// std::ios::showbase;
// std::ios::showpos;
// std::ios::showpoint;
// std::ios::basefield;
// std::ios::uppercase;
// std::cout.setf(std::ios::boolalpha);
// std::resetiosflags(std::ios::boolalpha);
// std::setw()
// std::setfill()
// std::left
// std::right

// Format integer types
#include <iostream>
using namespace std;

int main() {
  int num{255};
  std::cout << std::showbase; // display prefix
  std::cout << std::dec << num << std::endl;
  std::cout << std::hex << num << std::endl;
  std::cout << std::oct << num << std::endl;
  return 0;
}

// Format float types
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  double num{255.5523423434};
  std::cout << num << std::endl; // default precision is 3
  std::cout << std::fixed;       // fix default precision is 6
  std::cout << num << std::endl;
  std::cout << std::setprecision(2) << std::fixed; // set to 3
  std::cout << num << std::endl;
  return 0;
}

// Read and write file (std::ios::in, std::ios::out, std::ios::binary,
// std::ios::trunc, std::ios::app, std::ios::ate)
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;
int main() {
  std::string line;
  int a;
  float b;
  std::ifstream input{"abc.txt"};
  std::ofstream output{"abc-copy.txt"};
  // while(!input.eof()){
  //     input >> line >> a >> b;
  //     std::cout << std::setw(10) << line;
  //     std::cout << std::setw(10) << a;
  //     std::cout << std::setw(10) << b;
  // }

  while (std::getline(input, line)) {
    std::cout << line << std::endl;
    output << line;
  }

  input.close();
  output.close();
  return 0;
}