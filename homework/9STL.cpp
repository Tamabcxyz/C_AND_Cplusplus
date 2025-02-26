/**
 * https://en.cppreference.com/w/cpp/algorithm
 * STL standard template library: a library of powerful, reusable, adaptable,
 * generic classes and fucntions, implemented using c++ template, implement
 * common data structures and algorithms, huge class library
 */
// Element of the STL
// Container: collects of objects or primitive types (array, vector, deque,
// stack, set, map, etc...) Algorithms: function for processing sequences of
// elements from containers (find, max, count, accumulate, sort, etc ...)
// Iterators: generate sequences of element from containers (forward, reverse,
// by value, by reference, constant, etc...)

// Types of containers
//     Sequence container:
//         array, vector, list, forward_list, deque
//     Associative containers
//         set, multi set, map, multi map
//     Container adapters
//         stack, queue, priority queue

// Types of iterators
//     input iterators - from the container to the program
//     output iterators - from the program to the container
//     forward iterators - navigate one item at a time in one direction
//     bi-directional interators - navigate one item at a time both directions
//     random access iterators - directly access a container item

#include <iostream>
#include <numeric> // for std::accumulate
#include <string>
#include <vector>

int main() {
  // Create a vector of strings
  std::vector<std::string> words = {"Hello", "world"};

  // The new string to concatenate with each element
  std::string additionalString = ", ";

  // Use std::accumulate to concatenate each element with the new string
  std::string result =
      std::accumulate(words.begin(), words.end(),
                      std::string(""), // initial value
                      [additionalString](const std::string &accumulated,
                                         const std::string &word) {
                        std::cout << "accumulated: " << accumulated
                                  << std::endl;
                        std::cout << "word: " << word << std::endl;
                        return accumulated + word + additionalString;
                      });

  // Print the result
  std::cout << "Concatenated string: " << result << std::endl;

  return 0;
}

#include <algorithm> //reverse
#include <iostream>
#include <numeric> //accumulate
#include <vector>

#define MAX(a, b) (a > b ? a : b)
#define SQUARE(a) ((a) * (a)) // note: put the arg in the parenthesis

using namespace std;
void print(const std::vector<int> &vec) {
  for (auto &e : vec) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
  print(vec);

  auto sum =
      std::accumulate(vec.begin(), vec.end(),
                      0); // accumulate(first, last, sum_init_value, myfun);
  std::cout << "Sum: " << sum << std::endl;

  std::reverse(vec.begin(), vec.end()); // reverse vector
  print(vec);

  std::cout << MAX(1, 2) << std::endl;
  std::cout << MAX(4, 2) << std::endl;
  std::cout << MAX(1.5, 2.3) << std::endl;
  std::cout << MAX('A', 'B') << std::endl;

  auto result = 100 / SQUARE(5);
  std::cout << result << std::endl;
  return 0;
}

// template
#include <iostream>

using namespace std;
template <typename T> T MY_MAX(const T &a, const T &b) { return a > b ? a : b; }

template <typename T1, typename T2> void func(T1 a, T2 b) {
  std::cout << a << " : " << b << std::endl;
}

int main() {
  cout << MY_MAX(1, 2) << std::endl;
  cout << MY_MAX(1.3, 2.3) << std::endl;
  cout << MY_MAX(3, 2) << std::endl;
  cout << MY_MAX('B', 'C') << std::endl;
  func<int, float>(2, 1.5);
  return 0;
}

// class template
#include <iostream>

using namespace std;
template <typename T> 
class Item {
private:
  std::string name;
  T value;

public:
  Item(std::string a, T b) : name{a}, value{b} {}
  std::string getName() const { return name; }
  T getValue() const { return value; }
  ~Item() = default;
};

template <typename T1, typename T2> 
struct My_Pair {
  T1 first;
  T2 second;
};

