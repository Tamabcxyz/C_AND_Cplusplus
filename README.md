# Road map: https://roadmap.sh/cpp
High Memory
--------------
|   Stack    |  <--- Grows downward
--------------
|   Heap     |  <--- Grows upward
--------------
|   BSS      |  (Uninitialized global and static variables)
--------------
|   Data     |  (Initialized global and static variables)
--------------
|   Text     |  (Program code/instructions)
--------------
Low Memory
***Stack vs Heap***:
- Stack memory is fast but limited in size.
- Heap memory is slower but more flexible and larger in size.
***Default Initialization***:
- Variables in BSS are automatically initialized to 0.
- Local variables on the Stack are not initialized by default (contain garbage values).
***Memory Management***:
- Always free() dynamically allocated memory from the Heap.
- Improper memory management can lead to leaks or crashes.
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
    static int y; //in c++17 we can declare "static inline int y;"
    public:
    void setX(int a){x=a;}
    void setY(int b){y=b;}
    int getX(){return x;}
    int getY(){return y;}
};
//Have to init static data member
int Base::y=1; //we can remove this line if using inline keywork in c++ 17
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
5. const* and *const
```
#include <iostream>
// "const char *" can be write like this "char const *" : a pointer to const character
// "char * const" a const pointer to a character
// => const before * it's const of variable, const after * it's const of pointer
int main() {
    char i = 'A';
    char t = 'T';
    //const char *ptr1 = &i;
    //*ptr1 = 'B'; //can't do that because "const char *ptr1 = &i;" mark as const char we can modify i
    // char * const ptr2 = &i;
    // ptr2 = &t; // error because "char * const ptr2 = &i;" mark as a const pointer it can not point to another address

    return 0;
}
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
#### a reference data member in class only asign on this way
```
#include <iostream>
using namespace std;
struct Point{
    int x=0,y=0;
};
class Shape : public Point{
    private:
    Point& b;
    public:
    Shape(Point& for_b) : b{for_b}{
        //b = for_b; error
    }
    ~Shape(){}
};

int main()
{
    Point p;
    Shape shape(p);
    return 0;
}
```
#### pointer to implement into class
```
#include <iostream>
#include <string>
#include <memory>
class Person{
    public:
    Person(std::string, int);
    ~Person();
    std::string Get();
    private:
    class Implement; //inside class Person
    //Implement* imp_t;
    std::unique_ptr<Implement> imp_t;
};
//declare Implement class
class Person::Implement{
    public:
    std::string m_name;
    int m_age;
};
Person::Person(std::string name, int age){
    //imp_t = new Implement;
    imp_t = std::make_unique<Implement>();
    imp_t->m_name = name;
    imp_t->m_age = age;
}
Person::~Person(){ 
    //delete imp_t; 
}
std::string Person::Get(){ return imp_t->m_name + " : "+ std::to_string(imp_t->m_age); }
int main()
{
    Person a("Tam", 23);
    std::cout << a.Get();
    return 0;
}
```
#### parameter pack
how to plus all agument into a function
```
#include <iostream>
#include <string>
template<typename T>
T Plus(T arg){
    return arg;
}
template<typename T, typename... Args>
T Plus(T start, Args... args){
    return start + Plus(args...);
}

