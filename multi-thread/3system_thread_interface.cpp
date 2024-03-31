// "id" stand for identifier
#include <iostream>
#include <thread>

using namespace std;
void func() {
  std::cout << "func hello" << std::endl;
  std::cout << "func thread id: " << std::this_thread::get_id()
            << std::endl; // this play func thread id
}

int main() {
  std::cout << "main thread id: " << std::this_thread::get_id()
            << std::endl; // this play main thread id
  std::thread th(func);   // create object thread
  std::cout << "th thread id: " << th.get_id()
            << std::endl; // this play func thread id
  std::cout << "native_handle: " << th.native_handle()
            << std::endl; // check thread is execute complete
  th.join();
  std::cout << "native_handle: " << th.native_handle()
            << std::endl; // 0 is complete

  return 0;
}

// sleep_for
#include <iostream>
#include <thread>

using namespace std;

void func() {
  std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep for 2s
  std::cout << "print hello after 2s" << std::endl;
}

int main() {
  std::thread th(func); // create object thread
  th.join();
  return 0;
}

// can not copy thread, only move
#include <iostream>
#include <thread>

using namespace std;
void func1() {
  std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep for 2s
  std::cout << "print hello after 2s" << std::endl;
}

void func2(std::thread th) {
  std::cout << "func with agrument is thread have id: " << th.get_id()
            << std::endl;
  th.join();
}

int main() {
  std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
  std::thread th(func1);
  func2(std::move(th));
  // th.join(); //join is not need because thread have been moved
  return 0;
}

// function return thread object
#include <iostream>
#include <thread>

using namespace std;
void func1() {
  std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep for 2s
  std::cout << "print hello after 2s" << std::endl;
}

std::thread func2() {
  std::thread th(func1);
  return th;
}

int main() {
  std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;
  std::thread mainth = func2();
  std::cout << "mainth id: " << mainth.get_id() << std::endl;
  mainth.join();
  return 0;
}

//thread and exception
//done
