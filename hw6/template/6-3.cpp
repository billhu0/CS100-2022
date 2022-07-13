#include <string>

// REMOVE THIS CLASS WHEN SUBMITTING!!!
class Point {
  double x{0}, y{0};
  std::string label;

 public:
  Point(double x0, double y0, const std::string &l = "")
      : x(x0), y(y0), label(l) {}
  Point() = default;
  double get_x() const {
    return x;
  }
  double get_y() const {
    return y;
  }
  std::string get_label() const {
    return label;
  }
  Point &set_x(double x0) {
    x = x0;
    return *this;
  }
  Point &set_y(double y0) {
    y = y0;
    return *this;
  }
  Point &set_label(const std::string &l) {
    label = l;
    return *this;
  }
};

class Point_counted {
  friend class Point_handle;

  // All the members are private.

  Point p;
  unsigned cnt;
  
  // Define some helper member functions if you need.
};

class Point_handle {
  Point_counted *ptr;
  // Your code here.
};