int main()
{
    std::cout << Plus(1,4,6,7,10) <<std::endl; //you can put more parameters into function Plus
    std::cout << Plus<double>(1,4.5,6,7.3,10);
    return 0;
}
```
#### bind and placeholders
```
#include <iostream>
#include <functional> //for bind
using namespace std;
using namespace std::placeholders;
void plusfunc(int a, int b, int c){
    std::cout << (a) << std::endl;
    std::cout << (b) << std::endl;
    std::cout << (c) << std::endl;
    std::cout << (a+b+c) << std::endl;
}
int main()
{
    auto f = std::bind(plusfunc, 5,2,_1); //_1 recieve value of param when f call
    auto k = std::bind(plusfunc, 5,_1,_1);
    auto q = std::bind(plusfunc, _2, 2, _1); //_2 recieve value of 2th param when q call
    auto e = std::bind(plusfunc, _1, 2, _2);
    f(10); // 5+2+10
    k(1); //5+1+1
    q(1,13); //13+2+1
    e(1,13); // 1+2+13
    return 0;
}
```
#### What does “typedef void (*Something) ()” mean in C?
void (*Something) () declares Something as type alias to pointer to function taking variadic arguments (0 to any number) and returning void.
Now void Something() declares Something as function returning void. To declare a pointer to function one can use void (*Something)() and to declare it a typedef, use typedef void (*Something) ().
```
void somefunc(/* I hate empty argument list in C, put a void here */ ) 
{ 
  … 
} 
… 
typedef void (*Something) (); 
… 
Something something_fn_ptr = somefunc; 
(*something_fn_ptr) (); /* If you are a novice */ 
something_fn_ptr (); /* If you are modetately good or good in C */ 
```
### Design pattern (creational, structural, behavioral)
#### Creational design pattern: how to create object
###### 1.Factory method pattern: is a creational design pattern that provides **an interface for creating objects in a superclass**, but allows **subclasses to alter the type of objects that will be created**.
```
#include <iostream>
using namespace std;

class Item{
    public:
    virtual void print_object() = 0;
};
class IPhone12 : public Item{
    public:
    void print_object(){ std::cout << "IPhone12" << std::endl; }
};
class IPhone13 : public Item{
    public:
    void print_object(){ std::cout << "IPhone13" << std::endl; }
};

class Factory{
    public:
    Item* createIPhone(std::string str){
        if(str =="IPhone12"){ return new IPhone12; }
        if(str =="IPhone13"){ return new IPhone13; }
        return nullptr;
    }
};

class App{
    Factory fac;
    public:
    Item* createItem(std::string str){
        return fac.createIPhone(str);
    }
};

int main()
{
    App app;
    auto object = app.createItem("IPhone13");
    object->print_object(); // IPhone13
    return 0;
}
```
###### 2.Abstract factory pattern: is a creational design pattern that lets you produce **families** of related objects **without specifying their concrete classes**.
```
// make_unique only using -std=c++14 for compiler
#include <iostream>
#include <memory>
using namespace std;

class CheckBox {
    public:
    virtual void pain() = 0;
};

class Button {
    public:
    virtual void pain() = 0;
};

class WindowCheckBox : public CheckBox {
    public:
    void pain() override {
        std::cout << "WindowCheckBox\n";
    }
};
class LinuxCheckBox : public CheckBox {
    public:
    void pain() override{
        std::cout << "LinuxCheckBox\n";
    }
};

class WindowButton : public Button {
    public:
    void pain() override{
        std::cout << "WindowButton\n";
    }
};
class LinuxButton : public Button {
    public:
    void pain() override{
        std::cout << "LinuxButton\n";
    }
};

//families of interface CheckBox, Button
class GUIFactory {
    public:
    virtual std::unique_ptr<CheckBox> createCheckBox()=0;
    virtual std::unique_ptr<Button> createButton()=0;
};

class WindowTemplate : public GUIFactory {
    public:
    std::unique_ptr<CheckBox> createCheckBox() override {
        return std::make_unique<WindowCheckBox>();
    }
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowButton>();
    }
};

class LinuxTemplate : public GUIFactory {
    public:
    std::unique_ptr<CheckBox> createCheckBox() override {
        return std::make_unique<LinuxCheckBox>();
    }
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<LinuxButton>();
    }
};

