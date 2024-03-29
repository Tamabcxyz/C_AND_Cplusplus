★☆☆☆☆: 1 star for easy         
★★☆☆☆: 2 stars for normal          
★★★☆☆: 3 stars for standard            
★★★★☆: 4 stars for hard            
★★★★★: 5 stars extreme         

#### Q?: Choose correct answer (★★★☆☆)
```
pasted code demo
```
<details>
<summary>Result and explain</summary>
Result: ? </br>
Explain: 
</details>

#### Q1: Choose the correct answer (★★☆☆☆)
```
#include <stdio.h>
int main()
{
    printf("%d", printf("%s","Hello World"));
    return 0;
}
// A. Compile error
// B. Hello World11
// C. 11Hello World
```
<details>
<summary>Result and explain</summary>
Result: B  </br>     
Explain: the return type of the function printf is an int value (number character in represent string)
</details>

#### Q2: Choose the correct answer (★★☆☆☆)
```
#include <stdio.h>
int main()
{
    int a, b;
    printf("%d", scanf("%d %d", &a, &b)); // assumsion a=4, b=5
    return 0;
}
// A. 2
// B. 1
// C. 3
// D. 4
```
<details>
<summary>Result and explain</summary>
Result: A   </br>                       
Explain: the return type of the function scanf is and int value.                           
int scanf(const char* format, ...);                          
A positive integer: this means that scanf successfully matched and assigned values to that many variables as specified in the format string.                                   
EOF (End of File): scanf returns EOF when it encounters an error or reaches the end of the input stream. This typically happens when there's a mismatch between the format string and the input data or when there's an input error. EOF is usually defined as a negative integer constant.
</details>

#### Q3: Choose the correct answer (★★★☆☆)
```
#include <stdio.h>
int main()
{
    char s1[20] = "geeksquiz"; // can't assign another value
    char s2[] = "geeksquiz"; // can't assign another value
    char *s3  = "geeksquiz"; // can be assign another value
    printf("s1: %ld, s2: %ld, s3: %ld", sizeof(s1), sizeof(s2), sizeof(s3));
    return 0;
}
// A. Compile error
// B. s1: 20, s2: 10, s3: 8
// C. s1: 10, s2: 10, s3: 10
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: the size of s1 specifying with 20 bytes. s2 without specifying its size, the size is automatically determined based on the length of the string. The size of s3 is determined by the size of a pointer 4 bytes (32-bit system) or 8 bytes (64-bit system) 
</details>

#### Q4: Choose the correct answer (★☆☆☆☆)
```
#include <stdio.h>
int i = 0; //define
int a; //declare
extern int b; //declare
void func1(); //declare
extern void func2(); //declare
void func3(){} //define
int main(){
    return 0;
}
```
<details>
<summary>Result and explain</summary>
Result: ? </br>
Explain: A declaration introduces the name and type of a variable, function, or other program entity to the compiler without allocating memory or specifying its initial value. A definition not only declares the entity but also allocates memory (for variables) or provides the function body (for functions). It specifies the storage location and, for variables, an initial value
</details>

#### Q5: Choose the correct answer (★☆☆☆☆)
```
#include <stdio.h>
int main(){
    char c = 'a';
    int x = c++;
    printf("%c, %d", c, x);
    return 0;
}
// A. Compile error
// C. a, 97
// D. b, 97
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: x = c++ break down x=c, c=c+1, so now x='a' (convert 'a' to in = 97)
</details>

#### Q6: Choose the correct answer (★★★★★)
```
#include <stdio.h>
typedef struct{
    int x;
    float y;
} Mystruct;

int main(){
    Mystruct s{25};
    printf("%d, %f\n", s.x, s.y);
    return 0;
}
// A. Compile error
// B. Uncertain
// C. 25, 0.0
// D. 0, 25.0
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: The above code can compile successfully in C++, but it fails in the C compiler, In C, designated initializers for structures are not supported, which means you cannot initialize individual members of a structure by specifying their names within curly braces.
</details>

#### Q7: Choose the correct answer (★★★★☆)
```
#include <stdio.h>
typedef struct{
    int x;
    float y;
} Mystruct;

int main(){
    Mystruct s = {25.0f};
    printf("%d, %f\n", s.x, s.y);
    return 0;
}
// A. Compile error
// B. Uncertain
// C. 25, 0.0
// D. 0, 25.0
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: first number will initialize for first member of struct
</details>

