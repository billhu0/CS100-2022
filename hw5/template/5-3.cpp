#include <iostream>
#include <string>

class Expr_node {
 public:
  Expr_node() = default;
  virtual double eval() const = 0;
  virtual std::string to_string() const = 0;
  virtual ~Expr_node() = default;
  Expr_node(const Expr_node &) = delete;
  Expr_node &operator=(const Expr_node &) = delete;
};

class Number_node : public Expr_node {
  friend Number_node *make_number(double);
  double value;
  Number_node(double val) : value(val) {}
  virtual double eval() const override;
  virtual std::string to_string() const override;
};

inline Number_node *make_number(double value) {
  return new Number_node(value);
}

int main() {
  Expr_node *expr_tree = make_divide(
      make_plus(make_number(3), make_multiply(make_number(4), make_number(5))),
      make_number(6));
  std::cout << expr_tree->eval() << std::endl;
  std::cout << expr_tree->to_string() << std::endl;
  delete expr_tree;
  Expr_node *bonus_tree =
      make_plus(make_exp(make_sin(make_number(3))), make_number(1));
  std::cout << bonus_tree->eval() << std::endl;
  std::cout << bonus_tree->to_string() << std::endl;
  delete bonus_tree;
  return 0;
}