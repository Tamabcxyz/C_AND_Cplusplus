#include <iostream>
#include <thread>

using namespace std;

void hello(int i) {
  std::this_thread::sleep_for(std::chrono::seconds(i));
  std::cout << "hello: " << i << endl;
}

int main() {
  std::thread t1(hello, 1);
  std::thread t2(hello, 2);
  std::thread t3(hello, 3);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}

#include <iostream>
#include <thread>

using namespace std;

// this function make race condition
void hello(std::string str) {
  for (int i = 0; i < 5; i++) {
    std::cout << str[0] << str[1] << str[2] << endl;
  }
}

int main() {
  std::thread t1(hello, "abc");
  std::thread t2(hello, "def");
  std::thread t3(hello, "ghi");

  t1.join();
  t2.join();
  t3.join();

  return 0;
}

// to resolve that using mutex
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mx;

void hello(std::string str) {
  for (int i = 0; i < 5; i++) {
    mx.lock(); // lock the mutex before the critical section
    std::cout << str[0] << str[1] << str[2] << endl;
    mx.unlock(); // unlock the mutex after the critical section
  }
}

int main() {
  std::thread t1(hello, "abc");
  std::thread t2(hello, "def");
  std::thread t3(hello, "ghi");

  t1.join();
  t2.join();
  t3.join();

  return 0;
}

/**
 * std::mutex::try_lock() return imediately
 * return true if it locked the mutex
 * return false if it could not lock the mutex
 *
 */

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mx;

// this function make race condition
void hello(std::string str) {
  for (int i = 0; i < 5; i++) {
    try {
      mx.lock(); // lock the mutex before the critical section
      std::cout << str[0] << str[1] << str[2] << endl;
      throw std::exception(); // try to throw exception before the mutex unlock
      mx.unlock();            // never call
    } catch (std::exception &e) {
      std::cout << "debug: " << e.what() << std::endl;
    }
  }
}

int main() {
  std::thread t1(hello, "abc");
  std::thread t2(hello, "def");
  std::thread t3(hello, "ghi");

  t1.join();
  t2.join();
  t3.join();
  // ==> program hang out mutex can't call unlock to another thread access
  // resouce, t2,t3 wait
  return 0;
}

// to resolve that using std::lock_guard
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mx;

// this function make race condition
void hello(std::string str) {
  for (int i = 0; i < 5; i++) {
    try {
      std::lock_guard<std::mutex> lg(mx);
      std::cout << str[0] << str[1] << str[2] << endl;
      throw std::exception(); // try to throw exception before the mutex unlock
    }                         // call ~std::lock_guard
    catch (std::exception &e) {
      std::cout << "debug: " << e.what() << std::endl;
    }
  }
}

int main() {
  std::thread t1(hello, "abc");
  std::thread t2(hello, "def");
  std::thread t3(hello, "ghi");

  t1.join();
  t2.join();
  t3.join();

  return 0;
}

// using unique_lock insted of lock_guard
/**
 * std::try_to_lock
 *  + call the mutex's try_lock() member function
 *  + the owns_lock() member function checks if the mutex is locked
 * std::defer_lock
 *  + does not lock the mutex
 *  + can lock it later by calling the lock() member function
 *  + or by passing the std::unique_lock object to std::lock()
 * std::adopt_lock
 *  + takes a mutex that is already locked
 *  + avoids locking the mutex twice
 *
 * a std::unique_lock object can not be copied. it can be moved
 */

std::unique_lock<std::mutex> myLock(myMutex, std::try_to_lock);
if (myLock.owns_lock()) {
    // Lock was successfully acquired
} else {
    // Lock could not be acquired
}

std::unique_lock<std::mutex> myLock(myMutex, std::defer_lock);
// ... some other operations ...
myLock.lock();  // Now, explicitly lock the mutex when needed

std::unique_lock<std::mutex> myLock(myMutex, std::adopt_lock);
// The mutex is assumed to be already locked by the current thread

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mx;

void hello(std::string str) {
  for (int i = 0; i < 5; i++) {
    try {
      std::unique_lock<std::mutex> lg(mx);
      std::cout << str[0] << str[1] << str[2] << endl;
    } // call ~std::unique_lock
    catch (std::exception &e) {
      std::cout << "debug: " << e.what() << std::endl;
    }
  }
}

int main() {
  std::thread t1(hello, "abc");
  std::thread t2(hello, "def");
  std::thread t3(hello, "ghi");

  t1.join();
  t2.join();
  t3.join();

  return 0;
}

/**
 * std::unique_lock vs std::lock_guard
 * std::unique_lock is much more flexible, but
 *  +requires slightly storage
 *  +is slightly slower
 * recommendations
 * use lock_guard to lock a mutex for an entire scope
 * use unique_lock if you need to unlock within the scope
 * use unique_lock if you need the extra features
 */

/**
 * std::recursive_mutex
 * its lock() member function can be called repeatedly
 *  without calling unlock() first
 *  for each lock() call, there must enventually be an unlock() call
 * Normally a sign of bad design
 */

