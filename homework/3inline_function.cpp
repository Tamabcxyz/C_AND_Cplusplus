#include <iostream>
using namespace std;
/*
    Advantages
        Performance improvement
        Reduced Function Call Overhead
        Possibility of compiler optimization
        Avoidance of Function Call Stack Overhead
    Disadvantages
        Code Bloat
        Compiler's Decision
        Increased Compilation Time
        Reduced Cache Locality
*/
inline int add_number(int a, int b) { return a + b; }

int main() {
  int result{5};
  result = add_number(result, 5);
  std::cout << result << std::endl;
  return 0;
}