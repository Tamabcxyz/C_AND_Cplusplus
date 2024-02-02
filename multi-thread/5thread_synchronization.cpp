/**
 * coordination between workers
 * Assumsion:
 * worker A is writing a document
 * worker A needs an image that worker B is producing
 * worker A cannot continue until worker B has finished
 *
 * Solution:
 * have a manager coordinates the two workers
 * worker B tells the manager when they have finished
 * the manager tells worker A to resume work
 * B is working
 * A is waiting
 * B finished their work
 * B tells manager
 * Manager tells A to resume
 * A resume work
 *
 * Apply: A program which is performing a download
 *  one thread fetches the data over the network
 *  another thread display a progress bar
 *  a third thread will process the data when download is complete
 *
 * Strategies:
 * the threads run concurrently
 *  the data fetching thread runs continually
 *  the progress bar thread waits for information
 *  the processor thread waits until all the data has been received
 * when the download is complete
 *  the fetching thread terminates
 *  the progress bar thread terminates
 *  the processor thread runs
 */

// Simulation of a program which performs a download
//
// One thread featches the data
// Another thread displays a progress bar
// A third thread processes the data when the download is complete
//
// Implemented using bools to communicate between the threads
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std::literals;

// Shared variable for the data being fetched
std::string sdata;

// Flags for thread communication
bool update_progress = false;
bool completed = false;

// Mutexes to protect the shared variables
std::mutex data_mutex;
std::mutex completed_mutex;

// Data fetching thread
void fetch_data() {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Fetcher thread waiting for data..." << std::endl;
    std::this_thread::sleep_for(2s);

    // Update sdata, then notify the progress bar thread
    std::lock_guard<std::mutex> data_lck(data_mutex);
    sdata += "Block" + std::to_string(i + 1);
    std::cout << "sdata: " << sdata << std::endl;
    update_progress = true;
  }

  std::cout << "Fetch sdata has ended\n";

  // Tell the progress bar thread to exit
  // and wake up the processing thread
  std::lock_guard<std::mutex> completed_lck(completed_mutex);
  completed = true;
}

// Progress bar thread
void progress_bar() {
  size_t len = 0;

  while (true) {
    std::cout << "Progress bar thread waiting for data..." << std::endl;

    // Wait until there is some new data to display
    std::unique_lock<std::mutex> data_lck(data_mutex);
    while (!update_progress) {
      data_lck.unlock();
      std::this_thread::sleep_for(10ms);
      data_lck.lock();
    }

    // Wake up and use the new value
    len = sdata.size();

    // Set the flag back to false
    update_progress = false;
    data_lck.unlock();

    std::cout << "Received " << len << " bytes so far" << std::endl;

    // Terminate when the download has finished
    std::lock_guard<std::mutex> completed_lck(completed_mutex);
    if (completed) {
      std::cout << "Progress bar thread has ended" << std::endl;
      break;
    }
  }
}

void process_data() {
  std::cout << "Processing thread waiting for data..." << std::endl;

  // Wait until the download is complete
  std::unique_lock<std::mutex> completed_lck(completed_mutex); // Acquire lock

  while (!completed) {
    completed_lck.unlock();
    std::this_thread::sleep_for(10ms);
    completed_lck.lock();
  }

  completed_lck.unlock();

  std::lock_guard<std::mutex> data_lck(data_mutex);
  std::cout << "Processing sdata: " << sdata << std::endl;

  // Process the data...
}

int main() {
  // Start the threads
  std::thread fetcher(fetch_data);
  std::thread prog(progress_bar);
  std::thread processor(process_data);

  fetcher.join();
  prog.join();
  processor.join();
}

/**
 * condition variables (std::condition_variable)
 * defined in <condition_variable>
 * wait()
 *  takes an argument of type std::unique_lock
 *  it unlocks its argument and blocks the thread until a notification is
 * received wait_for() and wait_util() re-lock their argument if a notification
 * is not received in time notify_one() wake up one of the waiting threads the
 * scheduler decides which thread is woken up notify_all() wake up all the
 * waiting threads
 *
 * Scenario:
 * thread A locks the mutex
 *  it calls the condition variable's wait() member function
 *  the condtion variable unlocks the mutex
 *  the condtion variable blocks this thread
 * thread B locks the mutex
 *  it modifies the string and unlocks the mutex
 *  it call notify_one()
 * the condition variable wakes thread A up
 *  the wait() call returns with the mutex locked
 *  thread A resume execution and uses the string
 *
 * Note: condition variable only works with std::mutex does not work with
 * std::timed_mutex threre is also std::std::condition_variable_any work with
 * any mutex like object
 */