#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex myMutex;

void recursiveFunction(int depth) {
    std::unique_lock<std::recursive_mutex> lock(myMutex);
    std::cout << "Depth: " << depth << " - Thread ID: " << std::this_thread::get_id() << " - Locked" << std::endl;

    if (depth > 0) {
        recursiveFunction(depth - 1);
    }

    // The lock will be automatically released when 'lock' goes out of scope
    std::cout << "Depth: " << depth << " - Thread ID: " << std::this_thread::get_id() << " - Unlocked" << std::endl;
}

int main() {
    std::thread t1(recursiveFunction, 3);
    std::thread t2(recursiveFunction, 2);

    t1.join();
    t2.join();
    //In this example, recursiveFunction is a recursive function that locks the std::recursive_mutex and calls itself with a reduced depth. Since std::recursive_mutex allows multiple locks from the same thread, this won't lead to a deadlock.
    return 0;
}


/**
 * std::timed_mutex
 * similar to std::mutex, but with extra member functions
 * try_lock_for() ==> keep trying to lock the mutex for a specified duration
 * try_lock_util() ==> keep trying to lock the mutex until specified time
 * these return bool: true if the mutex was locked otherwise false
 *
 * Threre is an std::recursive_timed_mutex has the same member function
 * lock(), try_lock(), try_lock_for(), try_lock_until()
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::timed_mutex the_mutex;

void task1() {
  std::cout << "task1 trying to lock the mutex\n";
  the_mutex.lock();
  std::cout << "task1 locks the mutex\n";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  the_mutex.unlock();
  std::cout << "task1 unlocking the mutex\n";
}

void task2() {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "task2 trying to lock the mutex\n";
  while (!the_mutex.try_lock_for(std::chrono::seconds(1))) {
    // return false
    std::cout << "task2 could not lock the mutex\n";
    // try again on the next interation
  }
  // return true the mutex now can lock
  std::cout << "task2 has locked the mutex\n";
  the_mutex.unlock();
  std::cout << "task2 unlocking the mutex\n";
}

int main() {
  std::thread t1(task1);
  std::thread t2(task2);
  t1.join();
  t2.join();
  return 0;
}

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::timed_mutex the_mutex;

void task1() {
  std::cout << "task1 trying to lock the mutex\n";
  the_mutex.lock();
  std::cout << "task1 locks the mutex\n";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  the_mutex.unlock();
  std::cout << "task1 unlocking the mutex\n";
}

void task2() {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "task2 trying to lock the mutex\n";
  auto dealine =
      std::chrono::system_clock::now() + std::chrono::milliseconds(900);
  while (!the_mutex.try_lock_until(dealine)) {
    // return false
    std::cout << "task2 could not lock the mutex\n";
    // update dealine and try again
    dealine = std::chrono::system_clock::now() + std::chrono::milliseconds(900);
    // try again on the next interation
  }
  // return true the mutex now can lock
  std::cout << "task2 has locked the mutex\n";
  the_mutex.unlock();
  std::cout << "task2 unlocking the mutex\n";
}

int main() {
  std::thread t1(task1);
  std::thread t2(task2);
  t1.join();
  t2.join();
  return 0;
}

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::timed_mutex the_mutex;

void task1() {
  std::cout << "task1 trying to lock the mutex\n";
  std::lock_guard<std::timed_mutex> lck_guard(the_mutex);
  std::cout << "task1 locks the mutex\n";
  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << "task1 unlocking the mutex\n";
}

void task2() {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "task2 trying to lock the mutex\n";
  std::unique_lock<std::timed_mutex> uniq_lck(
      the_mutex, std::defer_lock); // defer_lock because we do not want the
                                   // constructor to lock the mutex
  while (!uniq_lck.try_lock_for(std::chrono::seconds(1))) {
    // return false
    std::cout << "task2 could not lock the mutex\n";
    // try again on the next interation
  }
  // return true the mutex now can lock
  std::cout << "task2 has locked the mutex\n";
  std::cout << "task2 unlocking the mutex\n";
}

int main() {
  std::thread t1(task1);
  std::thread t2(task2);
  t1.join();
  t2.join();
  return 0;
}

/**
 * multiple reader, single writer
 *
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
std::mutex mx;
int x = 0;

void read() {
  std::lock_guard<std::mutex> lg(mx);
  // start of critical section
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // end of critical section
}

void write() {
  std::lock_guard<std::mutex> lg(mx);
  // start of critical section
  ++x;
  // end of critical section
}

int main() {
  std::vector<std::thread> threads;
  for (int i = 0; i < 20; i++) {
    threads.push_back(std::thread(read));
  }
  threads.push_back(std::thread(write));
  threads.push_back(std::thread(write));
  for (int i = 0; i < 20; i++) {
    threads.push_back(std::thread(read));
  }
  for (auto &t : threads) {
    t.join();
  }
  return 0;
}

/**
 * std::shared_mutex is defined in <shared_mutex> . it can be locked in two
 * different ways 
 * - exclusive lock no other thread may acquire a lock no other
 * thread can enter a critical section 
 * - shared lock other threads may acquire a
 * shared lock they can execute critical sections concurrently
 *
 * std::lock_guard<std::shared_mutex>
 * std::unique_lock<std::shared_mutex>
 */
