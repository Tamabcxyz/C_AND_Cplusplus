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
template <typename T> class Item {
private:
  std::string name;
  T value;

public:
  Item(std::string a, T b) : name{a}, value{b} {}
  std::string getName() const { return name; }
  T getValue() const { return value; }
  ~Item() = default;
};

template <typename T1, typename T2> struct My_Pair {
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
template <int N> class Array {
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

//iterator container_type::iterator_type iterator_name
// std::vector<int>::iterator it1;
// std::list<int>::iterator it2;
// std::map<int, std::string>::iterator it3;
// std::set<char>::iterator it4;

// iterator : begin() and end()
// const_interator : cbegin() and cend()
// reverse_iterator : rbegin() and rend()
// const_reverse_iterator : crbegin() and crend()

//algorithm
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void print(std::vector<int> vec){
    for(auto it = vec.begin();it!=vec.end();it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec{1,2,3,4,5,6,7,2,9,10,-11};
    // std::vector<int>::reverse_iterator it = vec.rbegin();
    // while(it!=vec.rend()){
    //     std::cout << *it << " ";
    //     ++it;
    // }
    print(vec);
    
    std::for_each(vec.begin(), vec.end(), [&](int x){
        std::cout << x*2 << " ";
    }); //loop through each element of vector
    
    int number = std::count_if(vec.begin(), vec.end(), [](int x){
        return x%2!=0;
    }); // count if suitable with condition
    std::cout << number << std::endl;
    
    std::replace(vec.begin(), vec.end(), 2, 1); //replace 2 by 1
    print(vec);
    
    //check all element in container greater than 0
    if(std::all_of(vec.begin(), vec.end(), [](int x){return x>0;})){
        std::cout << "all elements in vec greater than zero" << std::endl;
    }else{
        std::cout << "one or some elements less than zero" << std::endl;
    }
    
    //uppercase string
    std::string str{"string to upper"};
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    std::cout << str << std::endl;
    return 0;
}

//array
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;
template<typename T, size_t S>
void print(const std::array<T, S> &arr){
    for(size_t i = 0 ; i<arr.size(); i++){
        std::cout << arr.at(i) << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::array<int, 5> arr{1,2,4,3,5};
    std::array<int, 5> arr1{6,7,8,9,10};
    print(arr);
    std::cout << arr.size() << std::endl;//5
    std::cout << arr.at(0) << std::endl;//1
    std::cout << arr[0] << std::endl;//1
    std::cout << arr.front() << std::endl; //1
    std::cout << arr.back() << std::endl;//5
    std::cout << arr.empty() << std::endl;//0 is false, 1 is true
    std::cout << arr.max_size() << std::endl; //5
    
    arr.swap(arr1);//swap the 2 arrays
    print(arr);
    print(arr1);
    
    int *data = arr.data(); //get raw array address
    std::cout << data << std::endl;
    std::cout << *data << std::endl;
    
    arr.fill(0); //fill all element zero
    print(arr);
    
    print(arr1);
    std::sort(arr1.begin(), arr1.end()); //sort
    print(arr1);
    
    std::array<int, 5>::iterator min = std::min_element(arr1.begin(), arr1.end());
    std::cout << "min: " << *min << std::endl; 
    auto max = std::max_element(arr1.begin(), arr1.end());
    std::cout << "max: " << *max << std::endl; 
    
    int count = std::count(arr1.begin(), arr1.end(), 3); //how many 3 appear
    return 0;
}

//vector
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void print(const std::vector<int> &vec){
    std::for_each(vec.begin(), vec.end(), [](int x){
        std::cout << x << " ";
    });
    std::cout << std::endl;
}

int main()
{
    vector<int> a{1,2,3,5};
    vector<int> b{6,7,8,9,10};

    print(a);
    print(b);
    vector<int>::iterator it = std::find(a.begin(), a.end(), 5); //find position 5
    a.insert(it, 4); //insert 4 at position where we found 5
    print(a);
    
    std::copy(a.begin(), a.end(), std::back_inserter(b)); //insert element of a to back vector b. relative std::copy_if
    print(b);
    
    
    vector<int> x{1,2,3,4,5};
    vector<int> y{10,20,30,40,50};
    vector<int> z;
    //1*10, 2*20,...
    std::transform(x.begin(), x.end(), y.begin(), std::back_inserter(z),[](int xx, int yy){return xx*yy;}); //see more std::front_inserter
    print(z);
    return 0;
}

// deque (double ended queue) like vector. If you need efficient random access and mostly insert or remove elements at the end, std::vector might be a good choice. 
// If you require efficient insertion or removal at both ends and can tolerate slightly higher overhead, std::deque could be more suitable.
// std::deque<int> myDeque;

// list and forward_list
// std::list<int> l; //list can be traversing (bi-directional)
// std::forward_list<int> fl;//forward_list reverse iterators not available, do not have .size(), .back()


// stack (FILO)
// std::stack<int> s1;
// std::stack<int, std::vector<std::string>> s2;
// std::stack<int, std::deque<std::string>> s3;
// std::stack<int, std::list<std::string>> s4;
// std::stack<int, std::forward_list<std::string>> s5;

// queue (FIFO)
// std::queue<int> s1;
// std::queue<int, std::vector<std::string>> s2;
// std::queue<int, std::deque<std::string>> s3;
// std::queue<int, std::list<std::string>> s4;
// std::queue<int, std::forward_list<std::string>> s5;

// priority queue (have ordered) (element largest will on top)