#### Q8: Choose the correct answer (★★★☆☆)
```
#include <stdio.h>
int main(){
    int a = 1;
    int b = 2;
    int c = 3;
    int d = a < b > c;
    printf("%d", d);
    return 0;
}
// A. 0
// B. 1
// C. 2
// D. 3
```
<details>
<summary>Result and explain</summary>
Result: 0 </br>
Explain: d = a < b > c break down code 1 < 2 return 1 (true), 1 > 3 return 0 (false)
</details>

#### Q9: Choose the correct answer (★★☆☆☆)
```
#include <stdio.h>
int main(){
    int a = 0;
    for(scanf("%d", &a); a; printf("%d", a--)); // assumtion a = 5
    return 0;
}
// A. Compile error
// B. 0
// C. 12345
// D. 54321
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: 
</details>

#### Q10: Choose the correct answer (★★☆☆☆)
```
#include <stdio.h>
int main(){
    printf("%s", "Are" "You" "Ok");
    return 0;
}
// A. Compile error
// B. AreYouOk
// C. Are You Ok
// D. Are
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: 
</details>

#### Q11: Choose the correct answer (★★★☆☆)
```
#include <stdio.h>
int main(){
    char c = 'abc';
    printf("%c", c);
    return 0;
}
// A. Compile error
// B. a
// C. b
// D. c
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: 'abc' is not a valid character literal but the compiler try to initialize the c variable by last charater
</details>

#### Q12: Choose the correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
class Base{  virtual void func(){}};
class D1 : public Base{};
class D2 : public Base{};
int main()
{
    Base *b = new D1();
    D2 *d2 = dynamic_cast<D2*>(b);
    D1 *d1 = dynamic_cast<D1*>(b);
    std::cout << d2 << ", "<< d1 << std::endl;
    return 0;
}
// A. Compile error
// B. 0, address of d1
// C. address of d2, 0
// D. address of d2, address of d1
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: can't cast b to D2 because b pointer points to D1 that's the reason output d2 is 0
</details>

#### Q13: Choose the correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
int x = 10;
void func(const int x){
    std::cout << x + x << ", " << ::x + x << std::endl;
}
int main()
{
    func(20);
    return 0;
}
// A. Compile error
// B. 20, 20
// C. 20, 30
// D. 40, 30
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: to call a local variable we can use ::
</details>

#### Q14: Choose the correct answer (★★★☆☆)
```
#include <stdio.h>

int main()
{
    printf("%lu, %lu, %lu", sizeof(int), sizeof(int *), sizeof(int **));
    return 0;
}
// A. 4, 8, 8
// B. 4, 4, 8
// C. 2, 4, 4
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: size of the integer is 4, size of pointer is depend on the system if system 32 bit size of pointer is 4, 8 for 64 bit
</details>

#### Q15: Choose the correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
int main()
{
    int i = 10;
    int *p = &i;
    int &ri = i;
    int &ra = 20;
    return 0;
}
// A. No error
// B. 5, 6
// C. 7, 8
// D. 8
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: line 5, 6 is valid, line 7 only compile with c++ compiler (it's syntax of c++ features), line 8 error because we can't create lvalue reference to rvalue
</details>

#### Q16: Choose the correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
class Myclass{
  private:
  int a;
  static int b;
};
int Myclass::b = 0;
int main()
{
    cout << sizeof(Myclass);
    return 0;
}

// A. Compile error
// B. 4
// C. 8
// D. 0
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: Static data members don't occupy the size of the class.
</details>

#### Q17: Choose the correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
int *func(){
    int arr[]={1,2,3};
    return arr;
}
int main()
{
    int *ptr = func();
    std::cout << ptr[0] << ", " << ptr[1] << ", " << ptr[2] << std::endl;
    return 0;
}

// A. Compile error
// B. Warning and empty print
// C. 1, 2, 3
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: arr in func store in stack after execute arr will be free
</details>

#### Q18: Choose the correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
int *func(){
    static int arr[]={1,2,3};
    return arr;
}
int main()
{
    int *ptr = func();
    std::cout << ptr[0] << ", " << ptr[1] << ", " << ptr[2] << std::endl;
    return 0;
}

// A. Compile error
// B. Warning and empty print
// C. 1, 2, 3
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: arr in func is a static variable; it's not stored in the stack; it's stored in a memory area called the global memory area.
</details>

#### Q19: Choose the correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class Base1{
  public:
  Base1(){std::cout << "Base1 constructor" << std::endl;}
  ~Base1(){std::cout << "Base1 destructor" << std::endl;}
};
class Base2{
  public:
  Base2(){std::cout << "Base2 constructor" << std::endl;}
  ~Base2(){std::cout << "Base2 destructor" << std::endl;}
};
class Derived : public Base1, public Base2{
  public:
  Derived(){std::cout << "Derived constructor" << std::endl;}
  ~Derived(){std::cout << "Derived destructor" << std::endl;}
};
int main()
{
    Derived d;
    return 0;
}

