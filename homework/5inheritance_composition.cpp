/**
 * 1. Inheritance is an "is-a" relationship between classes, It's allow a class
(child class) to inherit properties and behaviror from another class (parent
class)
 * class Animal {
    public:
        void eat() {
            std::cout << "Animal is eating" << std::endl;
        }
    };

    class Dog : public Animal {
    public:
        void bark() {
            std::cout << "Dog is barking" << std::endl;
        }
    };

* 2. Composition is a "has-a" relationship between classes. It involves creating
objects of one class within another class, allowing the use of their
functionalities.
class Engine { public: void start() { std::cout << "Engine
started" << std::endl;
        }
    };

    class Car {
    private:
        Engine carEngine; //composition

    public:
        void drive() {
            carEngine.start();
            std::cout << "Car is driving" << std::endl;
        }
    };

*/

#include <iostream>
using namespace std;
class Base {
public:
  int a;
  Base() : a{0} { std::cout << "Base no-args constructor" << std::endl; }
  Base(int x) : a{x} {
    std::cout << "Base int overloaded constructor" << std::endl;
  }
  Base(const Base &other) : a{other.a} {
    std::cout << "Base copy constructor call" << std::endl;
  }
  Base &operator=(const Base &rhs) {
    std::cout << "Base copy assignment call" << std::endl;
    if (this != &rhs) {
      this->a = rhs.a;
    }
    return *this;
  }
  ~Base() { std::cout << "Base destructor" << std::endl; }

protected:
  int b;

private:
  int c;
};

class Derived : public Base {
public:
  int value;
  Derived() : Base{}, value{0} { // implicit call Base constructor no-args
    std::cout << "Derived no-args constructor" << std::endl;
  }
  Derived(int x)
      : Base{x}, value{x} { // implicit call Base overloaded constructor 
    std::cout << "Derived int overloaded constructor" << std::endl;
  }
  Derived(const Derived &other) : Base{other}, value{other.value} {
    std::cout << "Derived copy constructor call" << std::endl;
  }
  Derived &operator=(const Derived &rhs) {
    std::cout << "Derived copy assignment call" << std::endl;
    if (this != &rhs) {
      Base::operator=(rhs);
      value = rhs.value;
    }
    return *this;
  }
  void change() {
    a = 10; // OK
    b = 20; // OK
    //   c = 30; //error can not access to private
  }
  ~Derived() { std::cout << "Derived destructor" << std::endl; }
};

int main() {
  Base b;
  b.a = 10;
  // b.b = 20; //error can not access to protected

  Derived d{1};
  return 0;
}
#include <iostream>

// Base class
class MyBaseClass {
protected:
  int protectedVariable;

public:
  MyBaseClass(int value) : protectedVariable(value) {}

  void showProtected() {
    std::cout << "Protected variable in MyBaseClass: " << protectedVariable
              << std::endl;
  }
};

// Derived class
class MyDerivedClass : public MyBaseClass {
private:
  int value;

public:
  MyDerivedClass(int valuei) : MyBaseClass{valuei}, value{valuei} {}

  void accessProtected() {
    protectedVariable = 100;
    std::cout << protectedVariable;
  }
};

int main() {
  // Creating an object of the derived class
  MyDerivedClass derivedObj(42);

  // Accessing the protected member through a public function of the base class
  derivedObj.showProtected();

  // Accessing the protected member directly from the derived class
  derivedObj.accessProtected();

  return 0;
}

#include <iostream>
using namespace std;
class Base {
public:
  void func() { std::cout << "base func\n"; }

protected:
  int b;

private:
  int c;
};

class Derived : public Base {
public:
  void func() { std::cout << "derive func\n"; }
};

int main() {
  Base *b = new Derived;
  b->func();//base func called because donnot have virtual,  so will call at compile time
  return 0;
}