// Condition variable example
//
// The reader thread waits for a notification
// The writer thread modifies the shared variable "sdata"
// The writer thread sends a notification
// The reader thread receives the notification and resumes
// The reader thread uses the new value of the shared data
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// Waiting thread
void reader() {
  // Lock the mutex
  std::cout << "Reader thread locking mutex\n";
  std::unique_lock<std::mutex> uniq_lck(mut);
  std::cout << "Reader thread has locked the mutex\n";

  // Call wait()
  // This will unlock the mutex and make this thread
  // sleep until the condition variable wakes us up
  std::cout << "Reader thread sleeping...\n";
  cond_var.wait(uniq_lck);

  // The condition variable has woken this thread up
  // and locked the mutex
  std::cout << "Reader thread wakes up\n";

  // Display the new value of the string
  std::cout << "Data is \"" << sdata << "\"\n";
}

// Notifying thread
void writer() {
  {
    // Lock the mutex
    std::cout << "Writer thread locking mutex\n";

    // Lock the mutex
    // This will not be explicitly unlocked
    // std::lock_guard is sufficient
    std::lock_guard<std::mutex> lck_guard(mut);
    std::cout << "Writer thread has locked the mutex\n";

    // Pretend to be busy...
    std::this_thread::sleep_for(2s);

    // Modify the string
    std::cout << "Writer thread modifying data...\n";
    sdata = "Populated";
  }

  // Notify the condition variable
  std::cout << "Writer thread sends notification\n";
  cond_var.notify_one();
}

int main() {
  // Initialize the shared string
  sdata = "Empty";

  // Display its initial value
  std::cout << "Data is \"" << sdata << "\"\n";

  // Start the threads
  std::thread read(reader);
  std::thread write(writer);

  write.join();
  read.join();
}

/**
 * condition variable with predicate
 * if writer call notify() before the reader calls wait(), the condition
 * variable is notified when there are no threads waiting, the reader will never
 * woken up, the reader could be blocked forever ==> lost wakeup
 *
 * if the reader thread calls wait() before but the writer thread forgot calls
 * notify() ==> spurious wakeup Solve two problem using wait() with predicate
 * check a shared bool
 *  the bool is initialized to false
 *  its set to true when the writer sends the notification
 * the reader thread will call this predicate
 * it will only call wait() if the predicate return false
 */
// demo slot wakeup
//  Example of a "lost wakeup"
//
//  The writer thread sends its notification before the reader calls wait()
//  The reader never receives the notification
//  The reader thread blocks indefinitely
#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// Waiting thread
void reader() {
  // Lock the mutex
  std::cout << "Reader thread locking mutex\n";
  std::unique_lock<std::mutex> uniq_lck(mut);
  std::cout << "Reader thread has locked the mutex\n";

  // Call wait()
  // This will unlock the mutex and make this thread
  // sleep until the condition variable wakes us up
  std::cout << "Reader thread sleeping...\n";
  cond_var.wait(uniq_lck);

  // The condition variable has woken this thread up
  // and locked the mutex
  std::cout << "Reader thread wakes up\n";

  // Display the new value of the string
  std::cout << "Data is \"" << sdata << "\"\n";
}

// Notifying thread
void writer() {
  {
    // Lock the mutex
    std::cout << "Writer thread locking mutex\n";

    // Lock the mutex
    // This will not be explicitly unlocked
    // std::lock_guard is sufficient
    std::lock_guard<std::mutex> lck_guard(mut);
    std::cout << "Writer thread has locked the mutex\n";

    // Pretend to be busy...
    std::this_thread::sleep_for(2s);

    // Modify the string
    std::cout << "Writer thread modifying data...\n";
    sdata = "Populated";
  }

  // Notify the condition variable
  std::cout << "Writer thread sends notification\n";
  cond_var.notify_one();
}

