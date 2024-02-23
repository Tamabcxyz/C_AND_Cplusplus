/**
 * can not create object from an abstract class
 * pure virtual function specified with "=0" in its declaration
 */

#include <iostream>
#include <vector>
using namespace std;
class Shape { // abstract class Shape
private:
public:
  virtual void draw() = 0;   // pure virtual function
  virtual void rotate() = 0; // pure virtual function
  virtual ~Shape() {}
};

class Open_Shape : public Shape { // abstract class
public:
  virtual ~Open_Shape() {}
};

class Close_Shape : public Shape { // abstract class
public:
  virtual ~Close_Shape() {}
};

class Line : public Open_Shape { // concreate class
public:
  virtual void draw() override { std::cout << "draw a line" << std::endl; }
  virtual void rotate() override {
    std::cout << "rotating a line" << std::endl;
  }
  virtual ~Line() {}
};

class Circle : public Close_Shape { // concreate class
public:
  virtual void draw() override { std::cout << "draw a circle" << std::endl; }
  virtual void rotate() override {
    std::cout << "rotating a circle" << std::endl;
  }
  virtual ~Circle() {}
};

class Square : public Close_Shape { // concreate class
public:
  virtual void draw() override { std::cout << "draw a square" << std::endl; }
  virtual void rotate() override {
    std::cout << "rotating a square" << std::endl;
  }
  virtual ~Square() {}
};

void refresh(const std::vector<Shape *> &shapes) {
  for (const auto &s : shapes) {
    s->draw();
  }
}

int main() {
  // Shape s; // error
  // Shape *ptrs = new Shape;// error

  Shape *p1 = new Circle;
  Shape *p2 = new Line;
  Shape *p3 = new Square;
  std::vector<Shape *> shapes{p1, p2, p3};
  refresh(shapes);
  delete p1;
  delete p2;
  delete p3;
  return 0;
}