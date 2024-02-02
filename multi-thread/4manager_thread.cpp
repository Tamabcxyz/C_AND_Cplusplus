/**
 * instead of calling join(), we can call detach() run in background
 * the parent thread will continue executing
 * the child thread will run until it completes
 * or the program terminates
 * annalogous to daemon process
 * When an execution thread in detached
 * the std::thread object is no longer associated with it
 * the destructor will not call std::terminate()
 *
 * Exception in parent thread
 * the destructors are called for every object in scope
 * include std::thread is destructor
 * this checks whether join() or detach() have been called
 * if neither, it calls std::terminate()
 * ==> we must call either join() or detach() before the thread is destructoyed
 *
 */

#include <iostream>
#include <stdexcept>
#include <thread>

using namespace std;
void hello() { std::cout << "func hello" << std::endl; }

int main() {
  // std::thread th(hello); //solution
  try {
    // create a thread object
    std::thread th(hello);
    // might throw an exception
    throw std::exception(); // after exception thread object which is being
                            // destroyed without join()
    th.join();
  } catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
    // th.join(); //solution //join before destructor is called
  }

  return 0; // should be move the thread object outside the try/catch block
}

/**
 * RAII solution
 * wrap the std::thread object inside a class
 * the class destructor call join() on the std::thread object
 *
 * an std::thread object can only be joined once
 *
 * the joinable() member function
 * return false
 * if join() or detach() have already been called
 * or if the thread object is not associated with a exxecution thread
 * return true if we need to call join()
 */

#include <iostream>
#include <thread>

using namespace std;
class ThreadGuard {
private:
  std::thread th;

public:
  ThreadGuard() = default;
  ThreadGuard(std::thread &&thcp) : th(std::move(thcp)) {}

  ThreadGuard(const ThreadGuard &) = delete; // delete copy constructor
  ThreadGuard &operator=(const ThreadGuard &) = delete; // delete copy
                                                        // assignment
  // destructor - join the thread if necessary
  ~ThreadGuard() {
    if (th.joinable()) {
      th.join();
    }
  }
};

void hello() { std::cout << "func hello" << std::endl; }

int main() {
  try {
    std::thread th(hello);

    ThreadGuard cth{std::move(th)};
    throw std::exception();
  } //~ThreadGuard will be call when run out of this block
  catch (std::exception &e) {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  return 0;
}

