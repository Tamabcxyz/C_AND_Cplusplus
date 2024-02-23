/**
 * raw pointer
 * uninitialized (wild) pointer
 * memory leaks
 * dangling pointers
 * not exception safe
 *
 * smart pointer
 * allocation
 * deallocation
 * lifetime management
 *
 * ==>smart pointer is a Object implemented using class template in c++
 * ==>can only pointe to heap-allocated memory
 * ==>automaticlly call delete when no longer needed
 * ==>adhere to RAII (Resource Acquisition Is Initialization) principles
 *
 * Unique pointer (unique_ptr)
 * Shared pointer (shared_ptr)
 * Weak pointer (weak_ptr)
 * Auto pointer (auto_ptr) ==> not use anymore
 */

#include <iostream>
#include <memory>
#include <vector>
using namespace std;
// unique pointer
// points to an object of type T on the heap
// it is unique-there can only be one unique_ptr<T> pointing to the object on
// the heap owns what it points to can not be assigned or copied can be move
// when the pointer is destroyed, what it points to is automatically destroyed

int main() {
  std::unique_ptr<int> p1{new int{100}};
  std::cout << *p1 << std::endl; // 100
  *p1 = 200;
  std::cout << *p1 << std::endl; // 200

  std::cout << p1.get() << std::endl; // return address (draw pointer)
  p1.reset();                         // p1 is now nullptr

  std::vector<std::unique_ptr<int>> vec;
  std::unique_ptr<int> ptr = std::make_unique<int>(100);
  // vec.push_back(ptr); //copy not allowed
  vec.push_back(std::move(ptr)); // can be moved
  return 0;
}

#include <iostream>
#include <memory>
#include <vector>
using namespace std;
// shared pointer
// points to an object of type T on the heap
// it is not unique-there can many shared_ptr pointing to the same object on the
// heap establishes shared ownership relationship can be assigned and copied can
// be moved doesn't support managing arrays by default when the use count is
// zero, the managed object on the heap is destroyed

int main() {
  std::shared_ptr<int> p1{new int{100}};
  std::cout << p1.use_count() << std::endl; // 1

  std::shared_ptr<int> p2{p1};
  std::cout << p1.use_count() << std::endl; // 2
  std::cout << p2.use_count() << std::endl; // 2

  p1.reset();
  std::cout << p1.use_count() << std::endl; // 0
  std::cout << p2.use_count() << std::endl; // 1

  std::shared_ptr<int> ptr = std::make_shared<int>(100);

  return 0;
}

#include <iostream>
#include <memory>
using namespace std;
// weak pointer
//  points to an object of type T on the heap
//  does not participate in owning relationship
//  always created from a shared_ptr
//  does not increment or decrement reference use_count
//  used to prevent strong reference cycles which could prevent objects from
//  being deleted
class B; // forward declaration
class A {
private:
  std::shared_ptr<B> b_ptr;

public:
  void set_B(std::shared_ptr<B> &b) { b_ptr = b; }
  A() { std::cout << "construct A call" << std::endl; }
  ~A() { std::cout << "destruct A call" << std::endl; }
};

class B {
private:
  std::weak_ptr<A> a_ptr; // if using shared_ptr in here the destructor never
                          // call only use weak_ptr to break the cycles
public:
  void set_A(std::shared_ptr<A> &a) { a_ptr = a; }
  B() { std::cout << "construct B call" << std::endl; }
  ~B() { std::cout << "destruct B call" << std::endl; }
};
int main() {
  std::shared_ptr<A> a = std::make_shared<A>();
  std::shared_ptr<B> b = std::make_shared<B>();
  a->set_B(b);
  b->set_A(a);
  return 0;
}

#include <iostream>
#include <memory>
using namespace std;
// custom delete smart pointer
// functions
// lambdas
// others
class Test {
private:
  int value;

public:
  Test() { std::cout << "Test constructor" << std::endl; }
  Test(int x) : value{x} {
    std::cout << "Test constructor with arg" << std::endl;
  }
  ~Test() { std::cout << "Test destructor" << std::endl; }
};

int main() {
  std::shared_ptr<Test> ptr_test(new Test{100}, [](Test *ptr_test) {
    std::cout << "custom delete" << std::endl;
    delete ptr_test;
  });
  return 0;
}