// A. Compile error
// B. Derived constructor
// C.
// Base1 constructor
// Base2 constructor
// Derived constructor
// Derived destructor
// Base2 destructor
// Base1 destructor
// D.
// Derived constructor
// Derived destructor
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: A derived class will call the constructor of the base class first.
</details>

#### Q20: Choose the correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class Base{
  private:
    int i;
  public:
    Base(int x) : i(x) {}
    void show(){
        std::cout << "i: " << i << std::endl;
    }
};
void print(Base b){b.show();}
int main()
{
    Base b(10);
    print(b);
    print(20);
    return 0;
}
// A. Compile error
// B.
// i: 10
// i: 20
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: compiler auto-implicitly converts 20 and assigns it to base class (it's bad, need explicit keyword in constructor of Base class to fix it)
</details>

#### Q21: Choose the correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class Base{
  private:
    int i;
  public:
    explicit Base(int x) : i(x) {}
    void show(){
        std::cout << "i: " << i << std::endl;
    }
};
void print(Base b){b.show();}
int main()
{
    Base b(10);
    print(b);
    print(20);
    return 0;
}
// A. Compile error
// B.
// i: 10
// i: 20
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: could not convert ‘20’ from ‘int’ to ‘Base’
</details>

#### Q22: Choose the correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
class BaseA{
  private:
    int a;
  public:
    explicit BaseA(int x) : a(x) {}
};
class BaseB{
  private:
    int b;
  public:
    explicit BaseB(int x) : b(x) {}
    operator BaseA() const{
        return BaseA(b);
    }
};
int main()
{
    BaseA a = BaseB(10);
    return 0;
}
// A. Compile error
// B. Compile success
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: in BaseB have implemented operator BaseA that's convert BaseB class to BaseA class (conversion operator)
</details>

#### Q23: Choose the correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
    private:
    int arr[10];
};
class B : public A{};
class C : public A{};
class D : public B, public C{};
int main()
{
    std::cout << sizeof(D) << std::endl;
    return 0;
}
// A. Compile error
// B. 40
// C. Compile success
// D. 80
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: arr is initial with 10 elements have type interger; B inherit from A, then size of B is 40, the same with C, D inherit for B and C therefore 40 + 40 = 80
</details>

#### Q24: Choose the correct answer (★★★★★)
```
#include <iostream>
using namespace std;
class A{
    private:
    int arr[10];
};
class B : virtual public A{};
class C : virtual public A{};
class D : public B, public C{};
int main()
{
    std::cout << sizeof(D) << std::endl;
    return 0;
}
// A. Compile error
// B. 56
// C. Compile success
// D. 40
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: Both classes B and C virtually inherit from class A. This means they share a single instance of the base class A. Virtual inheritance is used to ensure that there's only one copy of the base class A in the hierarchy. Class D inherits from both B and C. D also shares the same virtual base class A. That's the reason why D have 40 bytes, but 40 not exactly bytes in this case. Each virtual base class subobject of A adds some overhead, which includes information for runtime type identification (RTTI) and other bookkeeping data. This overhead is compiler-dependent and is typically a few bytes. 40 bytes (for int a[10]) X bytes (overhead for the first virtual base class A) Y bytes (overhead for the second virtual base class A). So the result is 40 + X + Y, In this case X + Y = 16
</details>

#### Q25: Choose the correct answer (★★★★★)
```
#include <iostream>
using namespace std;
class A{
    private:
    int arr[10];
};
class B : virtual public A{};
class C : public A{};
class D : public B, public C{};
int main()
{
    std::cout << sizeof(D) << std::endl;
    return 0;
}
// A. Compile error
// B. 56
// C. Compile success
// D. 88
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: A class have arr is 40 bytes, B virtually inherit from class A so B 48 bytes. C inherit from class A 40 bytes. D inherit from two class B and C 48 + 40 = 88
</details>

