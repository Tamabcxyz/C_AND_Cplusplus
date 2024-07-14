/**
 * std::forward 
*/
#include <iostream>
#include <utility>

// Function that forwards its arguments to another function
template<typename Func, typename... Args>
void forward_to_function(Func&& func, Args&&... args) {
    // Forwarding arguments to another function
    std::forward<Func>(func)(std::forward<Args>(args)...);
}

// Sample function that prints its arguments
void print_args(int &a, const std::string& str) {
    std::cout << "Arguments: " << a << ", " << str << std::endl;
    a++;
}

int main() {
    int num = 10;
    std::string text = "Hello";

    // Calling the forwarding function
    forward_to_function(print_args, num, text);
    
    std::cout << num;

    return 0;
}

#include <utility>
#include <iostream>
using namespace std;

void foo(int& x) {
    // Do something with x
    x++;
}

void foo(int&& x) {
    // Do something with x
}

template<typename T>
void forwarder(T&& arg) {
    foo(std::forward<T>(arg));
}

int main() {
    int x = 42;
    forwarder(x);   // arg is an lvalue reference
    std::cout << x << std::endl;
    forwarder(123); // arg is an rvalue reference
    return 0;
}
