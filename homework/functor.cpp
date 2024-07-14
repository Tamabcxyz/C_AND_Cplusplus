#include <iostream>
#include <functional>

// Functor class
class Functor {
public:
    void operator()() const {
        std::cout << "Functor called" << std::endl;
    }
};

class MyClass {
public:
    // Static member function
    static void staticMemberFunction() {
        std::cout << "Static member function called" << std::endl;
    }

    // Non-static member function
    void memberFunction() {
        std::cout << "Non-static member function called" << std::endl;
    }
};

// Free function
void freeFunction() {
    std::cout << "Free function called" << std::endl;
}

int main() {
    // Free function
    std::function<void()> func1 = freeFunction;
    func1(); // Calls freeFunction

    // Static member function
    std::function<void()> func2 = MyClass::staticMemberFunction;
    func2(); // Calls staticMemberFunction

    // Non-static member function with std::bind
    MyClass obj;
    std::function<void()> func3 = std::bind(&MyClass::memberFunction, &obj);
    func3(); // Calls obj.memberFunction

    // Non-static member function with lambda
    std::function<void()> func4 = [&obj]() { obj.memberFunction(); };
    func4(); // Calls obj.memberFunction

    // Functor
    Functor functor;
    std::function<void()> func5 = functor;
    func5(); // Calls functor.operator()

    return 0;
}


//summary: functor can assign a non-static function. if you want to assign a function of a class to function pointer have two ways
// 1. std::bind
// 2. masking function method to static member function