int main() {
  // Initialize the shared string
  sdata = "Empty";

  // Display its initial value
  std::cout << "Data is \"" << sdata << "\"\n";

  // Start the threads
  // If the writer thread finishes before the reader thread starts, the
  // notification is lost
  std::thread write(writer);
  std::this_thread::sleep_for(500ms);
  std::thread read(reader);

  write.join();
  read.join();
}

// Condition variable with predicate
//
// The reader thread will wait until "condition" becomes true
// This avoids lost and spurious wakeups
#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// bool flag for predicate
bool condition = false;

// Waiting thread
void reader() {
  // Lock the mutex
  std::cout << "Reader thread locking mutex\n";
  std::unique_lock<std::mutex> uniq_lck(mut);
  std::cout << "Reader thread has locked the mutex\n";

  // Call wait()
  // This will unlock the mutex and make this thread
  // sleep until the condition variable wakes us up
  std::cout << "Reader thread sleeping...\n";

  // Lambda predicate that checks the flag
  cond_var.wait(uniq_lck, [] { return condition; });

  // The condition variable has woken this thread up
  // and locked the mutex
  std::cout << "Reader thread wakes up\n";

  // Display the new value of the string
  std::cout << "Data is \"" << sdata << "\"\n";
  std::cout << "Reader thread unlocks the mutex\n";
}

// Notifying thread
void writer() {
  {
    // Lock the mutex
    std::cout << "Writer thread locking mutex\n";

    // Lock the mutex
    // This will not be explicitly unlocked
    // std::lock_guard is sufficient
    std::lock_guard<std::mutex> lck_guard(mut);
    std::cout << "Writer thread has locked the mutex\n";

    // Pretend to be busy...
    std::this_thread::sleep_for(2s);

    // Modify the string
    std::cout << "Writer thread modifying data...\n";
    sdata = "Populated";

    // Set the flag
    condition = true;

    std::cout << "Writer thread unlocks the mutex\n";
  }

  // Notify the condition variable
  std::cout << "Writer thread sends notification\n";
  cond_var.notify_one();
}

int main() {
  // Initialize the shared string
  sdata = "Empty";

  // Display its initial value
  std::cout << "Data is \"" << sdata << "\"\n";

  // The notification is not lost,
  // even if the writer thread finishes before the reader thread starts
  // or there is a "spurious wakeup" (wait returns without a notification)
  std::thread write(writer);
  std::this_thread::sleep_for(500ms);
  std::thread read(reader);

  write.join();
  read.join();
}

// Condition variable with predicate
// Example with multiple waiting threads
#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// bool flag for predicate
bool condition = false;

// Waiting thread
void reader() {
  // Lock the mutex
  std::cout << "Reader thread locking mutex\n";
  std::unique_lock<std::mutex> uniq_lck(mut);
  std::cout << "Reader thread has locked the mutex\n";

  // Call wait()
  // This will unlock the mutex and make this thread
  // sleep until the condition variable wakes us up
  std::cout << "Reader thread sleeping...\n";

  // Lambda predicate that checks the flag
  cond_var.wait(uniq_lck, [] { return condition; });

  // The condition variable has woken this thread up
  // and locked the mutex
  std::cout << "Reader thread " << std::this_thread::get_id() << " wakes up\n";

  // Display the new value of the string
  std::cout << "Data is \"" << sdata << "\"\n";
  std::cout << "Reader thread unlocks the mutex\n";
}

// Notifying thread
void writer() {
  {
    // Lock the mutex
    std::cout << "Writer thread locking mutex\n";

    // Lock the mutex
    // This will not be explicitly unlocked
    // std::lock_guard is sufficient
    std::lock_guard<std::mutex> lck_guard(mut);
    std::cout << "Writer thread has locked the mutex\n";

    // Pretend to be busy...
    std::this_thread::sleep_for(2s);

    // Modify the string
    std::cout << "Writer thread modifying data...\n";
    sdata = "Populated";

    // Set the flag
    condition = true;

    std::cout << "Writer thread unlocks the mutex\n";
  }

  // Notify the condition variable
  std::cout << "Writer thread sends notification\n";

  cond_var.notify_all();
  /*
  for (int i = 0; i < 2; ++i)
          cond_var.notify_one();
  */
}

