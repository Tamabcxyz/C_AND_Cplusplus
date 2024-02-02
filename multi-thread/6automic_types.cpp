/**
 * integer operations and threads
*/
/**
 * atomic keyword
 * the compiler will generate special instructions which   
 *  disable pre-fetch for variable "count"
 *  flush the store buffer immediately after doing the increment
 * this also avoids some other problems
 *  hardware optimizations which change the instruction order
 *  compiler optimizations which change the instruction order
 * the result is that only one thread can access count at a time
 * this prevent the data race
 *  it also makes the operation take much longer
 * 
 * in the <atomic> header
 * ex: atomic<int> x= 0;
*/
// A shared variable is modified by multiple threads
// Use an "atomic" variable to prevent a data race
#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

std::atomic<int> counter = 0;

void task()
{
    for (int i = 0; i < 100'000; ++i)
        ++counter;
}

int main()
{
    std::vector<std::thread> tasks;
	
    for (int i = 0; i < 10; ++i)
        tasks.push_back(std::thread(task));
    
	for (auto& thr: tasks)
		thr.join();
    
	std::cout << counter << '\n';
}


/**
 * volatile keyword
*/
// A shared variable is modified by multiple threads
// Using a "volatile" variable does not prevent a data race
#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

volatile int counter = 0;

void task() {
    for (int i = 0; i < 100'000; ++i)
        ++counter;
}

int main() {
    std::vector<std::thread> tasks;
    for (int i = 0; i < 10; ++i)
        tasks.push_back(std::thread(task));
    for (auto& thr: tasks)
		thr.join();
    std::cout << counter << '\n';
}

/**
 * double-checked locking
 * one solution is to make the initialized object atomic
 * atomic<Test *> ptest = nullptr;
 * 
 * atomic types do not support the . or -> operators
 * we must copy to a non-atomic pointer before we can use it
 * Test *ptr = ptest;
 * ptr->func();
 * 
*/

/**
 * member functions for atomic types
 * store()
 *  atomically replace the object's value with its argument
 * 
 * load()
 *  atomically return the object's value
 * 
 * operator =()
 * operator T()
 *  synonyms for store() and load()
 * 
 * exchange()
 *  atomic replace the object's value with its argument
 *  returns the previous value
 * 
 * member functions fo specializations
 * atomic pointers support pointer arithmetic
 *  increment and decrement operators
 *  fetch_add() synonym for x++
 *  fetch_sub() synonym for x--
 *  += and -= operators
 * 
 * integer specializations have these, plus
 *  atomic bitwise logical operations &, | and ^
*/
// Demonstrate member functions of atomic types
#include <iostream>
#include <atomic>

int main()
{
	std::atomic<int> x = 0;
	std::cout << "After initialization: x = " << x << '\n';
	
	// Atomic assignment to x
	x = 2;
	
	// Atomic assignment from x. y can be non-atomic
	int y = x;
	
	std::cout << "After assignment: x = " << x << ", y = " << y << '\n';
	
	x.store(3);
	std::cout << "After store: x = " << x.load() << '\n';
	
	std::cout << "Exchange returns " << x.exchange(y) << '\n';
	std::cout << "After exchange: x = " << x << ", y = " << y << '\n';
}

/**
 * std::atomic_flag is an atomic boolean type has less overhead than std::atomic<bool>
 * only three operations
 *  clean() sets flag to false
 *  test_and_set() set flag to true and return previous value
 *  operator =()
 * must be initialized to false
 *  atomic_flag lock = ATOMIC_FLAG_INIT;
 * 
*/
//spin lock
// Use std::atomic_flag to implement a spin lock
// which protects a critical section
#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

// The atomic_flag must be initialized as false
std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void task(int n)
{
	// test_and_set()
	// Returns true if another thread set the flag
	// Returns false if this thread set the flag
	while (lock_cout.test_and_set()) {}
	
	// Start of critical section
	// do some work
	using namespace std::literals;
	std::this_thread::sleep_for(50ms);
	std::cout << "I'm a task with argument " << n << '\n';
	// End of critical section
	
	// Clear the flag, so another thread can set it
	lock_cout.clear();
}

int main()
{
	std::vector<std::thread> threads;
	
	for (int i = 1; i <= 10; ++i)
	    threads.push_back(std::thread(task, i));
	
	for (auto& thr : threads)
		thr.join();
}

// Use std::mutex to protect a critical section
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

std::mutex mut;

void task(int n) {
	std::lock_guard<std::mutex> lg(mut);
	
	// Start of critical section
	// do some work
	using namespace std::literals;
	std::this_thread::sleep_for(50ms);
	std::cout << "I'm a task with argument " << n << '\n';
	// End of critical section
}

int main() {
	std::vector<std::thread> threads;
	
	for (int i = 1; i <= 10; ++i)
	    threads.push_back(std::thread(task, i));
	
	for (auto& thr : threads)
		thr.join();
}


// Another way to solve double-checked locking
// Make the lazily-initialized variable atomic
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

class Test {
	// ...
public:
	void func() { /*...*/ }
};

std::atomic<Test*> ptest = nullptr;  // Variable to be lazily initialized
std::mutex mut;

void process()
{
	// First check of ptest
	if (!ptest) {
		std::lock_guard<std::mutex> lck_guard(mut);

		// Second check of ptest
		if (!ptest) {
			// Initialize ptest
			ptest = new Test;
		}
	}

	// Atomic pointers cannot be dereferenced
	// Copy it to a non-atomic pointer first
	Test *ptr_test = ptest;
	ptr_test->func();
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread(process));

	for (auto& thr : threads)
		thr.join();
}

// Broken implementation of lock-free queue (has data race)
#include <vector>
#include <list>
#include <thread>
#include <iostream>

template <typename T>
struct LockFreeQueue {
private:
	// Use an std::list to store the elements
	std::list<T> lst;

	// iHead and iTail iterators
	typename std::list<T>::iterator iHead, iTail;

public:
	// Class constructor
	LockFreeQueue()
	{
		// Create a "dummy" element to separate iHead from iTail
		lst.push_back(T());
		iHead = lst.begin();
		iTail = lst.end();
	}

	// Producer thread function
	void Produce(const T& t)
	{
		// Add the new element
		lst.push_back(t);

		// Update iTail
		iTail = lst.end();

		// Erase the removed elements
		lst.erase(lst.begin(), iHead);
	}

	// Consumer thread function
	bool Consume(T& t)
	{
		// Go to the first element
		auto iFirst = iHead;
		++iFirst;

		// If queue is not empty
		if (iFirst != iTail) {
			// Update iHead
			iHead = iFirst;

			// Fetch this first element
			t = *iHead;
			return true;
		}

		// No elements to fetch
		return false;
	}

	// Function to display all the elements
	void Print()
	{
		// Go to the first element
		auto head = iHead;
		++head;

		// We cannot use a range-for loop, because we only access some of the elements
		for (auto el = head; el != iTail; ++el)
			std::cout << *el << ", ";
		std::cout << '\n';
	}
}; // End of class definition

int main()
{
	LockFreeQueue<int> lfq;
	std::vector<std::thread> threads;
	int j = 1;

	for (int i = 0; i < 10; ++i) {
		// Run the member functions of LockFreeQueue in threads
		// Syntax for member function with std::thread:
		// First argument is a pointer to the member function
		// Second argument is the address of the object the member function is called on
		// (this will be the "this" pointer in the member function)
		// Then the arguments to the member function. These are passed as reference to int
		// so we need to wrap them in std::ref()
		/*
		lfq.Produce(i);
		lfq.Consume(j);
		*/

		std::thread produce(&LockFreeQueue<int>::Produce, &lfq, std::ref(i));
		threads.push_back(std::move(produce));
		std::thread consume(&LockFreeQueue<int>::Consume, &lfq, std::ref(j));
		threads.push_back(std::move(consume));
	}

	// Wait for the threads to complete
	for (auto& thr: threads)
		thr.join();

	lfq.Print();
}