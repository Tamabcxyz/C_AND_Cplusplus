#include <iostream>
#define STRINGIZE(x) #x
#define LOG(...) std::cout << __VA_ARGS__ << std::endl
#define DEBUG_PRINT(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)


int main() {
    
    std::cout << STRINGIZE(abcd) << std::endl; 
    std::string a{"hi"},b{"helo"};
    LOG("hello it's me");
    LOG(a);
    int x = 10;
    DEBUG_PRINT("The value of x is: %d\n", x);
    DEBUG_PRINT("The value of a is: %s\n", a.c_str());
    return 0;
}