#### Q26: Choose the correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  public:
  void call(){ std::cout << "call A" << std::endl;  }
};
class B : public A{
  public:
  void call(){ std::cout << "call B" << std::endl;  }
};

class C : public B{};

int main()
{
    C c;
    c.call();
    return 0;
}
// A. Compile error
// B. call B
// C. call A
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: Because that's the behavior of inheritant C inheriting from B and B inheriting from A, object C will find the call function directly if B does not have a call function; if B does not have a call function, it will find directly if B is A, and check if A class has a call function. In this case, B class has a call function, therefore the correct answer is B.
</details>

#### Q27: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class Base{
  public:
  Base(){ std::cout << "Constructor Base" << std::endl; }
};
typedef Base* pointerBase;
int main()
{
   pointerBase p1, p2;
   return 0;
}
// A. Compile error
// B. The constructor will call two times
// C. The constructor will call one time
// D. The constructor not call
```
<details>
<summary>Result and explain</summary>
Result: D </br>
Explain: pointerBase is an alias present for Base pointer, in this case both of them p1 and p2 is pointer it't not an object that's the reason why the constructor not call
</details>

#### Q28: Choose correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
class Base{
  public:
  Base(){ std::cout << "Constructor Base" << std::endl; }
};
int main()
{
   Base* p1, p2;
   return 0;
}
// A. Compile error
// B. The constructor will call two times
// C. The constructor will call one time
// D. The constructor not call
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: p1 is an pointer of Base class (it's not an oject not call contstructor), p2 is an object
</details>

#### Q29: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private:
  int x, y;
  public:
  A(int a = 0, int b = 0) : x(a), y(b) {}
  int getX(){ return x; }
  int getY(){ return y; }
  A& incX(){ x++; return *this; }
  A& incY(){ y++; return *this; }
};
int main()
{
   A a;
   a.incX().incY().incX();
   std::cout << "x=" << a.getX() << ", y=" << a.getY() << std::endl;
   return 0;
}
// A. Compile error
// B. x=0, y=0
// C. x=2, y=1
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: after calling incX() or incY(), it's returning a reference to object A; therefore, we can call it many times (key word: chaining methods)
</details>

#### Q30: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private:
  int x, y;
  public:
  A(int a = 0, int b = 0) : x(a), y(b) {}
  int getX(){ return x; }
  int getY(){ return y; }
  A incX(){ x++; return *this; }
  A incY(){ y++; return *this; }
};
int main()
{
   A a;
   a.incX().incY().incX();
   std::cout << "x=" << a.getX() << ", y=" << a.getY() << std::endl;
   return 0;
}
// A. Compile error
// B. x=1, y=0
// C. x=1, y=1
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: after calling incX() or incY(), it's returning a new object A (key word: chaining methods)
</details>

#### Q31: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private:
  int x;
  public:
  A(int a = 0) : x(a) {}
  void setX(int a) const { x = a; }
  int getX(){ return x; }
};
int main()
{
   A a{};
   a.setX(5);
   std::cout << "x=" << a.getX() << std::endl;
   return 0;
}
// A. Compile error
// B. x=5
// C. x=0
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: setX define as const function so only read can not modify the value
</details>

#### Q32: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private:
  mutable int x;
  public:
  A(int a = 0) : x(a) {}
  void setX(int a) const { x = a; }
  int getX(){ return x; }
};
int main()
{
   A a{};
   a.setX(10);
   std::cout << "x=" << a.getX() << std::endl;
   return 0;
}
// A. Compile error
// B. x=10
// C. x=0
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: setX define as const function so only read can not modify the value but key word mutable allow change value of x
</details>

#### Q33: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private:
  int x;
  public:
  A(int a = 0) : x(a) {}
  int getX() { return x; }
};
int main()
{
   const A a{};
   std::cout << "x=" << a.getX() << std::endl;
   return 0;
}
// A. Compile error
// B. x=0
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: object *a* mask as const so *a* can be call function const. The code above will raise error 
</details>

#### Q34: Choose correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
class Myclass{
  private:
  int x;
  public:
  Myclass(int a = 1) : x(a) {}
  operator double(){ return (double)x; }
  operator int(){ return x; }
};
void func(double x){ std::cout << "double x=" << x << std::endl; }
void func(int x){ std::cout << "int x=" << x << std::endl; }
int main()
{
   Myclass m;
   func(m);
   return 0;
}
// A. Compile error
// B. double x=0
// C. int x=0
// D. int x=1
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: in Myclass have define two conversion operator double and int when call func method the compiler can not decide what exactly function need to call
</details>

#### Q35: Choose correct answer (rated)
```
#include <iostream>
using namespace std;
class A{
  private:
  int x;
  public:
  void func(){ std::cout << "A" << std::endl; }
};
class B{
  private:
  int x;
  public:
  virtual void func(){ std::cout << "B" << std::endl; }
};
int main()
{
   std::cout << sizeof(A) << sizeof(B) << std::endl;
   return 0;
}
// A. Compile error
// B. 416
// C. 48
// D. 44
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: A is nomal class with member x have 4 bytes, B is a class with virtual function that will create pointer point to vtable (4+8) and add some padding that's the reason why size of B class is 16
</details>