// c++17
#include <chrono>
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

using namespace std;
std::shared_mutex sm;
int x = 0;

void read() {
  std::shared_lock<std::shared_mutex> sl(sm);
  // start of critical section
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // end of critical section
}

void write() {
  std::lock_guard<std::shared_mutex> lg(sm);
  // start of critical section
  ++x;
  // end of critical section
}

int main() {
  std::vector<std::thread> threads;
  for (int i = 0; i < 20; i++) {
    threads.push_back(std::thread(read));
  }
  threads.push_back(std::thread(write));
  threads.push_back(std::thread(write));
  for (int i = 0; i < 20; i++) {
    threads.push_back(std::thread(read));
  }
  for (auto &t : threads) {
    t.join();
  }
  return 0;
}

/**
 * std::shared_mutex member fucntion
 * exclusive locking
 *  lock()
 *  try_lock()
 *  unlock()
 * shared locking
 *  lock_shared()
 *  try_lock_shared()
 *  unlock_shared()
 */

/**
 * pros and cons of std::shared_mutex
 * uses more memory than std::mutex
 * slower than std::mutex
 * Best suited to situations where reader threads greatly outnumber writer
 * threads, read operations take a long time
 */

#include <iostream>
#include <thread>
#include <vector>

class Singleton {
  // Pointer to unique instance
  static Singleton *single;

  // The constructor is private
  Singleton() { std::cout << "Initializing Singleton" << std::endl; }

public:
  // The copy and move operators are deleted
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton &operator=(Singleton &&) = delete;

  // Static member function to obtain the Singleton object
  static Singleton *get_Singleton();
};

// Static member function to obtain the Singleton object
Singleton *Singleton::get_Singleton() {
  if (single == nullptr)
    single = new Singleton;
  return single;
}

Singleton *Singleton::single = nullptr;

void task() {
  Singleton *single = Singleton::get_Singleton();
  std::cout << single << std::endl;
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; ++i)
    threads.push_back(std::thread(task));

  for (auto &thr : threads)
    thr.join();
}
// if using pointer and run mutiple threads the instance can be wrong we can
// using mutext to fix it

#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;
class Singleton {
private:
  static Singleton *instance; // common resources
  static std::mutex mutex_;   // for solve the problem in thread
  std::string name;
  Singleton(){}; // have to put in private to prevent call and created instance
  Singleton(std::string value) : name{value} {};

public:
  Singleton(Singleton &) = delete;            // need to delete copy constructor
  Singleton *operator=(Singleton &) = delete; // need to delete copy assignment
  static Singleton *
  getSingletonInstance(std::string value); // function static to get instance
  std::string getName();
};

Singleton *Singleton::getSingletonInstance(std::string value) {
  if (instance == nullptr) {
    std::lock_guard<std::mutex> lock(
        mutex_); // to make sure one instance created
    if (instance == nullptr) {
      instance = new Singleton(value);
    }
  }
  return instance;
}
string Singleton::getName() { return name; }

Singleton *Singleton::instance = nullptr; // have to initial in global
mutex Singleton::mutex_;

void task(const std::string &str) {
  Singleton *instance = Singleton::getSingletonInstance(str);
  std::cout << instance->getName() << std::endl;
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; ++i)
    threads.push_back(std::thread(task, "Bi"));
  threads.push_back(std::thread(task, "Bob"));

  for (auto &thr : threads)
    thr.join();
  return 0;
}

/**
 * thread-local variables
 */

#include <iostream>
#include <random>
#include <thread>

using namespace std;
// thread-local random number engine, Each thread that accesses it gets its own copy.
thread_local std::mt19937 mt;
// std::mt19937 mt; // if don't have thread_local random of two thread will have
// different values
// ensures that each thread generates the same sequence
void func() {
  std::uniform_int_distribution<int> dist(0, 10); // doubles in the range 0 to 1
  for (int i = 0; i < 10; i++) {
    std::cout << dist(mt) << std::endl;
  }
}

int main() {
  cout << "thread 1's random value\n";
  std::thread th1(func);
  th1.join();
  cout << "thread 2's random value\n";
  std::thread th2(func);
  th2.join();
  // two thread generates with the same random numbers
  return 0;
}

/**
 * double-checked locking
 */

// Lazy initialization (multi-threaded)
// Uses std::call_once()
#include <iostream>
#include <mutex>
#include <thread>

class Test {
public:
  Test() { std::cout << "Test constructor called\n"; }

  void func() { std::cout << "func call\n"; }
};

Test *ptest = nullptr; // Variable to be lazily initialized

std::once_flag ptest_flag; // The flag stores synchronization data

void process() {
  // Pass a callable object which performs the initialization
  std::call_once(ptest_flag, []() { ptest = new Test; });
  ptest->func();
}