int main() {
  // Initialize the shared string
  sdata = "Empty";

  // Display its initial value
  std::cout << "Data is \"" << sdata << "\"\n";

  // The notification is not lost,
  // even if the writer thread finishes before the reader thread starts
  // or there is a "spurious wakeup" (wait returns without a notification)

  std::thread write(writer);
  std::thread read1(reader);
  std::this_thread::sleep_for(10ms);
  std::thread read2(reader);
  std::this_thread::sleep_for(10ms);
  std::thread read3(reader);
  std::this_thread::sleep_for(10ms);

  write.join();
  read1.join();
  read2.join();
  read3.join();
}

// Simulation of a program which performs a download
//
// One thread featches the data
// Another thread displays a progress bar
// A third thread processes the data when the download is complete
//
// Implemented using a condition variabla to communicate between the threads
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std::literals;

// Shared variable for the data being fetched
std::string sdata;

// bool flags for predicates
bool update_progress = false;
bool completed = false;

// Mutexes to protect the shared variables
std::mutex data_mutex;
std::mutex completed_mutex;

// The condition variables
std::condition_variable data_cv;
std::condition_variable completed_cv;

// Data fetching thread
void fetch_data() {
  for (int i = 0; i < 5; ++i) {
    std::cout << "Fetcher thread waiting for data..." << std::endl;
    std::this_thread::sleep_for(2s);

    // Update sdata, then notify the progress bar thread
    std::unique_lock<std::mutex> uniq_lck(data_mutex);
    sdata += "Block" + std::to_string(i + 1);
    std::cout << "Fetched sdata: " << sdata << std::endl;
    update_progress = true;
    uniq_lck.unlock();
    data_cv.notify_all();
  }

  std::cout << "Fetch sdata has ended\n";

  // Tell the progress bar thread to exit
  // and wake up the processing thread
  std::lock_guard<std::mutex> lg(completed_mutex);
  completed = true;
  completed_cv.notify_all();
}

// Progress bar thread
void progress_bar() {
  size_t len = 0;

  while (true) {
    std::cout << "Progress bar thread waiting for data..." << std::endl;

    // Wait until there is some new data to display
    std::unique_lock<std::mutex> data_lck(data_mutex);
    data_cv.wait(data_lck, [] { return update_progress; });

    // Wake up and use the new value
    len = sdata.size();

    // Set our flag back to false
    update_progress = false;
    data_lck.unlock();

    std::cout << "Received " << len << " bytes so far" << std::endl;

    // Check if the download has finished
    std::unique_lock<std::mutex> compl_lck(completed_mutex);

    // Terminate when the download has finished
    if (completed_cv.wait_for(compl_lck, 10ms, [] { return completed; })) {
      std::cout << "Progress bar thread has ended" << std::endl;
      break;
    }
  }
}

void process_data() {
  std::this_thread::sleep_for(200ms);
  std::cout << "Processing thread waiting for data..." << std::endl;

  // Wait until the download is complete
  std::unique_lock<std::mutex> compl_lck(completed_mutex); // Acquire lock

  completed_cv.wait(compl_lck, [] { return completed; });
  compl_lck.unlock();

  std::lock_guard<std::mutex> data_lck(data_mutex);
  std::cout << "Processing sdata: " << sdata << std::endl;

  // Process the data...
}

int main() {
  // Start the threads
  std::thread fetcher(fetch_data);
  std::thread prog(progress_bar);
  std::thread processor(process_data);

  fetcher.join();
  prog.join();
  processor.join();
}

/**
 * futures and promises
 * std::thread does not provide a way to return a value. So far, we have used a
 * shared variable, access to the shared variable needs to be protected by locks
 * condition variables allow us to coordinate threads. A thread can signal to
 * another thread that shared data has been modified. Cannot directly transfer
 * data from one thread to another. C++ provide some classes to doing that
 * std::future and std::promise, there are allow for transferring data between
 * threads
 *
 * futures and promises use a producer-consumer model
 * a producer thread will generate a result
 * a consumer thread waits for the result
 * the producer thread generate the result and stores it in the shared state,
 * the cunsumer thread reads the result from the shared state
 *
 * std::promise object is associated with the producer
 * std::future object is associated with the consumer
 */

