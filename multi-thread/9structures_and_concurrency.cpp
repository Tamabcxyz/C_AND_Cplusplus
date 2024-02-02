/**
 * data structures and concurrency
 * a data structure has multiple elements
 *  multiple threads may access these elements
 *  these accesses can conflict
 *  locks or atomic operations may be needed
 * 
*/

// Conflicting operations on STL containers are not safe
// They must be synchronized
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>

// Shared vector
std::vector<int> vec;

// Mutex to protect std::vector's data
std::mutex mut;

void func1()
{
	// Potentially conflicting access - must be protected
	//std::lock_guard<std::mutex> lgd(mut);//don't have this line the program will be crash
	for (int i = 0; i < 100000; ++i)
		vec.push_back(i);
}

void func2()
{
	// Potentially conflicting access - must be protected
	//std::lock_guard<std::mutex> lgd(mut); //don't have this line the program will be crash
	for (int i = 100000; i < 200000; ++i)
		vec.push_back(i);
}

int main()
{
	std::thread thr1(func1);
	std::thread thr2(func2);

	thr1.join();
	thr2.join();

	std::cout << "shptr data: ";
	for (int i = 0; i < 200000; ++i)
		std::cout << vec[i] << ", ";

	std::cout << "Finished\n";
}

// Operations on std::shared_ptr
#include <memory>
#include <iostream>

int main()
{
	// Pass a pointer as the constructor argument
	std::shared_ptr<int> ptr1(new int(42));
	
	// Calling std::make_shared() is better
	auto ptr2 = std::make_shared<int>(42);
	
	// Can be dereferenced
	std::cout << *ptr1 << '\n';
	
	// Pointer arithmetic is not supported
	// ++ptr1;
	
	// Assignment, copying and moving are allowed
	ptr1 = ptr2;
	std::shared_ptr<int> ptr3(ptr2);
	std::shared_ptr<int> ptr4(std::move(ptr2));
	
	// Releases the allocated memory
	ptr1 = nullptr;
}

// std::shared_ptr and thread safety
// Operations which only affect the reference counter are safe
// and do not need to be synchronized
#include <memory>
#include <thread>
#include <iostream>

// std::shared_ptr has an "atomic" reference counter
std::shared_ptr<int> shptr = std::make_shared<int>(42);

void func1()
{
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp1 = shptr;
}

void func2()
{
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp2 = shptr;
}

int main()
{
	std::thread thr1(func1);
	std::thread thr2(func2);
	thr1.join();
	thr2.join();
}

// std::shared_ptr and thread safety
// Operations which affect the pointed-to data are not safe
// They must be synchronized
#include <memory>
#include <thread>
#include <iostream>
#include <mutex>

// std::shared_ptr has an "atomic" reference counter
std::shared_ptr<int> shptr = std::make_shared<int>(42);

// Mutex to protect std::shared_ptr's data
std::mutex mut;

void func1()
{
	// Potentially conflicting access - must be protected
	std::lock_guard<std::mutex> lgd(mut);
	*shptr = 5;
}

void func2()
{
	// Potentially conflicting access - must be protected
	std::lock_guard<std::mutex> lgd(mut);
	*shptr = 7;
}

int main()
{
	std::cout << "shptr data: " << *shptr << '\n';

	std::thread thr1(func1);
	std::thread thr2(func2);

	thr1.join();
	thr2.join();

	std::cout << "shptr data: " << *shptr << '\n';
}