int main() {
  std::thread thr1(process);
  std::thread thr2(process);
  thr1.join();
  thr2.join();
  /**
   * This pattern is useful when you want to ensure that an expensive initialization operation is performed only once, regardless of how many threads attempt to access the shared resource concurrently.
  */
}

// Lazy initialization (multi-threaded)
// Uses Meyers singleton
#include <iostream>
#include <mutex>
#include <thread>

class Test {
  // ...
public:
  Test() { std::cout << "Test constructor called\n"; }

  void func() { std::cout << "func call\n"; }
};

void process() {
  static Test ptest; // Variable which is lazily initialized (one time)
  ptest.func();
}

int main() {
  std::thread thr1(process);
  std::thread thr2(process);
  thr1.join();
  thr2.join();
}

/**
 * conclusion
 * four way to do thread-safe initialization
 *  naive use of a mutex
 *  use std::call_once()
 *  double checked locking with c++ 17 compiler or later
 *  meyers singleton with static local variable
 *
 * recommendations
 *  use meyers singleton, if ptest is not required outside the function
 *  otherwise, use std::call_once()
 */

/**
 * deadlock
 */
// code demo deadlock
//  Mutual deadlock
//  Two threads wait for the other to unlock a mutex
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA() {
  std::cout << "Thread A trying to lock mutex 1...\n";
  std::lock_guard<std::mutex> lck_guard(mut1); // Acquire lock on mut1
  std::cout << "Thread A has locked mutex 1\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread A trying to lock mutex 2...\n";
  std::lock_guard<std::mutex> lck_guard2(mut2); // Wait for lock on mut2
  std::cout << "Thread A has locked mutex 2\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread A releases all its locks\n";
}

void funcB() {
  std::cout << "Thread B trying to lock mutex 2...\n";
  std::lock_guard<std::mutex> lck_guard1(mut2); // Acquire lock on mut2
  std::cout << "Thread B has locked mutex 2\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread B trying to lock mutex 1...\n";
  std::lock_guard<std::mutex> lck_guard2(mut1); // Wait for lock on mut1
  std::cout << "Thread B has locked mutex 1\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread B releases all its locks\n";
}

int main() {
  std::thread thrA(funcA);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// solution for deadlock code above two function lock mutex one first
// Avoid deadlock by writing the threads
// so that they lock the mutexes in the same order
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA() {
  std::cout << "Thread A trying to lock mutex 1...\n";
  std::lock_guard<std::mutex> lck_guard(mut1); // Acquire lock on mut1
  std::cout << "Thread A has locked mutex 1\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread A trying to lock mutex 2...\n";
  std::lock_guard<std::mutex> lck_guard2(mut2); // Wait for lock on mut2
  std::cout << "Thread A has locked mutex 2\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread A releases all its locks\n";
}

void funcB() {
  std::cout << "Thread B trying to lock mutex 1...\n";
  std::lock_guard<std::mutex> lck_guard1(mut1); // Acquire lock on mut1
  std::cout << "Thread B has locked mutex 1\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread B trying to lock mutex 2...\n";
  std::lock_guard<std::mutex> lck_guard2(mut2); // Wait for lock on mut2
  std::cout << "Thread B has locked mutex 2\n";
  std::this_thread::sleep_for(50ms); // Do some work
  std::cout << "Thread B releases all its locks\n";
}

int main() {
  std::thread thrA(funcA);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// Dining philosophers problem (part 1)
//
// 5 philosophers sit at a round table which has 5 forks on it.
// A philosopher has a fork at each side of them.
// A philosopher can only eat if they can pick up both forks.
// If a philosopher picks up the fork on their right,
// that prevents the next philosopher from picking up their left fork.
//
// All the philosophers pick up their left fork at the same time
// They wait to pick up their right fork (which is also their neighbour's left
// fork) Their neighbour is waiting to pick up their own right fork All the
// philosophers are waiting for their neighbour
//
// The philosophers are blocked indefinitely.
// Deadlock
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std::literals;

// Some data about the problem
constexpr int nforks = 5;
constexpr int nphilosophers = nforks;
std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

// Keep track of how many times a philosopher is able to eat
int mouthfuls[nphilosophers] = {0};

// A philosopher who has not picked up both forks is thinking
constexpr auto think_time = 2s;

// A philosopher has picked up both forks is eating
constexpr auto eat_time = 1s;

// A philosopher who has picked up one fork will put it down again
// if they cannot pick up the other fork they need
constexpr auto time_out = think_time;

// A mutex prevents more than one philosopher picking up the same fork
// A philosopher thread can only pick up a fork if it can lock the corresponding
// mutex
std::mutex fork_mutex[nforks];

// Mutex to protect output
std::mutex print_mutex;

// Functions to display information about the 'nth' philosopher

// Interactions with a fork
void print(int n, const std::string &str, int forkno) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << forkno << '\n';
}

// The philosopher's state
void print(int n, const std::string &str) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << '\n';
}