#### Q36: Choose correct answer (★★☆☆☆)
```
#include <iostream>
using namespace std;
class A{
  public:
    virtual void show(int a)=0;
};
class B : public A{
  private:
    int x;
  public:
    void show() { std::cout << "show" << std::endl; }
};
int main()
{
   B b;
   b.show();
   return 0;
}
// A. Compile error
// B. show
// C. Nothing print out
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: class B inherit from A but do not override show functin with parameter integer
</details>

#### Q37: Choose correct answer (★★☆☆☆)
```
#include <iostream>
using namespace std;
class A{
  public:
    virtual void show(int a)=0;
};
class B : public A{
  private:
    int x;
  public:
    void show() { std::cout << "show" << std::endl; }
};
int main()
{
   B *b;
   return 0;
}
// A. Compile error
// B. show
// C. Nothing print out
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: b is pointer not object so not call constructor
</details>

#### Q38: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  public:
    A(){ std::cout << "Constructor A" << std::endl; }
};
int main()
{
   A a();
   return 0;
}
// A. Compile error
// B. Constructor A
// C. Waring and nothing print
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: empty parentheses were disambiguated as a function declaration
</details>

#### Q39: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private: 
    int &x;
  public:
    A(int &a) : x(a){}
    int &getX(){ return x; }
};
int main()
{
   int x = 10;
   A a{x};
   std::cout << a.getX();
   x = 20;
   std::cout << a.getX();
   return 0;
}
// A. Compile error
// B. 1010
// C. 1020
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: because x is reference variable
</details>

#### Q30: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private: 
    static const int x = 100;
  public:
    static int getX(){ return x; }
};
int main()
{
   std::cout << A::getX();
   return 0;
}
// A. Compile error
// B. 100
// C. 0
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: 
</details>

#### Q31: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private: 
    static int x;
  public:
    void setX(int a) { x = a; }
    static int getX() const{ return x; }
};
int A::x = 10;
int main()
{
   std::cout << A::getX();
   return 0;
}
// A. Compile error
// B. 100
// C. 10
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: static member function can't be const, function mask with const to protect no-const variable
</details>

#### Q30: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{ public: A(){ std::cout << "A"; } };
class B{ public: B(){ std::cout << "B"; } };
class C{ public: C(){ std::cout << "C"; } };
int main()
{
   class A a;
   B b;
   class C c;
   return 0;
}
// A. Compile error
// B. ABC
// C. B
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: would be fine when create an object with class keyword
</details>

#### Q31: Choose correct answer (★★★☆☆)
```
#include <iostream>
using namespace std;
class A{
  private: 
    int x;
  public:
    int &getX(){ return x; }
    void printX() { std::cout << x <<std::endl; }
};
int main()
{
   class A a;
   a.getX() = 10;
   a.printX();
   return 0;
}
// A. Compile error
// B. 0
// C. 10
```
<details>
<summary>Result and explain</summary>
Result: C </br>
Explain: getX return a reference value of x can be change at caller side
</details>