int main() {
    std::unique_ptr<GUIFactory> gf;
    gf = std::make_unique<LinuxTemplate>();
    
    auto button = gf->createButton();
    auto checkbox = gf->createCheckBox();
    
    button->pain();// LinuxButton
    checkbox->pain();// LinuxCheckBox
}
```
###### 3.Builder pattern: is a creational design pattern that lets you **construct complex objects step by step**. The pattern allows you to produce different types and representations of an object using the same construction code.
```
#include <iostream>
#include <string>
//object need to create
class Pizza{
private:
    std::string dough_;
    std::string sauce_;
    std::string topping_;
    
public:
    void setDough(std::string dough){
        dough_ = dough;
    }
    void setSauce(std::string sauce){
        sauce_ = sauce;
    }
    void setTopping(std::string topping){
        topping_ = topping;
    }
    void disPlay(){
        std::cout << "Dough: " << dough_ << ", Sauce: " << sauce_ << ", Topping: " << topping_ << std::endl;
    }
};
//abstract builder
class PizzaBuilder{
    public:
    virtual void buildDough(std::string dough) = 0;
    virtual void buildSauce(std::string sauce) = 0;
    virtual void buildTopping(std::string topping) = 0;
    virtual Pizza getPizza() = 0;
};

class TamPizza : public PizzaBuilder{
private:
    Pizza pizza_;
public:
   void buildDough(std::string dough) override{
       pizza_.setDough(dough);
   }
   void buildSauce(std::string sauce) override{
       pizza_.setSauce(sauce);
   }
   void buildTopping(std::string topping) override{
       pizza_.setTopping(topping);
   }
   Pizza getPizza() override{
       return pizza_;
   }
};

class TaiPizza : public PizzaBuilder{
private:
    Pizza pizza_;
    int code;
public:
   void buildDough(std::string dough) override{
       pizza_.setDough(dough);
   }
   void buildSauce(std::string sauce) override{
       pizza_.setSauce(sauce);
   }
   void buildTopping(std::string topping) override{
       pizza_.setTopping(topping);
   }
   Pizza getPizza() override{
       return pizza_;
   }
   void disPlayCode(){
       std::cout << "Tai have code: " << code << std::endl;
   }
};

class Shipper{
    private:
    PizzaBuilder* builder_;
    public:
    void setPizza(PizzaBuilder* builder){
        builder_ = builder;
    }
    
    Pizza getPizza(){
        return builder_->getPizza();
    }
};

int main(){
    Shipper shipper;
    
    TamPizza tPizza;
    tPizza.buildDough("Tam dough");
    tPizza.buildSauce("Tam sauce");
    tPizza.buildTopping("Tam topping");
    shipper.setPizza(&tPizza);
    Pizza tm = shipper.getPizza();
    tm.disPlay(); //Dough: Tam dough, Sauce: Tam sauce, Topping: Tam topping
    
    TaiPizza taiPizza;
    taiPizza.buildDough("Tai dough");
    taiPizza.buildSauce("Tai sauce");
    taiPizza.buildTopping("Tai topping");
    shipper.setPizza(&taiPizza);
    Pizza ti = shipper.getPizza();
    ti.disPlay(); //Dough: Tai dough, Sauce: Tai sauce, Topping: Tai topping
    return 0;
}
```
###### 4.Prototype pattern: is a creational design pattern that lets you **copy existing objects**  without making your code dependent on their classes.
```
#include <iostream>
#include <unordered_map>

class Shape{
  public:
  virtual ~Shape() {}
  virtual Shape* clone() const = 0;
  virtual void draw() const = 0;
};

class Circle : public Shape {
    private:
    int radius;
    public:
    Circle(int r) : radius(r) {}
    Shape* clone() const override{
        return new Circle(*this);
    }
    void draw() const override{
        std::cout << "Draw from Circle radius is: " << radius << std::endl;
    }
};

class Square : public Shape{
    private:
    int size;
    public:
    Square(int s) : size(s){}
    Shape* clone() const override{
        return new Square(*this);
    }
    void draw() const override{
        std::cout << "Draw from Square size is: " << size << std::endl;
    }
};

class ShapeCache{
    private:
    std::unordered_map<std::string, Shape*> cache;
    public:
    Shape* getShape(const std::string &type){
        return cache[type]->clone();
    }
    void loadCache(){
        cache["circle"] = new Circle(5);
        cache["square"] = new Square(10);
    }
};

int main(){
    ShapeCache sc;
    sc.loadCache();
    
    Shape* c = sc.getShape("circle");
    Shape* s = sc.getShape("square");
    
    c->draw();
    s->draw();
    
    delete c;
    delete s;
}
```
###### 5.Singleton pattern: is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.
```
#include <iostream>
#include <string>
#include <thread>

