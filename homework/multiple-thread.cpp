#include <iostream>
#include <string>
#include <thread>
void print(const std::string &str) {
    std::cout << "\nprint: " << str << std::endl;
}
int main()
{
    std::thread th1(print, "hi");
    std::thread th2(print,  "hello");
    if(th1.joinable())
        th1.join();
    if(th2.joinable())
        th2.join();
    return 0;
}