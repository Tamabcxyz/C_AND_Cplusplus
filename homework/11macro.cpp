#include <iostream>
#define STRINGIZE(x) #x
#define LOG(...) std::cout << __VA_ARGS__ << std::endl
#define DEBUG_PRINT(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)

int main() {

  std::cout << STRINGIZE(abcd) << std::endl;
  std::string a{"hi"}, b{"helo"};
  LOG("hello it's me");
  LOG(a);
  int x = 10;
  DEBUG_PRINT("The value of x is: %d\n", x);
  DEBUG_PRINT("The value of a is: %s\n", a.c_str());
  return 0;
}

// print_log is a function

#define LOG_DEBUG(...) print_log(LOG_DEBUG_DEBUG,  __FILENAME__, __LINE__) (__VA_ARGS__)
#define LOG_DEBUG2(...) print_log(LOG_DEBUG_DEBUG2, __FILENAME__, __LINE__) (__VA_ARGS__)
#define LOG_DEBUG3(...) print_log(LOG_DEBUG_DEBUG3, __FILENAME__, __LINE__) (__VA_ARGS__)
#define LOG_DEBUG4(...) print_log(LOG_DEBUG_DEBUG4, __FILENAME__, __LINE__) (__VA_ARGS__)
#define LOG_WARN(...) print_log(LOG_DEBUG_WARN, __FILENAME__, __LINE__) (__VA_ARGS__)
#define LOG_INFO(...) print_log(LOG_DEBUG_INFO, __FILENAME__, __LINE__) (__VA_ARGS__) 
#define LOG_ERROR(...) print_log(LOG_DEBUG_ERROR, __FILENAME__, __LINE__) (__VA_ARGS__)