int main() {
  Item<int> item1{"Tam", 10};
  std::cout << item1.getName() << " : " << item1.getValue() << std::endl;
  Item<float> item2{"Tam", 10.5f};
  std::cout << item2.getName() << " : " << item2.getValue() << std::endl;
  Item<std::string> item3{"Tam", "number"};
  std::cout << item3.getName() << " : " << item3.getValue() << std::endl;
  Item<Item<int>> item4{"Michael", {"Tran", 9}};
  std::cout << item3.getName() << " : " << item4.getValue().getName() << " : "
            << item4.getValue().getValue() << std::endl;

  My_Pair<int, std::string> mp1{1, "mot"};
  std::cout << "My_Pair: " << mp1.first << " : " << mp1.second << std::endl;
  My_Pair<std::string, std::string> mp2{"hai", "HAI"};
  std::cout << "My_Pair: " << mp2.first << " : " << mp2.second << std::endl;
  return 0;
}

// implement array using template
#include <iostream>

using namespace std;
template <int N> 
class Array {
private:
  int size{N}; // number element in Array
  int arrs[N]; // N needs to know at compile-time
public:
  Array() = default;
  Array(int init_val) {
    for (auto &e : arrs) {
      e = init_val;
    }
  }
  void fill(const int &value) {
    for (auto &e : arrs) {
      e = value;
    }
  }
  int getSize() const { return size; }
  friend std::ostream &operator<<(std::ostream &os, const Array<N> &obj) {
    os << "[";
    for (const auto &e : obj.arrs) {
      os << e << " ";
    }
    os << "]";
    return os;
  }
  int &operator[](int index) { return arrs[index]; }
  ~Array() = default;
};

int main() {
  Array<5> nums;
  std::cout << "The size of nums: " << nums.getSize() << std::endl;
  std::cout << nums << std::endl;

  nums.fill(10);
  std::cout << "The size of nums: " << nums.getSize() << std::endl;
  std::cout << nums << std::endl;

  nums[3] = 20;
  std::cout << "The size of nums: " << nums.getSize() << std::endl;
  std::cout << nums << std::endl;

  Array<100> nums2{1};
  std::cout << "The size of nums2: " << nums2.getSize() << std::endl;
  std::cout << nums2 << std::endl;
  return 0;
}

// iterator container_type::iterator_type iterator_name
//  std::vector<int>::iterator it1;
//  std::list<int>::iterator it2;
//  std::map<int, std::string>::iterator it3;
//  std::set<char>::iterator it4;

// iterator : begin() and end()
// const_interator : cbegin() and cend()
// reverse_iterator : rbegin() and rend()
// const_reverse_iterator : crbegin() and crend()

// algorithm
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
void print(std::vector<int> vec) {
  for (auto it = vec.begin(); it != vec.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 2, 9, 10, -11};
  // std::vector<int>::reverse_iterator it = vec.rbegin();
  // while(it!=vec.rend()){
  //     std::cout << *it << " ";
  //     ++it;
  // }
  print(vec);

  std::for_each(vec.begin(), vec.end(), [&](int x) {
    std::cout << x * 2 << " ";
  }); // loop through each element of vector

  int number = std::count_if(vec.begin(), vec.end(), [](int x) {
    return x % 2 != 0;
  }); // count if suitable with condition
  std::cout << number << std::endl;

  std::replace(vec.begin(), vec.end(), 2, 1); // replace 2 by 1
  print(vec);

  // check all element in container greater than 0
  if (std::all_of(vec.begin(), vec.end(), [](int x) { return x > 0; })) {
    std::cout << "all elements in vec greater than zero" << std::endl;
  } else {
    std::cout << "one or some elements less than zero" << std::endl;
  }

  // uppercase string
  std::string str{"string to upper"};
  std::transform(str.begin(), str.end(), str.begin(), ::toupper);
  std::cout << str << std::endl;
  return 0;
}

