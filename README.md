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




# Understanding the meaning of lvalues and rvalues in c++
lvalue is something that points to a specific memory location.
On the other hand. rvalue is something that doesn't point anywhere.
rvalues are temporary and short lived while lvalues live a longer life since they exist as variables.
For examples:
```
int x = 666; 
```
Here 666 is rvalue, that number is assigned to x, which is a variable. A variable has a specific memory location, So its an lvalue.
x is an lvalue so you can do stuff like that:
```
int* y = &x;
```
&x is grabbing the memory address of x and putting it into pointer y
We can't do stuff like that:
```
int y;
666 = y; // error!
```
or:
```
int* y = &666; // error!
```
#### Functions returning lvalues and rvalues
```
int setValue()
{
    return 6;
}
setValue() = 3; // error!
```
setValue() return an rvalue (6). Which can not be the left operand of assignment. Now what happends if the fucntion returns an lvalue instead.
```
int global = 100;
int& setGlobal()
{
    return global;    
}
setGlobal() = 400; // OK
```
It works because setGlobal() return reference
#### Lvalue to rvalue conversion
An lvalue may get converted to rvalue through + - * / operator
```
int x = 1;
int y = 3;
int z = x + y;   // ok
```
x and y are lvalues, but the addition operator wants to rvalues, How come?. The answer is quite simple: x and y have undergone an implicit lvalue-to-rvalue conversion.
What about the opposite? Can an rvalue be converted to lvalue? ==> Nope. When you do stuff like
```
int y = 10;
int& yref = y;
yref++;        // y is now 11
```
yref as of type int&  that should point to an existing object a referency to y. It's called an lvalue referency. Now you can happily change the value of y through its reference yref.
The forbidden conversion from rvalue to lvalue:
```
void fnc(int& x)
{
}

int main()
{
    fnc(10);  // Nope!
    // This works instead:
    // int x = 10;
    // fnc(x);
}
```
I'm passing a temporary rvalue (10) to a function that takes a referency as argument. Invalid rvalue to lvalue conversion. There's a workaground create a temporary variable where to store the rvalue and then pass it to the function (as in the commented out code) or using const.
#### Const lvalue reference to the rescue
According to the language specifications you are allowed to bind a const lvalue to rvalue
```
const int& ref = 10;  // OK!
```
And of course also the following one:
```
void fnc(const int& x)
{
}

int main()
{
    fnc(10);  // OK!
}
```
The idea behind is quite straightforward. The literal constant 10 is volatile and would expire in no time, so a reference to it is just meaningless. Under the hood the compiler creates an hidden variable for you (i.e. an lvalue) where to store the original literal constant, and then bounds that hidden variable to your reference. That's basically the same thing I did manually in a couple of snippets above. For example:
```
// the following...
const int& ref = 10;

// ... would translate to:
int __internal_unique_name = 10;
const int& ref = __internal_unique_name;
```
Now your reference points to something that exists for real (until it goes out of scope) and you can use it as usual, except for modifying the value it points to:
```
const int& ref = 10;
std::cout << ref << "\n";   // OK!
std::cout << ++ref << "\n"; // error: increment of read-only reference ‘ref’
```
#### Nested ternary operator
Sysntax:
```
Expression1 ? Expression2 : Expression3
```
For example:
```
(a) ? (b ? c : d) : (e ? f : g)
```
We can also express it using nested if else statement to understand it better
```
if  ( a )
    if( b )
        execute c
    else
        execute d
else
    if ( e )
        execute f
    else
        execute g
```

