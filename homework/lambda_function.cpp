/**
 * [capture](parameter_list) -> return_type {
    // body of the lambda function

    Default capture
    [=] //Default capture by value
    [&] //Default capture by reference
    [this] //Default capture this object bu reference

    Using default and explicit captures
    [=, &x] //Default caputure by value but capture x by reference
    [&, y] //Default capture by reference but capture y by value
    [this, z] //Default capture this by but capture z by value
}
*/

#include <iostream>
using namespace std;

int main() {
  int a = 5, b = 10;
  auto add = [&a, &b](int x, int y) -> int {
    b++; // Capture 'b' by reference, so it can be modified
    a--;
    return a + b + x + y;
  };

  int result = add(1, 2);
  std::cout << "b: " << b << std::endl;
  std::cout << "a: " << a << std::endl;
  std::cout << "Result: " << result << std::endl;
  return 0;
}

#include <functional>
#include <iostream>
#include <vector>
using namespace std;
// void filter_vector(const std::vector<int> &vec, std::function<bool(int)>
// func){
void filter_vector(const std::vector<int> &vec, auto func) {
  std::cout << "[";
  for (auto &i : vec) {
    if (func(i)) {
      std::cout << i;
    }
  }
  std::cout << "]";
}

int main() {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
  filter_vector(vec, [](int x) { return (x & 1) == 0; }); // positive number
  filter_vector(vec, [](int x) { return (x & 1) != 0; }); // negative number
  return 0;
}

#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int x{100};
  auto f = [x]() mutable { // mutable key word help capture can be modify
                           // without using &
    x = x + 100;
    std::cout << "x inside: " << x << std::endl;
  };

  f();                                            // 200
  std::cout << "x out side1: " << x << std::endl; // 100
  f(); // in the second time x was capture at first time, now in body x have
       // value 200 x = x+100 ==> x=300
  std::cout << "x out side2: " << x << std::endl; // 100

  return 0;
}

#include <iostream>
#include <string>

using namespace std;

class Person {
private:
  std::string name;
  int age;
  friend std::ostream &operator<<(std::ostream &os, const Person &rhs);

public:
  Person() = default;
  Person(const std::string &name, const int &age) : name{name}, age{age} {}
  Person(const Person &p) = default;
  std::string getName() const { return this->name; }
  int getAge() const { return this->age; }
  void setName(const std::string &tName) { this->name = tName; }
  void setAge(const int &tAge) { this->age = tAge; }
  ~Person() = default;

  auto change_person1() {
    return [this](const std::string &newName, const int &newAge) {
      name = newName;
      age = newAge;
    };
  }
  auto change_person2() {
    return [=](const std::string &newName, const int &newAge) {
      name = newName;
      age = newAge;
    };
  }
  auto change_person3() {
    return [&](const std::string &newName, const int &newAge) {
      name = newName;
      age = newAge;
    };
  }
};

std::ostream &operator<<(std::ostream &os, const Person &rhs) {
  os << "[Person: " << rhs.name << " : " << rhs.age << "]" << std::endl;
  return os;
}

int main() {
  Person person("Jep", 23);
  std::cout << person;

  // capture [this]
  auto ch1 = person.change_person1();
  ch1("Person1", 30);
  std::cout << person;

  // capture [=]
  auto ch2 = person.change_person2();
  ch2("Person2", 40);
  std::cout << person;

  // capture [&]
  auto ch3 = person.change_person3();
  ch3("Person3", 50);
  std::cout << person;

  return 0;
}

/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java,
PHP, Ruby, Perl, C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C,
Assembly, HTML, CSS, JS, SQLite, Prolog. Code, Compile, Run and Debug online
from anywhere in world.

*******************************************************************************/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
private:
  std::string name;
  int age;
  friend std::ostream &operator<<(std::ostream &os, const Person &rhs);

public:
  Person() = default;
  Person(const std::string &name, const int &age) : name{name}, age{age} {}
  Person(const Person &p) = default;
  std::string getName() const { return this->name; }
  int getAge() const { return this->age; }
  void setName(const std::string &tName) { this->name = tName; }
  void setAge(const int &tAge) { this->age = tAge; }
  ~Person() = default;
};

class People {
private:
  std::vector<Person> people;
  int max_people;

public:
  People(int max = 10) : max_people{max} {}
  People(const People &p) = default;
  void add(const std::string &name, const int &age) {
    people.emplace_back(name, age);
  }
  void setMaxPeople(int max) { max_people = max; }
  int getMaxPeople() const { return max_people; }
  // get people by age

  std::vector<Person> filterPeopleByAge(int max_age) {
    std::vector<Person> result;
    int count{0};
    std::copy_if(people.begin(), people.end(), std::back_inserter(result),
                 [this, &count, max_age](const Person &p) {
                   return p.getAge() > max_age && ++count <= max_people;
                 });
    return result;
  }
};

std::ostream &operator<<(std::ostream &os, const Person &rhs) {
  os << "[Name: " << rhs.name << " age: " << rhs.age << "]";
  return os;
}

int main() {
  People ps;
  ps.add("A", 18);
  ps.add("B", 20);
  ps.add("C", 30);
  ps.add("D", 45);
  ps.add("E", 60);

  auto filter = ps.filterPeopleByAge(45);
  for (auto &p : filter) {
    std::cout << p << std::endl;
  }

  return 0;
}

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class PasswordValidator1 {
private:
  char restricted{'$'};

public:
  bool is_valid(const std::string &password) {
    return std::all_of(password.begin(), password.end(),
                       [this](char c) { return c != restricted; });
  }
};

class PasswordValidator2 {
private:
  std::vector<char> restricted{'$', '!', '%'};

public:
  bool is_valid(std::string_view password) {
    return std::all_of(password.begin(), password.end(), [this](char c) {
      return std::none_of(restricted.begin(), restricted.end(),
                          [c](char s) { return c == s; });
    });
  }
};

int main() {
  PasswordValidator1 validator1;
  std::string str1{"Password123!"};
  std::cout << validator1.is_valid(str1) << std::endl;

  PasswordValidator2 validator2;
  std::string_view str2{str1};
  std::cout << validator2.is_valid(str2) << std::endl;
  return 0;
}