// array
#include <algorithm>
#include <array>
#include <iostream>
using namespace std;
template <typename T, size_t S> void print(const std::array<T, S> &arr) {
  for (size_t i = 0; i < arr.size(); i++) {
    std::cout << arr.at(i) << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::array<int, 5> arr{1, 2, 4, 3, 5};
  std::array<int, 5> arr1{6, 7, 8, 9, 10};
  print(arr);
  std::cout << arr.size() << std::endl;     // 5
  std::cout << arr.at(0) << std::endl;      // 1
  std::cout << arr[0] << std::endl;         // 1
  std::cout << arr.front() << std::endl;    // 1
  std::cout << arr.back() << std::endl;     // 5
  std::cout << arr.empty() << std::endl;    // 0 is false, 1 is true
  std::cout << arr.max_size() << std::endl; // 5

  arr.swap(arr1); // swap the 2 arrays
  print(arr);
  print(arr1);

  int *data = arr.data(); // get raw array address
  std::cout << data << std::endl;
  std::cout << *data << std::endl;

  arr.fill(0); // fill all element zero
  print(arr);

  print(arr1);
  std::sort(arr1.begin(), arr1.end()); // sort
  print(arr1);

  std::array<int, 5>::iterator min = std::min_element(arr1.begin(), arr1.end());
  std::cout << "min: " << *min << std::endl;
  auto max = std::max_element(arr1.begin(), arr1.end());
  std::cout << "max: " << *max << std::endl;

  int count = std::count(arr1.begin(), arr1.end(), 3); // how many 3 appear
  return 0;
}

// vector
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
void print(const std::vector<int> &vec) {
  std::for_each(vec.begin(), vec.end(), [](int x) { std::cout << x << " "; });
  std::cout << std::endl;
}

int main() {
  vector<int> a{1, 2, 3, 5};
  vector<int> b{6, 7, 8, 9, 10};

  print(a);
  print(b);
  vector<int>::iterator it = std::find(a.begin(), a.end(), 5); // find position
                                                               // 5
  a.insert(it, 4); // insert 4 at position where we found 5
  print(a);

  std::copy(a.begin(), a.end(), std::back_inserter(b)); // insert element of a to back vector b. relative std::copy_if
  print(b);

  vector<int> x{1, 2, 3, 4, 5};
  vector<int> y{10, 20, 30, 40, 50};
  vector<int> z;
  // 1*10, 2*20,...
  std::transform(
      x.begin(), x.end(), y.begin(), std::back_inserter(z),
      [](int xx, int yy) { return xx * yy; }); // see more std::front_inserter
  print(z);
  return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

//functor: class or struct implement operator() ==> functor
typedef struct{
    void operator()(int &x){
        x*=x;
    }
}Test_t;

int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};
    Test_t test;
    std::for_each(myVector.begin(), myVector.end(), test); 
    std::for_each(myVector.begin(), myVector.end(), [](int x){std::cout << x << " ";});
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

void funcPtr(int &x){
    x*=x;
}
int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};
    std::for_each(myVector.begin(), myVector.end(), funcPtr);//funcPtr is function pointer
    std::for_each(myVector.begin(), myVector.end(), [](int x){std::cout << x << " ";});
    return 0;
}

#include <iostream>
#include <array>
#include <algorithm>

int main() {
    std::array<int, 4> myarr = {1, 2, 3, 4};
    std::array<int, 5> myarr1 = {5,4,3,2,1};
    myarr.swap(myarr1);
    
    std::for_each(myarr.begin(), myarr.end(), [](int x){std::cout << x << " ";});
    std::for_each(myarr1.begin(), myarr1.end(), [](int x){std::cout << x << " ";});
    return 0;
}


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template<typename T>
struct Display{
    void operator()(const T x){
        std::cout << x << " ";
    }
};

int main() {
    std::vector<int> intVector = {1, 2, 3, 4, 5};
    std::vector<std::string> stringVector = {"one", "two", "three", "four", "five"};
    
    std::for_each(intVector.begin(), intVector.end(), Display<int>());
    std::for_each(stringVector.begin(), stringVector.end(), Display<std::string>());

    Display <int>d;
    std::for_each(intVector.begin(), intVector.end(), d);
    return 0;
}


// deque (double ended queue) like vector. If you need efficient random access
// and mostly insert or remove elements at the end, std::vector might be a good
// choice. If you require efficient insertion or removal at both ends and can
// tolerate slightly higher overhead, std::deque could be more suitable.
// std::deque<int> myDeque;

// list and forward_list
// std::list<int> l; //list can be traversing (bi-directional)
// std::forward_list<int> fl;//forward_list reverse iterators not available, do
// not have .size(), .back()

// stack (FILO)
// std::stack<int> s1; //as the default deque underlying container used to implement the stack
// std::stack<int, std::vector<std::string>> s2;//vector underlying container used to implement the stack
// std::stack<int, std::deque<std::string>> s3;
// std::stack<int, std::list<std::string>> s4;//list underlying container used to implement the stack
// std::stack<int, std::forward_list<std::string>> s5;

