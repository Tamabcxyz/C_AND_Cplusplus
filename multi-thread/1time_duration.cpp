// Time Durations
#include <chrono>
#include <iostream>

int main() {
  // using namespace std::chrono;

  // Define a duration of 2 seconds
  std::chrono::seconds secDuration = std::chrono::seconds(2);

  // Add two durations
  std::chrono::seconds totalDuration = secDuration + std::chrono::seconds(3);

  std::cout << "Total duration: " << totalDuration.count() << " seconds\n";

  return 0;
}

// Time Points
#include <chrono>
#include <ctime>
#include <iostream>

int main() {
  // using namespace std::chrono;

  // Get the current time point
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

  // Convert time point to a time_t
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

  std::cout << "Current time: " << std::ctime(&currentTime);

  return 0;
}

// Sleeping:
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Sleep for 2 seconds" << std::endl;
  return 0;
}

// Generate number but it not change
#include <iostream>
#include <random>

using namespace std;

int main()
{
    std::mt19937 mt;
    // we want to ints in the range 0 to 100
    std::uniform_int_distribution<int> uuid(0,100);
    for(int i=0; i<5;i++){
        std::cout << uuid(mt) << std::endl; //number generate from 0 to 100 fixed (not change)
    }
    return 0;
}

