/**
 * synchronous: wait for each task to complete
 * asynchronous: continue without waiting for task to complete
 */

/**
 * std::packaged_task
 * defined in <future>
 * encapsulates a task
 *  a callable object for the task's code
 *  an std::promise for the result of the task
 * provides a higher level of abstraction
 * ex: std::packaged_task<int(int, int)> ptask(...);
 *
 * Apply:
 * create a container of packaged_task object
 *  the threads do not start up until we are ready for them
 * useful for managing threads
 *  each task can be run on a specified thread
 *  thread scheduler runs threads in a certain order
 *  thread pool consists of threads waiting for work to arrive
 */

// Packaged task example
// Executes the task in the current thread
#include <chrono>
#include <future>
#include <iostream>

using namespace std::literals;

int main() {
  // Packaged task object
  // The callable object is a lambda expression
  // It takes int and int arguments
  // It returns int
  std::packaged_task<int(int, int)> ptask([](int a, int b) {
    std::this_thread::sleep_for(2s);
    return a + b;
  });

  // The promise object is an std::promise<int>
  // Get the future associated with it
  std::future<int> fut = ptask.get_future();

  // Invoke the packaged task in this thread
  ptask(6, 7);

  std::cout << "Waiting for result\n"; // to check main thread wait or not

  // Call get() to receive the result of the packaged task
  std::cout << "6 + 7 is " << fut.get() << '\n';

  //==>main thread wait 2s to display "Waiting for result" ==> synchronous
}

// Packaged task example
// Executes the task in a new thread
#include <chrono>
#include <future>
#include <iostream>

using namespace std::literals;

int main() {
  // Packaged task object
  // The callable object is a lambda expression
  // It takes int and int arguments
  // It returns int
  std::packaged_task<int(int, int)> ptask([](int a, int b) {
    std::this_thread::sleep_for(2s);
    return a + b;
  });

  // The promise object is an std::promise<int>
  // Get the future associated with it
  auto fut = ptask.get_future();

  // Start a new thread
  // The packaged task will be its entry point
  std::thread thr(std::move(ptask), 6, 7);

  std::cout << "Waiting for result\n"; // to check main thread wait or not

  std::cout << "6 + 7 is " << fut.get() << '\n';

  thr.join();

  //==>main thread display "Waiting for result" ==> asynchronous
}

/**
 * async function (std::async())
 * defined in <future>
 * higher-leve abstraction than std::thread
 *  we can execute a task with std::async() which runs in the background
 *  this allow us to do other work while the task is running
 *  alternatively, it can run synchronously in the same thread
 * similar syntax to std::thread's constructor
 *  the task function is the first argument
 *  followed by the argument to task function
 * std::async() return an std::future object contain the result of the task
 * also support throw exception
 */
// Hello world using std::async()
#include <future>
#include <iostream>

// Task function
void hello() { std::cout << "Hello, Async!\n"; }

int main() {
  // Call std::async() to perform the task
  std::async(hello);
}

// How to get a result from a task executed by std::async()
// Yet another bad Fibonacci implementation!
#include <chrono>
#include <future>
#include <iostream>

// Task which returns a value
unsigned long long fibonacci(unsigned long long n) {
  if (n <= 1)
    return 1;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  std::cout << "Calling fibonacci(44)\n";

  // Call async() and store the returned future
  auto result = std::async(fibonacci, 44);

  // Do some other work
  bool finished = false;

  using namespace std::literals;
  while (result.wait_for(1s) != std::future_status::ready) {
    std::cout << "Waiting for the result...\n";
  }

  // Call get() when we are ready
  std::cout << result.get() << std::endl;
}

// A task started by std::async() throws an exception
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

// Task which returns a value
int produce() {
  int x = 42;

  using namespace std::literals;
  std::this_thread::sleep_for(2s);

  // Some code which may throw an exception
  if (1) {
    throw std::out_of_range("Oops");
  }

  std::cout << "Produce returning " << x << '\n';
  return x;
}

int main() {
  // Call async() and store the returned future
  auto result = std::async(produce);

  // Get the result - may throw an exception
  std::cout << "Future calling get()...\n";
  try {
    int x = result.get(); // Get the result
    std::cout << "Future returns from calling get()\n";
    std::cout << "The answer is " << x << '\n';
  } catch (std::exception &e) {
    std::cout << "Exception caught: " << e.what() << '\n';
  }
}

/**
 * std::async() and lauch options
 * launch flags
 * std::launch::async
 *  a new thread is started for the task
 *  the task is executed as soon as the thread starts
 * std::launch::deferred
 *  nothing happens until get() is called on the returned future
 *  the task is then executed
 * if both flags are set
 *  the implementation decides whether to start a new thread
 *  this is the default
 */

// async_launch_options.cc
// The different launch options for std::async()
#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;

int task() {
  std::cout << "Executing task() in thread with ID: ";
  std::cout << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(5s);
  std::cout << "Returning from task()\n";
  return 42;
}

void func(const std::string &option = "default"s) {
  std::future<int> result;

  if (option == "async"s)
    result = std::async(std::launch::async, task);
  else if (option == "deferred"s)
    result = std::async(std::launch::deferred, task);
  else
    result = std::async(task);

  std::cout << "Calling async with option \"" << option << "\"\n";
  std::this_thread::sleep_for(2s);
  std::cout << "Calling get()\n";
  std::cout << "Task result: " << result.get() << '\n';
}

int main() {
  std::cout << "In main thread with ID: " << std::this_thread::get_id() << '\n';

  func("async");
  func("deferred");
  func("default");
}

/**
 * return value from wait() and friends
 * wait() return nothing
 * wait_for() and wait_util() return:
 *  std::future_status::ready if the result is available
 *  std::future_status::timeout if the timeout has expired
 *  std::future_status::deferred if the result is being lazily evaluated
 * in lazy evaluation, the task does not run until get() is called
 */

/**
 * choosing a thread object
 * we now have three different ways to execute a stask
 *  create an std::thread object
 *  create an std::packaged_task object
 *  call std::async()
 */

/**
 * advantages of std::async()
 *
 * the simplest way to execute a task
 *  easy to obtain the return value from a task
 *  or to catch any exception thrown in the task
 *  choice of running the task synchronously or asynchronously
 * higher-level abstraction than std::thread
 *  the library managers the threads for the programmer
 *  and the inter-thread communication
 *  no need to use shared data
 *
 * disavantages of std::async()
 *
 * can not detach tasks
 * a task executed with std::launch::async is "implicitly joined"
 * the returned future's destructor will block until the task complete
 */
// async_future_destructor.cc
// The destructor for std::async() will block
// if launched with std::launch::async
#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;

void task() {
  std::this_thread::sleep_for(5s);
  std::cout << "Task result: " << 42 << '\n';
}

void func() {
  std::cout << "Calling async\n";
  auto result = std::async(std::launch::async,
                           task); // will block until the task complete
}

int main() {
  func();
  std::cout << "Task started\n";
}

/**
 * advantages of std::packaged_task
 *
 * the best choice if we want to represent tasks as objects
 *  e.g. to create a container of tasks
 * a lower-level abstraction than std::async()
 *  can control when a task is executed
 *  can control on which thread it is executed
 */

/**
 * advantages of std::thread
 *
 * the most flexible
 *  allows access to the underlying software thread
 *  useful for features not supported by standard c++
 *  can be detached
 */

/**
 * conclusion
 *
 * for starting a new thread in general use std::async()
 * for containers of thread object use std::packeged_task
 * for starting a detachable thread use std::thread
 */