// Thread which represents a dining philosopher
void dine(int phil_no) {
  // Philosopher A has fork 0 on their left
  // and fork 1 on their right
  // Philosopher B has fork 1 on their left
  // and fork 2 on their right
  // ...
  // Philosopher E has fork 4 on their left
  // and fork 0 on their right
  //
  // Each philosopher must pick up their left fork first
  int lfork = phil_no;
  int rfork = (phil_no + 1) % nforks;

  print(phil_no, "\'s left fork is number ", lfork);
  print(phil_no, "\'s right fork is number ", rfork);
  print(phil_no, " is thinking...");

  std::this_thread::sleep_for(think_time);

  // Make an attempt to eat
  print(phil_no, " reaches for fork number ", lfork);

  // Try to pick up the left fork
  fork_mutex[lfork].lock();
  print(phil_no, " picks up fork ", lfork);
  print(phil_no, " is thinking...");

  // Succeeded - now try to pick up the right fork
  std::this_thread::sleep_for(think_time);

  print(phil_no, " reaches for fork number ", rfork);

  fork_mutex[rfork].lock();

  // Succeeded - this philosopher can now eat
  print(phil_no, " picks up fork ", rfork);
  print(phil_no, " is eating...");

  std::this_thread::sleep_for(eat_time);

  print(phil_no, " puts down fork ", lfork);
  print(phil_no, " puts down fork ", rfork);
  print(phil_no, " is thinking...");

  fork_mutex[lfork].unlock();
  fork_mutex[rfork].unlock();
  std::this_thread::sleep_for(think_time);
}

int main() {
  // Start a separate thread for each philosopher
  std::vector<std::thread> philos;

  for (int i = 0; i < nphilosophers; ++i) {
    philos.push_back(std::move(std::thread{dine, i}));
  }

  for (auto &philo : philos)
    philo.join();

  // How many times were the philosophers able to eat?
  for (int i = 0; i < nphilosophers; ++i) {
    std::cout << "Philosopher " << names[i];
    std::cout << " had " << mouthfuls[i] << " mouthfuls\n";
  }
}

/**
 * std::scoped_lock can lock more than one mutex at the same time
 */
