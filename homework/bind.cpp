// ===============std::bind
#include <iostream>
#include <functional>

class MyClass {
private:
    int value;

public:
    MyClass(int val) : value(val) {}

    void printValue(int val) {
        std::cout << "Value: " << val << std::endl;
    }

    void processValue(int val) {
        auto boundPrint = std::bind(&MyClass::printValue, this, std::placeholders::_1);
        boundPrint(val);
    }
};

int main() {
    MyClass obj(42);
    obj.processValue(100);
    return 0;
}

// ===============Binding a Member Function to a Specific Object
#include <iostream>
#include <functional>

class MyClass {
public:
    void print() {
        std::cout << "Hello from MyClass" << std::endl;
    }
};

int main() {
    MyClass obj1, obj2;

    // Bind the member function 'print' to obj1
    auto boundPrint1 = std::bind(&MyClass::print, &obj1);

    // Bind the member function 'print' to obj2
    auto boundPrint2 = std::bind(&MyClass::print, &obj2);

    // Call the bound functions
    boundPrint1(); // Prints "Hello from MyClass"
    boundPrint2(); // Prints "Hello from MyClass"

    return 0;
}

// ===============Creating a Function Object from a Member Function Pointer
#include <iostream>
#include <functional>

class MyClass {
public:
    void print() {
        std::cout << "Hello from MyClass" << std::endl;
    }
};

int main() {
    MyClass obj;

    // Define a member function pointer
    void (MyClass::*printPtr)() = &MyClass::print;

    // Bind the member function pointer to 'obj'
    auto boundPrint = std::bind(printPtr, &obj);

    // Call the bound function
    boundPrint(); // Prints "Hello from MyClass"

    return 0;
}

// ===============Binding Member Function with Additional Arguments
#include <iostream>
#include <functional>

class MyClass {
public:
    void print(int value) {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    MyClass obj;

    // Bind the member function 'print' to 'obj' with additional argument
    auto boundPrint = std::bind(&MyClass::print, &obj, std::placeholders::_1);

    // Call the bound function with an argument
    boundPrint(42); // Prints "Value: 42"

    return 0;
}