// queue (FIFO)
// std::queue<int> s1;
// std::queue<int, std::vector<std::string>> s2;
// std::queue<int, std::deque<std::string>> s3;
// std::queue<int, std::list<std::string>> s4;
// std::queue<int, std::forward_list<std::string>> s5;

// priority queue (have ordered) (element largest will on top)


/**
 * sumary:
 * array: have to input size std::array<int, 5> myArray
 * vector: don't need to provide size std::vector<int> vec;
 * list:  inserting and deleting elements at both ends but donnot access random (faster than deque)
 * deque: inserting and deleting elements at both ends can access randomly
 * forward_list, 
*/

/**
 * std::all_of: kiểm tra tất cả phần tử thuộc phạm vi
 * std::any_of: kiểm tra một phần tử bất kì thuộc phạm vi
 * std::none_of: không phần tử nào thuộc phạm vi
*/

/**
 * std::for_each_n: chỉ kiểm tra n số
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    std:vector<int> nums = {
      1,2,3,4,5,6,7,8,-1   
    };
    auto check = [](int x){
        bool b = x>0;
        if(b){
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
        return b;
    };
    std::for_each_n(nums.begin(), 5, check); // n in here is 5
    return 0;
}

/**
 * std::mismatch: tìm vị trí khác nhau giữa 2 container (vector, string, ...)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    std::vector<int> v1 = {
      1,2,3,4,5,6,7,8,-1   
    };
    std::vector<int> v2 = {
      1,2,3,4,-1, 7, 8
    };
    std::vector<int>::iterator end= v1.begin()+3;
    auto result = std::mismatch(v1.begin(), end, v2.begin());
    if(result.first == end && result.second == v2.begin()+3){
        std::cout << "two vector are equal\n";
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    std::vector<int> v1 = {
      1,2,3,4,5,6,7,8,-1   
    };
    std::vector<int> v2 = {
      1,2,3,4,-1, 7, 8
    };
    std::vector<int>::iterator end= std::begin(v1)+3;
    auto result = std::mismatch(std::begin(v1), end, std::begin(v2));
    if(result.first == end && result.second == std::begin(v2)+3){
        std::cout << "two vector are equal\n";
    }
    return 0;
}

#include <iostream>
#include <algorithm>

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 6, 5}; // Note the difference at arr2[3]

    auto result = std::mismatch(std::begin(arr1), std::end(arr1), std::begin(arr2));
    if (result.first != std::end(arr1)) {
        std::cout << "Mismatch found at position: " << std::distance(std::begin(arr1), result.first) << std::endl;
        std::cout << "arr1: " << *result.first << ", arr2: " << *result.second << std::endl;
    } else {
        std::cout << "Arrays are identical." << std::endl;
    }

    return 0;
}

/**
 * std::equal: kiểm tra 
*/

#include <iostream>
#include <algorithm>

bool is_palindrome(const std::string &str) {
    return std::equal(str.begin(), str.begin() + str.size() / 2, str.rbegin());
}