// Use std::scoped_lock to avoid deadlock
// All the mutexes are locked in a single operation
// Requires C++17 compiler
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA() {
  std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
  std::scoped_lock scoped_lck(mut1, mut2);
  std::cout << "Thread A has locked mutexes 1 and 2\n";
  std::this_thread::sleep_for(50ms);
  std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB() {
  std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
  std::scoped_lock scoped_lck(mut2, mut1);
  std::cout << "Thread B has locked mutexes 2 and 1\n";
  std::this_thread::sleep_for(50ms);
  std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main() {
  std::thread thrA(funcA);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// Use std::adopt_lock to avoid deadlock
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA() {
  std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
  std::lock(mut1, mut2); // Lock both mutexes
  std::cout << "Thread A has locked mutexes 1 and 2\n";

  // Adopt the locks
  std::unique_lock<std::mutex> uniq_lk1(
      mut1, std::adopt_lock); // Associate each mutex
  std::unique_lock<std::mutex> uniq_lk2(mut2,
                                        std::adopt_lock); // with a unique_lock
  std::cout << "Thread A has adopted the locks\n";

  std::this_thread::sleep_for(50ms);
  std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB() {
  std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
  lock(mut2, mut1); // Lock both mutexes
  std::cout << "Thread B has locked mutexes 2 and 1\n";

  // Adopt the locks
  std::unique_lock<std::mutex> uniq_lk2(mut2,
                                        std::adopt_lock); // with a unique_lock
  std::unique_lock<std::mutex> uniq_lk1(
      mut1, std::adopt_lock); // Associate each mutex
  std::cout << "Thread B has adopted the locks\n";

  std::this_thread::sleep_for(50ms);
  std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main() {
  std::thread thrA(funcA);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// Use std::defer_lock to avoid deadlock
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA() {
  std::unique_lock<std::mutex> uniq_lk1(
      mut1, std::defer_lock); // Associate mutex with lock...
  std::unique_lock<std::mutex> uniq_lk2(
      mut2, std::defer_lock); // ...but don’t lock it yet

  std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
  std::lock(uniq_lk1, uniq_lk2); // Now lock both of them
  std::cout << "Thread A has locked mutexes 1 and 2\n";
  std::this_thread::sleep_for(50ms);
  std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB() {
  std::unique_lock<std::mutex> uniq_lk2(
      mut2, std::defer_lock); // Associate mutex with lock...
  std::unique_lock<std::mutex> uniq_lk1(
      mut1, std::defer_lock); // ...but don’t lock it yet

  std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
  std::lock(uniq_lk2, uniq_lk1); // Now lock both of them
  std::cout << "Thread B has locked mutexes 2 and 1\n";
  std::this_thread::sleep_for(50ms);
  std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main() {
  std::thread thrA(funcA);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// Use std::defer_lock to avoid deadlock
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA() {
  std::unique_lock<std::mutex> uniq_lk1(
      mut1, std::defer_lock); // Associate mutex with lock...
  std::unique_lock<std::mutex> uniq_lk2(
      mut2, std::defer_lock); // ...but don’t lock it yet

  std::cout << "Thread A trying to lock mutexes 1 and 2...\n";

  // Now lock both of them
  auto idx = std::try_lock(uniq_lk1, uniq_lk2);
  if (idx != -1) {
    std::cout << "try_lock failed on mutex with index " << idx << '\n';
  } else {
    std::cout << "Thread A has locked mutexes 1 and 2\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread A releasing mutexes 1 and 2...\n";
  }
}

void funcB() {
  std::unique_lock<std::mutex> uniq_lk2(
      mut2, std::defer_lock); // Associate mutex with lock...
  std::unique_lock<std::mutex> uniq_lk1(
      mut1, std::defer_lock); // ...but don’t lock it yet

  std::cout << "Thread B trying to lock mutexes 2 and 1...\n";

  // Now lock both of them
  auto idx = std::try_lock(uniq_lk2, uniq_lk1);
  if (idx != -1) {
    std::cout << "try_lock failed on mutex with index " << idx << '\n';
  } else {
    std::cout << "Thread B has locked mutexes 2 and 1\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread B releasing mutexes 2 and 1...\n";
  }
}

int main() {
  std::thread thrA(funcA);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// Dining philosophers problem (part 2a)
//
// 5 philosophers sit at a round table which has 5 forks on it.
// A philosopher has a fork at each side of them.
// A philosopher can only eat if they can pick up both forks.
// If a philosopher picks up the fork on their right,
// that prevents the next philosopher from picking up their left fork.
//
// The philosophers try to pick up both forks at the same time.
// If they succeed, they can eat.
// If not, both forks are available to their neighbours.
//
// All philosophers are able to eat.
// No deadlock
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std::literals;

// Some data about the problem
constexpr int nforks = 5;
constexpr int nphilosophers = nforks;
std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

// Keep track of how many times a philosopher is able to eat
int mouthfuls[nphilosophers] = {0};

// A philosopher who has not picked up both forks is thinking
constexpr auto think_time = 2s;

// A philosopher has picked up both forks is eating
constexpr auto eat_time = 1s;

// A philosopher who has picked up one fork will put it down again
// if they cannot pick up the other fork they need
constexpr auto time_out = think_time;

// A mutex prevents more than one philosopher picking up the same fork
// A philosopher thread can only pick up a fork if it can lock the corresponding
// mutex
std::mutex fork_mutex[nforks];

// Mutex to protect output
std::mutex print_mutex;

// Functions to display information about the 'nth' philosopher

// Interactions with forks
void print(int n, const std::string &str, int lfork, int rfork) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str;
  std::cout << lfork << " and " << rfork << '\n';
}

// The philosopher's state
void print(int n, const std::string &str) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << '\n';
}

// Thread which represents a dining philosopher
void dine(int phil_no) {
  // Philosopher A has fork 0 on their left
  // and fork 1 on their right
  // Philosopher B has fork 1 on their left
  // and fork 2 on their right
  // ...
  // Philosopher E has fork 4 on their left
  // and fork 0 on their right
  //
  // Each philosopher must pick up their left fork first
  int lfork = phil_no;
  int rfork = (phil_no + 1) % nforks;

  print(phil_no, "\'s forks are ", lfork, rfork);
  print(phil_no, " is thinking...");

  std::this_thread::sleep_for(think_time);

  // Make an attempt to eat
  print(phil_no, " reaches for forks ", lfork, rfork);

  // Try to pick up both forks
  std::lock(fork_mutex[lfork], fork_mutex[rfork]);
  print(phil_no, " picks up fork ", lfork, rfork);

  // Succeeded - this philosopher can now eat
  print(phil_no, " is eating...");
  ++mouthfuls[phil_no];

  std::this_thread::sleep_for(eat_time);

  print(phil_no, " puts down fork ", lfork, rfork);
  print(phil_no, " is thinking...");

  fork_mutex[lfork].unlock();
  fork_mutex[rfork].unlock();
  std::this_thread::sleep_for(think_time);
}

int main() {
  // Start a separate thread for each philosopher
  std::vector<std::thread> philos;

  for (int i = 0; i < nphilosophers; ++i) {
    philos.push_back(std::move(std::thread{dine, i}));
  }

  for (auto &philo : philos)
    philo.join();

  // How many times were the philosophers able to eat?
  for (int i = 0; i < nphilosophers; ++i) {
    std::cout << "Philosopher " << names[i];
    std::cout << " had " << mouthfuls[i] << " mouthful\n";
  }
}

// Dining philosophers problem (part 2b)
//
// 5 philosophers sit at a round table which has 5 forks on it.
// A philosopher has a fork at each side of them.
// A philosopher can only eat if they can pick up both forks.
// If a philosopher picks up the fork on their right,
// that prevents the next philosopher from picking up their left fork.
//
// Each philosopher tries to pick up their lowest numbered fork first.
// For philosopher E, this leaves their right fork free. This breaks
// the deadlock and allows philosopher D to eat, followed by the others.
//
// All philosophers are able to eat.
// No deadlock
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std::literals;

// Some data about the problem
constexpr int nforks = 5;
constexpr int nphilosophers = nforks;
std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

// Keep track of how many times a philosopher is able to eat
int mouthfuls[nphilosophers] = {0};

// A philosopher who has not picked up both forks is thinking
constexpr auto think_time = 2s;

// A philosopher has picked up both forks is eating
constexpr auto eat_time = 1s;

// A philosopher who has picked up one fork will put it down again
// if they cannot pick up the other fork they need
constexpr auto time_out = think_time;

// A mutex prevents more than one philosopher picking up the same fork
// A philosopher thread can only pick up a fork if it can lock the corresponding
// mutex
std::mutex fork_mutex[nforks];

// Mutex to protect output
std::mutex print_mutex;

// Functions to display information about the 'nth' philosopher

// Interactions with forks
void print(int n, const std::string &str, int lfork, int rfork) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str;
  std::cout << lfork << " and " << rfork << '\n';
}

// Interactions with a fork
void print(int n, const std::string &str, int forkno) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << forkno << '\n';
}

// The philosopher's state
void print(int n, const std::string &str) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << '\n';
}

// Thread which represents a dining philosopher
void dine(int phil_no) {
  // Philosopher A has fork 0 on their left
  // and fork 1 on their right
  // Philosopher B has fork 1 on their left
  // and fork 2 on their right
  // ...
  // Philosopher E has fork 4 on their left
  // and fork 0 on their right
  //
  // Each philosopher must pick up their left fork first
  int lfork = phil_no;
  int rfork = (phil_no + 1) % nforks;

  if (lfork > rfork) {
    std::swap(lfork, rfork);
  }

  print(phil_no, "\'s forks are ", lfork, rfork);
  print(phil_no, " is thinking...");

  std::this_thread::sleep_for(think_time);

  // Make an attempt to eat
  print(phil_no, " reaches for fork number ", lfork);

  // Try to pick up the left fork
  fork_mutex[lfork].lock();
  print(phil_no, " picks up fork ", lfork);
  print(phil_no, " is thinking...");

  // Succeeded - now try to pick up the right fork
  std::this_thread::sleep_for(think_time);

  print(phil_no, " reaches for fork number ", rfork);

  fork_mutex[rfork].lock();

  // Succeeded - this philosopher can now eat
  print(phil_no, " picks up fork ", rfork);
  print(phil_no, " is eating...");
  ++mouthfuls[phil_no];

  std::this_thread::sleep_for(eat_time);

  print(phil_no, " puts down fork ", lfork);
  print(phil_no, " puts down fork ", rfork);
  print(phil_no, " is thinking...");

  fork_mutex[lfork].unlock();
  fork_mutex[rfork].unlock();
  std::this_thread::sleep_for(think_time);
}

int main() {
  // Start a separate thread for each philosopher
  std::vector<std::thread> philos;

  for (int i = 0; i < nphilosophers; ++i) {
    philos.push_back(std::move(std::thread{dine, i}));
  }

  for (auto &philo : philos)
    philo.join();

  // How many times were the philosophers able to eat?
  for (int i = 0; i < nphilosophers; ++i) {
    std::cout << "Philosopher " << names[i];
    std::cout << " had " << mouthfuls[i] << " mouthful\n";
  }
}

// Livelock caused by poorly implemented deadlock avoidance
// If the thread cannot get a lock, sleep and try again
// However, all the threads wake up at the same time
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std::literals;

std::mutex mut1, mut2;

void funcA() {
  std::this_thread::sleep_for(10ms);
  bool locked = false;
  while (!locked) {
    std::lock_guard<std::mutex> lck_guard(mut1); // Lock mut1
    std::cout << "After you, Claude!\n";
    std::this_thread::sleep_for(2s);
    locked = mut2.try_lock(); // Try to lock mut2
  }
  if (locked)
    std::cout << "ThreadA has locked both mutexes\n";
}

void funcB() {
  bool locked = false;
  while (!locked) {
    std::lock_guard<std::mutex> lk(mut2); // Lock mut2
    std::cout << "After you, Cecil!\n";
    std::this_thread::sleep_for(2s);
    locked = mut1.try_lock(); // Try to lock mut1
  }
  if (locked)
    std::cout << "ThreadB has locked both mutexes\n";
}

int main() {
  std::thread thrA(funcA);
  std::this_thread::sleep_for(10ms);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// std::shared_lock and std::lock() avoid deadlock
// when locking multiple mutexes. They also avoid livelock.
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std::literals;

std::mutex mut1, mut2;

void funcA() {
  std::this_thread::sleep_for(10ms);

  std::cout << "After you, Claude!" << std::endl;
  std::scoped_lock scoped_lck(mut1, mut2); // Lock both mutexes
  std::this_thread::sleep_for(2s);
  std::cout << "Thread A has locked both mutexes\n";
}

void funcB() {
  std::cout << "After you, Cecil!\n";
  std::scoped_lock scoped_lck(mut2, mut1); // Lock mutexes
  std::this_thread::sleep_for(2s);
  std::cout << "Thread B has locked both mutexes\n";
}

int main() {
  std::thread thrA(funcA);
  std::this_thread::sleep_for(10ms);
  std::thread thrB(funcB);

  thrA.join();
  thrB.join();
}

// Dining philosophers problem (part 3)
//
// 5 philosophers sit at a round table which has 5 forks on it.
// A philosopher has a fork at each side of them.
// A philosopher can only eat if they can pick up both forks.
// If a philosopher picks up the fork on their right,
// that prevents the next philosopher from picking up their left fork.
//
// All the philosophers pick up their left fork at the same time
// They wait to pick up their right fork (which is also their neighbour's left
// fork) If a philosopher cannot pick up the right fork, they put down the left
// fork and go back to thinking.
//
// If all the philosophers pick up their left fork at the same time,
// and put it down at the same time, they will still not be able to eat.
// Livelock
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std::literals;

// Some data about the problem
constexpr int nforks = 5;
constexpr int nphilosophers = nforks;
std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

// Keep track of how many times a philosopher is able to eat
int mouthfuls[nphilosophers] = {0};

// A philosopher who has not picked up both forks is thinking
constexpr auto think_time = 2s;

// A philosopher has picked up both forks is eating
constexpr auto eat_time = 1s;

// A philosopher who has picked up one fork will put it down again
// if they cannot pick up the other fork they need
constexpr auto time_out = think_time;

// A mutex prevents more than one philosopher picking up the same fork
// A philosopher thread can only pick up a fork if it can lock the corresponding
// mutex
std::mutex fork_mutex[nforks];

// Mutex to protect output
std::mutex print_mutex;

// Functions to display information about the 'nth' philosopher

// Interactions with a fork
void print(int n, const std::string &str, int forkno) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << forkno << '\n';
}

// The philosopher's state
void print(int n, const std::string &str) {
  std::lock_guard<std::mutex> print_lock(print_mutex);
  std::cout << "Philosopher " << names[n] << str << '\n';
}

// Thread which represents a dining philosopher
void dine(int phil_no) {
  // Philosopher A has fork 0 on their left
  // and fork 1 on their right
  // Philosopher B has fork 1 on their left
  // and fork 2 on their right
  // ...
  // Philosopher E has fork 4 on their left
  // and fork 0 on their right
  //
  // Each philosopher must pick up their left fork first
  int lfork = phil_no;
  int rfork = (phil_no + 1) % nforks;

  print(phil_no, "\'s left fork is number ", lfork);
  print(phil_no, "\'s right fork is number ", rfork);
  print(phil_no, " is thinking...");

  std::this_thread::sleep_for(think_time);

  // Make an attempt to eat
  print(phil_no, " reaches for fork number ", lfork);

  // Try to pick up the left fork
  bool locked = false;

  while (!locked) {
    fork_mutex[lfork].lock();
    print(phil_no, " picks up fork ", lfork);
    print(phil_no, " is thinking...");

    // Succeeded - now try to pick up the right fork
    std::this_thread::sleep_for(think_time);
    print(phil_no, " reaches for fork number ", rfork);

    locked = fork_mutex[rfork].try_lock();

    if (!locked) {
      print(phil_no, " puts down fork ", lfork);
      std::this_thread::sleep_for(think_time);
      fork_mutex[lfork].unlock();
    }
  }

  // Succeeded - this philosopher can now eat
  print(phil_no, " picks up fork ", rfork);
  print(phil_no, " is eating...");
  ++mouthfuls[phil_no];

  std::this_thread::sleep_for(eat_time);

  print(phil_no, " puts down fork ", lfork);
  print(phil_no, " puts down fork ", rfork);
  print(phil_no, " is thinking...");

  fork_mutex[lfork].unlock();
  fork_mutex[rfork].unlock();
  std::this_thread::sleep_for(think_time);
}

int main() {
  // Start a separate thread for each philosopher
  std::vector<std::thread> philos;

  for (int i = 0; i < nphilosophers; ++i) {
    philos.push_back(std::move(std::thread{dine, i}));
  }

  for (auto &philo : philos)
    philo.join();

  // How many times were the philosophers able to eat?
  for (int i = 0; i < nphilosophers; ++i) {
    std::cout << "Philosopher " << names[i];
    std::cout << " had " << mouthfuls[i] << " mouthful(s)\n";
  }
}

/**
 * conclusion
 * basic mutex class (std::mutex)
 * mutex wrappers (std::lock_guard and std::unique_lock)
 * mutexes and time out (std::timed_mutex, std::unique_lock)
 * shared mutexes (std::shared_mutex, std::shared_lock)
 * static and thread-local data
 * deadlock
 * deadlock avoidance (std::scoped_lock, std::lock())
 * livelock and livelock avoidance
 */
