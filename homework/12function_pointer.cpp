/**
 * function pointer is a variable that can store the address of a function
 */

#include <iostream>

using namespace std;

int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int performOperation(int x, int y, int (*operation)(int, int)) {
  return operation(x, y);
}

int main() {
  int (*fadd)(int, int) = add; // function pointer point to add function
  int (*fsubtract)(int, int) = subtract; // function pointer point to subtract function

  std::cout << performOperation(5, 3, fadd) << std::endl;
  std::cout << performOperation(5, 3, fsubtract) << std::endl;
  return 0;
}

//===============================================
#include <iostream>

using namespace std;
typedef void (*makePtr)();

void makeCafe() { cout << "Make cafe" << std::endl; }
void makeTea() { cout << "Make tea" << std::endl; }
void makeMilkTea() { cout << "Make milk tea" << std::endl; }
void cancelOrder() { cout << "Cancel order" << std::endl; }

int main() {
  makePtr menu[4] = {cancelOrder, makeCafe, makeTea, makeMilkTea};
  int drink;
  std::cout << "Select drink from menu: " << std::endl;
  std::cout << "0. Cancel order" << std::endl;
  std::cout << "1. Cafe" << std::endl;
  std::cout << "2. Tea" << std::endl;
  std::cout << "3. Milk tea" << std::endl;
  std::cin >> drink;
  if (drink < 4) {
    menu[drink]();
  }
  return 0;
}

// callback function is a function will call another function
#include <iostream>

using namespace std;
typedef void (*StoreFn)(const char *str);

void download(StoreFn fn) {
  std::cout << "Pretend downloading ..." << std::endl;
  const char *s = "awesome";
  fn(s);
}

void test(const char *c) { std::cout << "test: " << c << std::endl; }

int main() {
  download(test);

  return 0;
}