// virtual members
#include <iostream>
using namespace std;

class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { width=a; height=b; }
    virtual int area ()
      { return 0; }
};

class Rectangle: public Polygon {
  public:
    int area ()
      { return width * height; }
};

class Triangle: public Polygon {
  public:
    int area ()
      { return (width * height / 2); }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  Polygon poly;
  const int SIZE=3;
  Polygon * ppoly[SIZE];
  ppoly[0] = &rect;
  ppoly[1] = &trgl;
  ppoly[2] = &poly;
  for(int i=0;i<SIZE;i++){
      ppoly[i]->set_values (4,5);
      cout << ppoly[i]->area() << '\n';
  }
  return 0;
}