int main()
{
    const std::string input = "abcba";
    // const std::string input = "abcbad";
    std::cout << is_palindrome(input) ? "is palindrome\n" : "not palindrome\n";
    return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>

bool isPalindrome(const std::vector<int>& vec) {
    return std::equal(vec.begin(), vec.begin() + vec.size() / 2, vec.rbegin());
}

int main() {
    std::vector<int> vec1 = {1, 2, 3, 2, 1}; // Palindrome
    std::vector<int> vec2 = {1, 2, 3, 4, 5}; // Not a palindrome

    std::cout << "Vector 1 is " << (isPalindrome(vec1) ? "" : "not ") << "a palindrome." << std::endl;
    std::cout << "Vector 2 is " << (isPalindrome(vec2) ? "" : "not ") << "a palindrome." << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  // Define two vectors of integers
  std::vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {1, 2, 3, 4, 5};

  // Compare the two vectors using std::equal
  bool equal = std::equal(vec1.begin(), vec1.end(), vec2.begin());

  // Output the result
  if (equal) {
      std::cout << "The vectors are equal." << std::endl;
  } else {
      std::cout << "The vectors are not equal." << std::endl;
  }
  return 0;
}

/**
 * std::find: tìm phần tử 
 * std::find_if: tìm phần tử thỏa mảng điều kiện 
 * std::find_if_not: tìm phần tử không thỏa mảng điều kiện 
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Define a vector of integers
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Use std::find to search for the value 3
    auto it = std::find(nums.begin(), nums.end(), 3);
    if (it != nums.end()) {
        std::cout << "Found value 3 at index: " << std::distance(nums.begin(), it) << std::endl;
    } else {
        std::cout << "Value 3 not found" << std::endl;
    }

    // Use std::find_if to search for the first even number
    auto evenIt = std::find_if(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
    if (evenIt != nums.end()) {
        std::cout << "Found the first even number: " << *evenIt << std::endl;
    } else {
        std::cout << "No even number found" << std::endl;
    }

    // Use std::find_if_not to search for the first odd number
    auto oddIt = std::find_if_not(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
    if (oddIt != nums.end()) {
        std::cout << "Found the first odd number: " << *oddIt << std::endl;
    } else {
        std::cout << "No odd number found" << std::endl;
    }

    return 0;
}

/**
 * std::find_last: tìm phần tử cuối cùng xuất hiện
 * std::find_last: tìm phần tử cuối cùng xuất hiện phù hợp với điều kiện
 * std::find_last: tìm phần tử cuối cùng xuất hiện không phù hợp với điều kiện
*/
#include <iostream>
#include <vector>
#include <algorithm>

template <typename ForwardIt, typename T>
ForwardIt find_last(ForwardIt first, ForwardIt last, const T& value) {
    auto it = std::find(std::reverse_iterator<ForwardIt>(last), std::reverse_iterator<ForwardIt>(first), value);
    if (it != std::reverse_iterator<ForwardIt>(first)) {
        return std::prev(it.base());
    }
    return last;
}

template <typename ForwardIt, typename UnaryPredicate>
ForwardIt find_last_if(ForwardIt first, ForwardIt last, UnaryPredicate p) {
    auto it = std::find_if(std::reverse_iterator<ForwardIt>(last), std::reverse_iterator<ForwardIt>(first), p);
    if (it != std::reverse_iterator<ForwardIt>(first)) {
        return std::prev(it.base());
    }
    return last;
}

template <typename ForwardIt, typename UnaryPredicate>
ForwardIt find_last_if_not(ForwardIt first, ForwardIt last, UnaryPredicate p) {
    auto it = std::find_if_not(std::reverse_iterator<ForwardIt>(last), std::reverse_iterator<ForwardIt>(first), p);
    if (it != std::reverse_iterator<ForwardIt>(first)) {
        return std::prev(it.base());
    }
    return last;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 3, 6, 7, 8, 3};

    // Find the last occurrence of value 3
    auto lastThree = find_last(nums.begin(), nums.end(), 3);
    if (lastThree != nums.end()) {
        std::cout << "Last occurrence of value 3 at index: " << std::distance(nums.begin(), lastThree) << std::endl;
    } else {
        std::cout << "Value 3 not found" << std::endl;
    }

    // Find the last even number
    auto lastEven = find_last_if(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
    if (lastEven != nums.end()) {
        std::cout << "Last even number: " << *lastEven << std::endl;
    } else {
        std::cout << "No even number found" << std::endl;
    }

    // Find the last odd number
    auto lastOdd = find_last_if_not(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
    if (lastOdd != nums.end()) {
        std::cout << "Last odd number: " << *lastOdd << std::endl;
    } else {
        std::cout << "No odd number found" << std::endl;
    }

    return 0;
}

/**
 * std::prev: chỉ tới phần tử liền sau
 * std::prev: chỉ tới phần tử liền trước
*/
#include <iostream>
#include <vector>
#include <iterator> // for std::prev and std::next

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Example with std::prev
    auto it = numbers.begin() + 3; // Iterator pointing to the fourth element
    auto prev_it = std::prev(it); // Iterator pointing to the third element
    std::cout << "Previous element: " << *prev_it << std::endl;

    // Example with std::next
    auto next_it = std::next(it); // Iterator pointing to the fifth element
    std::cout << "Next element: " << *next_it << std::endl;

    return 0;
}