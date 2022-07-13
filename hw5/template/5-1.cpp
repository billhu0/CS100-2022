
// DO NOT MODIFY THE CODE BELOW
#include <cstddef>

class Array {
public:
    Array();
    explicit Array(std::size_t n);
    explicit Array(int *begin, int *end);
    Array(const Array &other);
    Array &operator=(const Array &other);
    ~Array();
    int &at(std::size_t n);
    const int &at(std::size_t n) const;
    std::size_t size() const;
    bool empty() const;
    void clear();
    Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;
private:
    std::size_t m_size;
    int *m_data;
};

// YOUR CODE STARTS HERE


// YOUR CODE ENDS HERE

int main() {
    // You can test your implementation here, but we will replace the main function on OJ.

    return 0;
}