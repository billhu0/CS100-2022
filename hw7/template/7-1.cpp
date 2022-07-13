#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

// This class is quite simple with only some getters and setters.
// Finish the definitions of these functions first.
class Grade {
 public:
  // This constructor initializes the members with the parameters.
  Grade(const std::string &name, int number, double grade);
  std::string getName() const;
  void setName(const std::string &name);
  int getNumber() const;
  void setNumber(int number);
  double getGrade() const;
  void setGrade(double grade);

 private:
  std::string m_name;
  int m_number;
  double m_grade;
};

struct NameComparator {
  bool operator()(const Grade &a, const Grade &b) const;
};

struct NumberComparator {
  bool operator()(const Grade &a, const Grade &b) const;
};

struct GradeComparator {
  bool operator()(const Grade &a, const Grade &b) const;
};

class Gradesheet {
  friend std::ostream &operator<<(std::ostream &os, const Gradesheet &sheet);

 public:
  Gradesheet();
  ~Gradesheet();
  std::size_t size() const;
  double average() const;
  bool addGrade(const Grade &grade);
  double findByName(const std::string &name) const;
  double findByNumber(int number) const;
  Grade &operator[](std::size_t i);
  const Grade &operator[](std::size_t i) const;
  void sortByName();
  void sortByNumber();
  void sortByGrade();

 private:
  std::vector<Grade> m_grades;
};

int main() {
  Gradesheet sheet;
  sheet.addGrade(Grade("Bob", 1, 95));
  sheet.addGrade(Grade("Carl", 2, 100));
  sheet.addGrade(Grade("Alex", 3, 90));
  sheet.sortByGrade();
  std::cout << "size == " << sheet.size() << "\n" << sheet;
  return 0;
}