/**
 * concurrency
 * sometimes useful to distinguish from "parallelism"
 * describes conceptually distinct task
 *  separation of concerns
 *  can run on a single core
 * these tasks often interact
 *  wait for an event
 *  wait for each other
 * the task often overlap in time
 * concurrency is a feature of the program structure
 */

/**
 * parallelism seperate a task to many subtask and handle them
 * task parallelism
 * data parallelism: vectorization
 * pipelining
 *  perform dependent tasks sequentially
 *  process data concurrently
 * graph parallelism
 *  similar to pipelining, but with an arbitrary graph of dependencies
 */

// async.cc
// Example of data parallelism using std::async()
#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

// Compute the sum of a range of elements
double accum(double *beg, double *end) {
  return std::accumulate(beg, end, 0.0);
}

// Divide the data into 4 parts
// Use a separate part to process each subset
double add_parallel(std::vector<double> &vec) {
  // Find the first element of the vector
  auto vec0 = &vec[0];

  // Find the number of elements
  auto vsize = vec.size();

  // Start the threads
  // Pass the subset's range as argument to the task function
  auto fut1 = std::async(std::launch::async, accum, vec0, vec0 + vsize / 4);
  auto fut2 = std::async(std::launch::async, accum, vec0 + vsize / 4,
                         vec0 + 2 * vsize / 4);
  auto fut3 = std::async(std::launch::async, accum, vec0 + 2 * vsize / 4,
                         vec0 + 3 * vsize / 4);
  auto fut4 =
      std::async(std::launch::async, accum, vec0 + 3 * vsize / 4, vec0 + vsize);

  // Reduce step
  // Combine the results for each subset
  return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

int main() {
  // Populate a vector with elements 1, 2, ..., 16
  std::vector<double> vec(16);
  std::iota(vec.begin(), vec.end(), 1.0);

  // Populate a vector with 10,000 random elements
  std::vector<double> vrand(10'000);
  std::generate(vrand.begin(), vrand.end(), [&vrand]() { return dist(mt); });

  // Do the calculations
  std::cout << "Sum of first 16 integers: " << add_parallel(vec) << '\n';
  std::cout << "Sum of 10,000 random numbers: " << add_parallel(vrand) << '\n';
}

// using std::packaged_task
//  packaged_task.cc
//  Example of data parallelism using std::packaged_task
#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0, 100);

// Compute the sum of a range of elements
double accum(double *beg, double *end) {
  return std::accumulate(beg, end, 0.0);
}

// Divide the data into 4 parts
// Use a separate part to process each subset
double add_parallel(std::vector<double> &vec) {
  // Type alias to simplify the code
  using task_type = double(double *, double *);

  // Packaged tasks to manage each thread
  std::packaged_task<task_type> ptask1(accum);
  std::packaged_task<task_type> ptask2(accum);
  std::packaged_task<task_type> ptask3(accum);
  std::packaged_task<task_type> ptask4(accum);

  // Future objects for each thread's result
  auto fut1 = ptask1.get_future();
  auto fut2 = ptask2.get_future();
  auto fut3 = ptask3.get_future();
  auto fut4 = ptask4.get_future();

  // Find the first element of the vector
  auto vec0 = &vec[0];

  // Find the number of elements
  auto vsize = vec.size();

  // Start the threads
  // Pass the subset's range as argument to the task function
  std::thread thr1(std::move(ptask1), vec0, vec0 + vsize / 4);
  std::thread thr2(std::move(ptask2), vec0 + vsize / 4, vec0 + 2 * vsize / 4);
  std::thread thr3(std::move(ptask3), vec0 + 2 * vsize / 4,
                   vec0 + 3 * vsize / 4);
  std::thread thr4(std::move(ptask4), vec0 + 3 * vsize / 4, vec0 + vsize);

  thr1.join();
  thr2.join();
  thr3.join();
  thr4.join();

  // Reduce step
  // Combine the results for each subset
  return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

int main() {
  // Populate a vector with elements 1, 2, ..., 16
  std::vector<double> vec(16);
  std::iota(vec.begin(), vec.end(), 1.0);

  // Populate a vector with 10,000 random elements
  std::vector<double> vrand(10'000);
  std::generate(vrand.begin(), vrand.end(), [&vrand]() { return dist(mt); });

  // Do the calculations
  std::cout << "Sum of first 16 integers: " << add_parallel(vec) << '\n';
  std::cout << "Sum of 10,000 random numbers: " << add_parallel(vrand) << '\n';
}

/**
 * algorithm
 * defined in <algorithm> a few defined in <numeric>
 */
// Uses a standard algorithm to find a character in a string
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string str("Hello world");
  std::cout << "String to search: " << str << '\n';

  // Search string for first occurrence of 'o'
  std::cout << "Searching for first occurrence of \'o\'\n";
  auto res = std::find(str.cbegin(), str.cend(), 'o');

  // Did we find it?
  if (res != str.cend()) {
    // Access the result
    std::cout << "Found a matching element at index: " << res - str.cbegin()
              << '\n';

    std::cout << "At this point in the string: ";
    for (auto it = res; it != str.cend(); ++it)
      std::cout << *it;
    std::cout << '\n';
  } else
    std::cout << "No matching element\n";
}

// Uses a standard algorithm to find a character in a string
// The predicate makes the search case-insensitive
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int main() {
  std::string str("Hello world");
  std::cout << "String to search: " << str << '\n';

  // Search string for first occurrence of 'o'
  std::cout << "Searching for first occurrence of \'o\'\n";

  // Use a predicate function which ignores case
  auto res = std::find_if(str.cbegin(), str.cend(),
                          [](const char c) { return ::toupper(c) == 'O'; });

  // Did we find it?
  if (res != str.cend()) {
    // Access the result
    std::cout << "Found a matching element at index: " << res - str.cbegin()
              << '\n';

    std::cout << "At this point in the string: ";
    for (auto it = res; it != str.cend(); ++it)
      std::cout << *it;
    std::cout << '\n';
  } else
    std::cout << "No matching element\n";
}

/**
 * execution policies
 * sequenced execution
 * parallel execution
 * parallel and vectorized execution
 * vectorized execution only (not until c++20)
 *
 * global objects in <execution> in the std::execution namespace
 */

// Example of sequential execution policy
// Requires C++17 compiler
#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{3, 1, 4, 1, 5, 9};

  // Sort the elements of vec in reverse order
  std::sort(se::seq, vec.begin(), vec.end(),
            [](int a, int b) { return b < a; });

  for (auto i : vec)
    std::cout << i << ',';
  std::cout << '\n';
}

// Example of parallel execution policy with data race
// Requires C++17 compiler
#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec(20'000);
  int count = 0;

  std::for_each(se::par, vec.begin(), vec.end(),
                [&count](int &x) { x = ++count; });

  for (auto i : vec)
    std::cout << i << ',';
  std::cout << '\n';
}

// Example of vectorized execution policy
// Requires C++20 compiler
#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{3, 1, 4, 1, 5, 9};

  // Sort the elements of vec in reverse order
  std::sort(se::unseq, vec.begin(), vec.end(),
            [](int a, int b) { return b < a; });

  for (auto i : vec)
    std::cout << i << ',';
  std::cout << '\n';
}