#### Q32: Choose correct answer (★★★★☆)
```
#include <iostream>
using namespace std;
class C;
class A{
  private: 
    int x;
    void call() { std::cout << "call A" <<std::endl; }
  friend C;
};
class B : public A{
  public:
    void call() { std::cout << "call B" <<std::endl; }
};
class C : public B{
  public:
    void call() { A::call(); }
};
int main()
{
   C c;
   c.call();
   return 0;
}
// A. Compile error
// B. call A
// C. call B
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: in class a we have friend C that's allow C class can access private of A class
</details>

#### Q33: Choose correct answer (★★★☆☆)
```
#include <iostream>
#include <functional>

using namespace std;
void func(int &a, int &b){
    std::cout << "a=" << a << ", b=" << b << std::endl;
    ++a;
    ++b;
}

int main()
{
    int a = 1, b = 2;
    std::function<void()> f = std::bind(func, std::ref(a),b);
    
    a = 10;
    b = 20;
    
    std::cout << "Before: " << "a=" << a << ", b=" << b << std::endl;
    f();
    std::cout << "After: " << "a=" << a << ", b=" << b << std::endl;
    
    return 0;
}
// A. Compile error 
// B. Before: a=10, b=20
//    a=10, b=2
//    After: a=11, b=20
// C. Before: a=10, b=20
//    a=10, b=20
//    After: a=11, b=20
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: the result of Before *a* and *b* updated by main ==> a=10, b=20. When call f() at this time will execute func with param *a*  is passed by reference so it reflects the value of *a* in main, *b* is passed by value, so it retains its original value, which is 12 ==>a=10, b=2. when call f() *a* is +1 and value of b at this time is 20 ==>After: a=11, b=20
</details>

#### Q34: Choose correct answer (★★★☆☆)
```
// in extra.c file
extern int intMain;
void myFunc(){
    intMain = 200;
}

// int main.cpp file
#include <iostream>
using namespace std;
int intMain;
void myFunc();
int main()
{
    intMain = 100;
    std::cout << "intMain=" << intMain << std::endl;
    myFunc();
    std::cout << "intMain=" << intMain << std::endl;
    return 0;
}

// A. Compile error 
// B. intMain=100
//    intMain=200
// C. intMain=100
//    intMain=100
```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: "extern" keyword provide the infomation intMain variable have declared from another location
</details>

#### Q35: Choose correct answer (★★★★☆)
```
// in extra.c file
extern int intMain;
void myFunc(){
    intMain = 200;
}

// int main.cpp file
#include <iostream>
using namespace std;
static int intMain;
void myFunc();
int main()
{
    intMain = 100;
    std::cout << "intMain=" << intMain << std::endl;
    myFunc();
    std::cout << "intMain=" << intMain << std::endl;
    return 0;
}

// A. Compile error 
// B. intMain=100
//    intMain=200
// C. intMain=100
//    intMain=100
```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: local variable intMain declare is a static so it only modify inside main.cpp not outside (static variable can not be extern)
</details>

#### Q36: Choose correct answer (★★★☆☆)
```
// in extra.c file
extern void change_system_lock(int system_lock);
void myFunc(){
    change_system_lock(0);
}

// int main.cpp file
#include <iostream>
using namespace std;
void myFunc();
void change_system_lock(int system_lock);
int main()
{
    myFunc();
    return 0;
}
void change_system_lock(int system_lock){
    std::cout << "system_lock=" << system_lock << std::endl;
}

// A. Compile error 
// B. system_lock=0

```
<details>
<summary>Result and explain</summary>
Result: B </br>
Explain: we can use extern keyword to provide for compiler know the function have implement in another location
</details>

#### Q37: Choose correct answer (★★★★☆)
```
// in extra.c file
extern void change_system_lock(int system_lock);
void myFunc(){
    change_system_lock(0);
}

// int main.cpp file
#include <iostream>
using namespace std;
void myFunc();
void change_system_lock(int system_lock);
int main()
{
    myFunc();
    return 0;
}
static void change_system_lock(int system_lock){
    std::cout << "system_lock=" << system_lock << std::endl;
}

// A. Compile error 
// B. system_lock=0

```
<details>
<summary>Result and explain</summary>
Result: A </br>
Explain: static keyword prevent access from outside it's private function (static function can not be extern)
</details>