# Some questions in c/c++ you need to know
###### 1. C data type?
```
char, bool              1 byte
int, float              4 bytes
double, long            8 bytes
short int               2 bytes
```
###### 2. Difference between namespace and class?
```
Classes are datatypes. Classes are basiccally extended version of strutures. Class can contain data members and function as members.
Namespaces can contain variables and fucntion are grouping them into one. The namespaces cannot be created as object
Namespace can redefine but class is not.
Namespace donot need a named but class is requires.
```
###### 3. Difference between enum and enum class?
-Two enumerations cannot share the same members
```
    // Defining enum1 Gender
    enum Gender { Male,Female };
    // Defining enum2 Gender2 with same values
    // This will throw error
    enum Gender2 { Male,Female };
```
-No variable can have a name which is already member of enum like:
```
    enum Gender { Male,Female };
    // this will throw error
    int Male = 10;
```
-Enum are not type-safe: the compiler can compare two members of different enums
```
    // Defining enum1 Gender
    enum Gender { Male,Female };
    // Defining enum2 Color
    enum Color { Red,Green };
    Gender gender = Male;
    Color color = Red;
    // Upon comparing gender and color
    // it will return true as both have value 0
    // which should not be the case actually
    if (gender == color)
        cout << "Equal";
```
-Enum class can solved the problems obove of enum


