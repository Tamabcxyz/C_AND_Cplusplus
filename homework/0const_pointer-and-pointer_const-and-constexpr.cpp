
#include <iostream>

int main()
{
    //Normal Constant
    const int a = 32; int b = 20; int c = 10;
    //Pointer to a Constant Integer
    const int* consPtr = &a;
    consPtr = &b; //it's ok, can be change address
    // *consPtr = 100; cannot change value of const
    std::cout << *consPtr << std::endl;
    
    //Constant Pointer to an Integer
    int* const consPtr1 = &b;
    //consPtr1 = &c; //it's not ok, const consPtr1 cannot point to another address
    *consPtr1 = 100; //it's ok, can be change the value
    std::cout << *consPtr1 << std::endl;
    std::cout << b << std::endl;
    
    //Constant Pointer to a Constant Integer
    const int* const consPtr2 = &a;
    //consPtr2 = &c; //c not a constand and const consPtr2 cannot point to another address and not change the value
    std::cout << *consPtr2 << std::endl;
    
    //Constant Reference
    int num = 42;
    // Constant reference to an integer
    const int& refNum = num;//only num can be change
    // refNum = b;//it's not ok, cannot change the address
    // refNum = 100;//it's not ok, cannot change the vallue
    return 0;
}

/**
 * constexpr is a keyword in C++ that is used to indicate that a function or variable can be evaluated at compile-time.
*/
// constexpr for Variables
#include <iostream>
using namespace std;
constexpr int size = 10;

int main() {
    int arr[size];
    return 0;
}

// constexpr for Functions
#include <iostream>
using namespace std;
constexpr int square(int x) {
    return x * x;
}

int main() {
    constexpr int result = square(5);  // Computed at compile-time
    return 0;
}

/**
 * one example for character litteral constants
 * \n
 * \r
 * \t
*/

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    for (int i = 0; i <= 10; ++i) {
        std::cout << "Progress: " << i * 10 << "%\r";//The \r (carriage return) character is used to move the cursor or insertion point to the beginning of the current line. It doesn't create a new line
        std::cout << std::flush;  // Flush the output buffer to ensure immediate display

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\nDone!\n";

    return 0;
}