/**
 * std::future is a template class defined in <future>
 *  the parameter is the type of the data that will be returned
 *
 * get() member function
 *  obtains the result when ready
 *  blocks until the operation is complete
 *  fetches the result and return it
 *
 * wait() and friends
 *  blocks but do not return a result
 *  wait() blocks until the operation is complete
 *  wait_for() and wait_until() block with a timeout
 *
 * get_future() member function
 *  return the associated future
 *  ex: std::promise<int> prom; std::future fut = prom.get_future();
 *
 * set_value()
 *  set the result to its argument
 *
 * set_exception()
 *  indicates that an exception has occurred
 *  this can be stored in the shared state
 *
 */
// Example using std::promise and std::future
// to send a result from a producer thread
// to a consumer thread
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

// The producer's task function takes a std::promise as argument
void produce(std::promise<int> &px) {
  using namespace std::literals;

  // Produce the result
  int x = 42;
  std::this_thread::sleep_for(2s);

  // Store the result in the shared state
  std::cout << "Promise sets shared state to " << x << '\n';
  px.set_value(x);
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int> &fx) {
  // Get the result from the shared state
  std::cout << "Future calling get()...\n";
  int x = fx.get();
  std::cout << "Future returns from calling get()\n";
  std::cout << "The answer is " << x << '\n';
}

int main() {
  // Create an std::promise object
  // This creates an associated std::future object
  // and sets up a shared state between them
  std::promise<int> prom;

  // Get the future associated with the promise
  std::future<int> fut = prom.get_future();

  // Start the threads
  // The producer task function takes the promise as argument
  std::thread thr_producer(produce, std::ref(prom));

  // The consumer task function takes the future as argument
  std::thread thr_consumer(consume, std::ref(fut));

  thr_consumer.join();
  thr_producer.join();
}

// Example using std::promise and std::future
// to throw an exception from a producer thread
// to a consumer thread
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

// The producer's task function takes a std::promise as argument
void produce(std::promise<int> &px) {
  try {
    using namespace std::literals;
    int x = 42;
    std::this_thread::sleep_for(2s);

    // Code that may throw
    if (1)
      throw std::out_of_range("Oops");

    // No exception - store the result in the shared state
    std::cout << "Promise sets shared state to " << x << '\n';
    px.set_value(x);
  } catch (...) {
    // Exception thrown - store it in the shared state
    px.set_exception(std::current_exception());
  }
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int> &fx) {
  std::cout << "Future calling get()...\n";
  try {
    // Get the result from the shared state - may throw
    int x = fx.get();
    std::cout << "Future returns from calling get()\n";
    std::cout << "The answer is " << x << '\n';
  } catch (std::exception &e) {
    // Exception thrown - get it from the shared state
    std::cout << "Exception caught: " << e.what() << '\n';
  }
}

int main() {
  // Create an std::promise object
  // This creates an associated std::future object
  // and sets up a shared state between them
  std::promise<int> prom;

  // Get the future associated with the promise
  std::future<int> fut = prom.get_future();

  // Start the threads
  // The producer task function takes the promise as argument
  std::thread thr_producer(produce, std::ref(prom));

  // The consumer task function takes the future as argument
  std::thread thr_consumer(consume, std::ref(fut));

  thr_consumer.join();
  thr_producer.join();
}

/**
 * producer with std::make_exception_ptr()
 * to throw an exception ourselves, we could
 *  throw the exception inside a try block
 *  write a catch block that calls set_exception()
 *
 * c++11 has std::make_exception_ptr()
 *  takes the exception object we want to throw
 *  return a pointer to its argument
 *  pass this pointer to set_exception()
 *  avoid "boilerplate" code
 *  better code generateion
 */
// Example using std::promise and std::future
// to throw an exception from a producer thread
// to a consumer thread
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

