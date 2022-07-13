#include <cstddef>

class Matrix {
public:
    typedef double Scalar;
    typedef std::size_t Index;

    explicit Matrix(Index rows, Index cols);
    Matrix(const Matrix &other);
    Matrix& operator=(const Matrix &other);
    ~Matrix();
    Index rows() const;
    Index cols() const;
    Scalar& at(Index r, Index c);
    const Scalar& at(Index r, Index c) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix transpose() const;
    Matrix block(Index r, Index c, Index p, Index q) const; // Block of size p x q, starting at (r,c)
    Scalar trace() const; // For square matrix
    Scalar determinant() const; // For square matrix

private:
    // Define your private member variables and functions here

};