using namespace std;
class Singleton{
  private:
  static Singleton* instance; //common resources
  std::string name;
  Singleton(){}; //have to put in private to prevent call and created instance
  Singleton(std::string value) : name{value}{};
  public:
  Singleton(Singleton&) = delete; //need to delete copy constructor
  Singleton* operator=(Singleton&) = delete; //need to delete copy assignment
  static Singleton* getSingletonInstance(std::string value); //function static to get instance
  std::string getName();
};

Singleton* Singleton::getSingletonInstance(std::string value){
    if(instance==nullptr){
        instance = new Singleton(value);
    }
    return instance;
}
string Singleton::getName(){
    return name;
}

Singleton* Singleton::instance=nullptr; //have to initial in global

void processOne(){
    Singleton* instance = Singleton::getSingletonInstance("Bob");
    std::cout << instance->getName() <<std::endl;
}
void processTwo(){
    Singleton* instance = Singleton::getSingletonInstance("Bi");
    std::cout << instance->getName() <<std::endl;
}

int main()
{
    //this is a weak of singleton in multiple thread 
    std::thread t1(processOne);
    std::thread t2(processTwo);
    t1.join();
    t2.join();
    return 0;
}
```
###### Solved the problem in mutiple thread
```
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;
class Singleton{
  private:
  static Singleton* instance; //common resources
  static std::mutex mutex_; //for solve the problem in thread
  std::string name;
  Singleton(){}; //have to put in private to prevent call and created instance
  Singleton(std::string value) : name{value}{};
  public:
  Singleton(Singleton&) = delete; //need to delete copy constructor
  Singleton* operator=(Singleton&) = delete; //need to delete copy assignment
  static Singleton* getSingletonInstance(std::string value); //function static to get instance
  std::string getName();
};

Singleton* Singleton::getSingletonInstance(std::string value){
    if(instance==nullptr){
        std::lock_guard<std::mutex> lock(mutex_); //to make sure one instance created
        if(instance == nullptr){
            instance = new Singleton(value);
        }
    }
    return instance;
}
string Singleton::getName(){
    return name;
}

Singleton* Singleton::instance=nullptr; //have to initial in global
mutex Singleton::mutex_;

void processOne(){
    Singleton* instance = Singleton::getSingletonInstance("Bob");
    std::cout << instance->getName() <<std::endl;
}
void processTwo(){
    Singleton* instance = Singleton::getSingletonInstance("Bi");
    std::cout << instance->getName() <<std::endl;
}

int main()
{
    //solved with mutex and lock_guard 
    std::thread t1(processOne);
    std::thread t2(processTwo);
    t1.join();
    t2.join();
    return 0;
}
```
#### Structual design pattern: simlify the relationship between class and object to make the system flexible and efficient
1. Adapter
```
#include <iostream>
#include <algorithm>

class Target {
 public:
  virtual ~Target() = default;
  virtual std::string Request() const {
    return "Target: The default target's behavior.";
  }
};

// Client using Request from Target
void ClientCode(const Target *target) {
  std::cout << target->Request() << std::endl;
}

// Adaptee have SpecificRequest and client wanna using it
class Adaptee {
 public:
  std::string SpecificRequest() const {
    return ".eetpadA eht fo roivaheb laicepS";
  }
};

// Need to create a class call Adapter
class Adapter : public Target {
 private:
  Adaptee *adaptee_;

 public:
  Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
  std::string Request() const override {
    std::string to_reverse = this->adaptee_->SpecificRequest();
    std::reverse(to_reverse.begin(), to_reverse.end());
    return "Adapter: (TRANSLATED) " + to_reverse;
  }
};

int main(){
    Target *t = new Target;
    ClientCode(t); // Target: The default target's behavior.
    
    //client code using SpecificRequest via the Adapter 
    Adaptee *adaptee = new Adaptee;
    Adapter *adap = new Adapter(adaptee);
    ClientCode(adap); // Adapter: (TRANSLATED) Special behavior of the Adaptee.
    return 0;
}
```