// The producer's task function takes a std::promise as argument
void produce(std::promise<int> &px) {
  using namespace std::literals;
  int x = 42;
  std::this_thread::sleep_for(2s);

  // Code that may throw
  if (1) {
    px.set_exception(std::make_exception_ptr(std::out_of_range("Oops")));
    return;
  }

  // No exception - store the result in the shared state
  std::cout << "Promise sets shared state to " << x << '\n';
  px.set_value(x);
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int> &fx) {
  std::cout << "Future calling get()...\n";
  try {
    // Get the result from the shared state - may throw
    int x = fx.get();
    std::cout << "Future returns from calling get()\n";
    std::cout << "The answer is " << x << '\n';
  } catch (std::exception &e) {
    // Exception thrown - get it from the shared state
    std::cout << "Exception caught: " << e.what() << '\n';
  }
}

int main() {
  // Create an std::promise object
  // This creates an associated std::future object
  // and sets up a shared state between them
  std::promise<int> prom;

  // Get the future associated with the promise
  std::future<int> fut = prom.get_future();

  // Start the threads
  // The producer task function takes the promise as argument
  std::thread thr_producer(produce, std::ref(prom));

  // The consumer task function takes the future as argument
  std::thread thr_consumer(consume, std::ref(fut));

  thr_consumer.join();
  thr_producer.join();
}

/**
 * single producer with multiple consumers
 * consumer can not use the same future ==> use std::shared_future
 */
// code demo error happend
//  Example using std::promise and std::future
//  to send a result from a producer thread
//  to a consumer thread
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

// The producer's task function takes a std::promise as argument
void produce(std::promise<int> &px) {
  using namespace std::literals;

  // Produce the result
  int x = 42;
  std::this_thread::sleep_for(2s);

  // Store the result in the shared state
  std::cout << "Promise sets shared state to " << x << '\n';
  px.set_value(x);
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int> &fx) {
  // Get the result from the shared state
  std::cout << "Future calling get()...\n";
  int x = fx.get();
  std::cout << "Future returns from calling get()\n";
  std::cout << "The answer is " << x << '\n';
}

int main() {
  // Create an std::promise object
  // This creates an associated std::future object
  // and sets up a shared state between them
  std::promise<int> prom;

  // Get the future associated with the promise
  std::future<int> fut = prom.get_future();

  // Start the threads
  // The producer task function takes the promise as argument
  std::thread thr_producer(produce, std::ref(prom));

  // The consumer task function takes the future as argument
  std::thread thr_consumer(consume, std::ref(fut));
  std::thread thr_consumer2(consume, std::ref(fut));

  thr_consumer.join();
  thr_consumer2.join();
  thr_producer.join();
}

// Example using std::promise and std::shared_future
// to send a result from a producer thread
// to multiple consumer threads
#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

// Mutex to protect output
std::mutex mut;

// The producer's task function takes a std::promise as argument
void produce(std::promise<int> &px) {
  using namespace std::literals;

  // Produce the result
  int x = 42;
  std::this_thread::sleep_for(2s);

  // Store the result in the shared state
  std::cout << "Promise sets shared state to " << x << '\n';
  px.set_value(x);
}

// The consumer's task function takes an std::shared_future as argument
void consume(std::shared_future<int> &fx) {
  // Get the result from the shared state
  std::cout << "Thread " << std::this_thread::get_id() << " calling get()...\n";
  int x = fx.get();
  std::lock_guard<std::mutex> lck_guard(mut);
  std::cout << "Thread " << std::this_thread::get_id()
            << " returns from calling get()\n";
  std::cout << "Thread " << std::this_thread::get_id() << " has answer " << x
            << '\n';
}

int main() {
  // Create an std::promise object
  // This creates an associated std::future object
  // and sets up a shared state between them
  std::promise<int> prom;

  // Get an std::shared_future associated with the promise
  // This will move the promise's future into a shared future
  std::shared_future<int> shared_fut1 = prom.get_future();

  // Copy the shared future object
  std::shared_future<int> shared_fut2 = shared_fut1;

  // Start the threads
  // The producer task function takes the promise as argument
  std::thread thr_producer(produce, std::ref(prom));

  // Start two consumer threads
  // The consumer task function takes a shared future as argument
  // Each thread uses a different shared future object
  std::thread thr_consumer1(consume, std::ref(shared_fut1));
  std::thread thr_consumer2(consume, std::ref(shared_fut2));

  thr_consumer1.join();
  thr_consumer2.join();
  thr_producer.join();
}