// Example of parallel vectorized execution policy
// Requires C++17 compiler
#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{3, 1, 4, 1, 5, 9};

  // Sort the elements of vec in reverse order
  std::sort(se::par_unseq, vec.begin(), vec.end(),
            [](int a, int b) { return b < a; });

  for (auto i : vec)
    std::cout << i << ',';
  std::cout << '\n';
}

// An algorithm's predicate function throws an exception
#include <algorithm>
#include <exception>
#include <execution>
#include <iostream>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{3, 1, 4, 1, 5, 9};

  try {
    // Predicate throws an exception
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
      throw std::out_of_range("Oops");
      return true;
    });
  } catch (std::exception &e) {
    std::cout << "Caught exception: " << e.what() << '\n';
  }

  for (auto v : vec)
    std::cout << v << ", ";
  std::cout << '\n';
}

// An algorithm's predicate function throws an exception
// The algorithm has an execution policy
#include <algorithm>
#include <exception>
#include <execution>
#include <iostream>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{3, 1, 4, 1, 5, 9};

  try {
    // Predicate throws an exception
    std::sort(se::seq, vec.begin(), vec.end(), [](int a, int b) {
      throw std::out_of_range("Oops");
      return true;
    });
  } catch (std::exception &e) {
    std::cout << "Caught exception: " << e.what() << '\n';
  }

  for (auto v : vec)
    std::cout << v << ", ";
  std::cout << '\n';
}

// Example of std::accumulate()
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};

  std::cout << "Vector elements: ";
  for (auto i : vec)
    std::cout << i << ", ";
  std::cout << '\n';

  // Sum the elements of vec, using initial value 0
  // Performed in left-to-right order, one addition at a time
  // ((((0 + 1) + 2) + 3) + ...)
  auto sum = std::accumulate(vec.begin(), vec.end(), 0);

  std::cout << "The sum of the elements is " << sum << '\n';
}

// std::reduce support for std::accumulate with policies
//  Example of std::reduce()
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};

  std::cout << "Vector elements: ";
  for (auto i : vec)
    std::cout << i << ", ";
  std::cout << '\n';

  // Sum the elements of vec, using initial value 0
  // Performed as four parallel additions
  // ((0 + 1) + (2 + 3) + (4 + 5) + (6 + 7))
  auto sum = std::reduce(se::par, vec.begin(), vec.end(), 0);

  std::cout << "The sum of the elements is " << sum << '\n';
}

// std::partial_sum
//  Example of std::partial_sum()
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> vec{1, 2, 3, 4};
  std::vector<int> vec2(vec.size());

  // The elements of vec2 will be { 1, 1 + 2, 1 + 2 + 3, 1 + 2 + 3 + 4 };
  // vec2 will contain { 1, 3, 6, 10 };
  std::partial_sum(vec.begin(), vec.end(), vec2.begin());

  std::cout << "Vector elements: ";
  for (auto i : vec)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Elements of partial sum vector: ";
  for (auto i : vec2)
    std::cout << i << ", ";
  std::cout << '\n';
}

