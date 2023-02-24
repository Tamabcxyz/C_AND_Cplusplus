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
#### lvalue and rvalue reference
* lvalue (&)
* rvalue (&&)
Can only be bound to lvalues but not rvalues. How ever we can bound rvalue to **const lvalue reference**
```
int i = 10;
int& k = i; //k is a lvalue referency
int& k = 10; //Error because k is lvalue referencyand 10 is rvalue
const int& k = 10; //It's ok
```
Example for rvalue referency:
```
int func(){
//do some thing
return 0;
}
//in main
int&& i = 10; //ok
int&& x = func(); //ok
int x = func(); //ok
int& x = func(); //error because func return a rvalue not lvalue
```
**Convert lvalue to rvalue reference**
* std::move(lvalue)
* static_cast<typename &&>(lvalue)
#### Move senmatics move constructor
```
#include <iostream>
using namespace std;
class A{
    public:
        A(){std::cout << "Default constructor\n";}
        A(A&){std::cout << "Copy constructor\n";}
        A(A&&){std::cout << "Move constructor\n";}
};

int main()
{
    A a; //It's call default constructor
    A b = a; //It's call copy constructor
    A c = std::move(a); //It's call move constructor
    return 0;
}
```
#### Move senmatics move assignment operator
```
#include <iostream>
using namespace std;
class A{
    public:
        A(){std::cout << "Default constructor\n";}
        A(A&){std::cout << "Copy constructor\n";}
        A(A&&){std::cout << "Move constructor\n";}
        
        A& operator = (A&){
            std::cout << "Copy assignment\n";
            return *this;
        }
        A& operator = (A&&){
            std::cout << "Move assignment\n";
            return *this;
        }
};

int main()
{
    A a; //It's call default constructor
    A b; //It's call default constructor
    b = a; //It's call copy assignment operator
    b = std::move(a); //It's call move assignment operator
    return 0;
}
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
#### Static data member
```
#include <iostream>
using namespace std;
class Base{
    private:
    int x;
    //static data member
    static int y;
    public:
    void setX(int a){x=a;}
    void setY(int b){y=b;}
    int getX(){return x;}
    int getY(){return y;}
};
//Have to init static data member
int Base::y=1;
int main()
{
    Base a,b;
    a.setY(10);
    a.setX(1);
    b.setY(20);
    b.setX(2);
    std::cout << a.getX() <<std::endl; //1
    std::cout << a.getY() <<std::endl; //20
    std::cout << b.getX() <<std::endl; //2
    std::cout << b.getY(); //20
    return 0;
}
```
#### Const data member
+ const inside class (Can not change the value of const variable inside class)
+ const outside class (Can change the value of variable)
```
#include <iostream>
#include <string>
using namespace std;
class Car{
    private:
    const std::string cname;
    int no;
    public:
    Car(std::string name, int n):cname(name), no(n){}
    std::string getCarNameAndNo(){
        return cname + ", " + std::to_string(no);
    }
};

int main()
{
    //init const variable cname outside class through constructor
    Car a("Model A", 1), b("Model S", 2);
    std::cout << a.getCarNameAndNo() << std::endl; 
    std::cout << b.getCarNameAndNo() << std::endl; 
    return 0;
}
```
#### const before parameter vs const after function name c++
1. const keywork we can't change value
```
const int var =25; //const variable must be initialized when it's declared.
var =50; //gives error
```
2. variable pointer with **const** after ***** then we can't change pointer itself but content of pointer is changeable.
```
int *const ptr = new int;
ptr = new int; //gives error
*ptr=5445; //allowed
```
3. variable pointer with **const** before ***** then we can change pointer itself but content of pointer is not changeable.
```
int const* ptr = new int(85);      
//const int * ptr = new int(85);
ptr = new int; //allowed
*ptr=5445; //gives error
```
4. pointer and content both constant.
```
int const*constptr = new int(85);                        
//const int *constptr = new int(85);
ptr = new int; // not allowed
*ptr=5445; // not allowed
```
Example with class:
```
class C {
  void f(int x);
};
//You can imagine really looks like this:
 void f(C* this, int x);
//Now, if you declare it this way:
 void f(int x) const;
//It's as if you wrote this:
void f(const C* this, int x);
==> **const** after f() mean the method cannot modify the object on which it was invoked.
```
#### static_pointer_cast and dynamic_pointer_cast
```
#include <iostream>
#include <string>
#include <memory>
using namespace std;
class A {
    public:
      A() {}
      void func(){
          std::cout << "A\n";
      }
};
class B: public A {
    public:
      B() {}
      void func(){
          std::cout << "B\n";
      }
};

int main()
{
    auto a=std::make_shared<A>();
    //casting a shared pointer to pointer of class A if wanna use func of class A
    std::static_pointer_cast<A>(a)->func(); //A
    auto b = std::make_shared<B>();
    //casting a shared pointer to pointer of class B if wanna use func of class B
    std::static_pointer_cast<B>(b)->func(); //B
    //casting a shared pointer of delivery class (B) to Base class (A)
    auto c = std::dynamic_pointer_cast<A>(b);
    c->func(); //A
    //casting a shared pointer of Base class (A) to delivery class (B)
    auto d = std::static_pointer_cast<B>(a);
    d->func(); //B
    return 0;
}
```
#### Call private function of child class
```
using namespace std;
class A{
    private:
    int a;
    public:
    virtual void display(){
        std::cout << "A\n";
    }
};
class B : public A{
    private:
    int b;
    void display(){
        std::cout << "Private B";
    }
    public:
    B(int x):b{x}{}
};
int main()
{
    B b(5);
    A *a = &b;
    a->display(); // Private B
    return 0;
}
```
