/**
 * When you use std::enable_shared_from_this, it ensures that the object pointed to by ptr1 and ptr2 shares ownership. 
 * This means that both ptr1 and ptr2 contribute to keeping the object alive. 
 * If you were to use a direct assignment like std::shared_ptr<MyClass> ptr2 = ptr1;, both pointers would share ownership, 
 * but there would be no way for the object to obtain a shared pointer to itself from within its member functions.
*/
#include <memory>
#include <iostream>
using namespace std;
class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    std::shared_ptr<MyClass> createShared() {
        // Creating a shared_ptr from this pointer
        return shared_from_this();
    }
};

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    // std::shared_ptr<MyClass> ptr2 = ptr1->createShared();
    std::shared_ptr<MyClass> ptr2 = ptr1;
    // Both ptr1 and ptr2 share ownership of the same MyClass object
    std::cout << "addr1: " << ptr1 << std::endl;
    std::cout << "addr2: " << ptr2 << std::endl;
    ptr1.reset();
    if(ptr2){
        std::cout << "ptr2 still alive\n";
        std::cout << "addr2: " << ptr2 << std::endl;
    }
    return 0;
}