// std::inclusive_scan() work the same way as std::partial_sum
//  Example of std::inclusive_scan()
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{1, 2, 3, 4};
  std::vector<int> vec2(vec.size());

  // The elements of vec2 will be { 1, 1 + 2, 1 + 2 + 3, 1 + 2 + 3 + 4 };
  // vec2 will contain { 1, 3, 6, 10 };
  std::inclusive_scan(se::par, vec.begin(), vec.end(), vec2.begin());

  std::cout << "Vector elements: ";
  for (auto i : vec)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Elements of inclusive scan vector: ";
  for (auto i : vec2)
    std::cout << i << ", ";
  std::cout << '\n';
}

// std::exclusive_scan()
// Example of std::exclusive_scan()
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> vec{1, 2, 3, 4};
  std::vector<int> vec2(vec.size());

  // The elements of vec2 will be { -1, 1 + (-1), 1 + 2 + (-1), 1 + 2 + 3 + (-1)
  // } vec2 will contain { -1, 0, 2, 5 };
  std::exclusive_scan(se::par_unseq, vec.begin(), vec.end(), vec2.begin(), -1);

  // This is equivalent to
  std::vector<int> vec3{-1, 1, 2, 3};
  std::vector<int> vec4(vec.size());
  std::inclusive_scan(vec3.begin(), vec3.end(), vec4.begin());

  std::cout << "Vector elements: ";
  for (auto i : vec)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Elements of exclusive scan vector: ";
  for (auto i : vec2)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Elements of inclusive scan vector: ";
  for (auto i : vec4)
    std::cout << i << ", ";
  std::cout << '\n';
}

// Example of std::transform()
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec{1, 2, 3, 4};
  std::vector<int> vec2;

  // Double each element of vec and store the results in vec2
  std::transform(vec.begin(), vec.end(), std::back_inserter(vec2),
                 [](int n) { return 2 * n; });

  // Display the input vector
  std::cout << "Input vector:  ";
  for (auto i : vec)
    std::cout << i << ", ";
  std::cout << '\n';

  // Display the output vector
  std::cout << "Output vector: ";
  for (auto i : vec2)
    std::cout << i << ", ";
  std::cout << '\n';
}

// Example of std::transform() with two inputs
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec{1, 2, 3, 4};
  std::vector<int> vec2{5, 6, 7, 8};
  std::vector<int> vec3;

  // Add each element in v to the corresponding element in v2 and store the
  // result in v3
        std::transform(std::transform(vec.begin(), vec.end(),
				   vec2.begin(),
		           std::back_inserter(vec3),
		           [](int n1, int n2) {
    return n1 + n2;}
	);

	// Display the first input vector
	std::cout << "First input vector:  ";
	for (auto i : vec)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// Display the second input vector
	std::cout << "Second input vector: ";
	for (auto i : vec2)
		std::cout << i << ", ";
	std::cout << '\n';
	
	// Display the output vector
	std::cout << "Output vector: ";
	for (auto i : vec3)
		std::cout << i << ", ";
	std::cout << '\n';
}

// Example of std::transform_reduce()
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<int> x{1, 2, 3, 4, 5};
  std::vector<int> y{5, 4, 3, 2, 1};

  auto result = std::transform_reduce(
      se::par,            // Execution policy
      x.begin(), x.end(), // Iterator range for first vector
      y.begin(),          // Start of second vector
      0);                 // Initial value of sum

  std::cout << "First vector:  ";
  for (auto i : x)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Second vector: ";
  for (auto i : y)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Result is " << result << '\n'; // Displays 35
}

// Example of std::inner_product()
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> x{1, 2, 3, 4, 5};
  std::vector<int> y{5, 4, 3, 2, 1};

  auto result =
      std::inner_product(x.begin(), x.end(), // Iterator range for first vector
                         y.begin(),          // Start of second vector
                         0);                 // Initial value of sum

  std::cout << "First vector:  ";
  for (auto i : x)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Second vector: ";
  for (auto i : y)
    std::cout << i << ", ";
  std::cout << '\n';

  std::cout << "Result is " << result << '\n'; // Displays 35
}

// Example of std::transform_reduce()
// The * and + operators are overloaded
// Finds the greatest difference between the elements in two vectors
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

namespace se = std::execution;

int main() {
  std::vector<double> expected{0.1, 0.2, 0.3, 0.4, 0.5};
  std::vector<double> actual{0.09, 0.22, 0.27, 0.41, 0.52};

  auto max_diff = std::transform_reduce(
      se::par, begin(expected), end(expected), begin(actual),

      // Initial value for the largest difference
      0.0,

      //  "Reduce" operation
      [](auto diff1, auto diff2) { return std::max(diff1, diff2); },

      // "Transform" operation
      [](auto exp, auto act) { return std::abs(act - exp); });

  std::cout << "Max difference is: " << max_diff << '\n';
}
