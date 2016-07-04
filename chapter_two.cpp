#include <iostream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>

template <typename T>
class array {
private:
  T *a = nullptr;
  size_t length_ = 0;
public:
  size_t length(void) { return length_; }
  array(void) {};
  array(size_t len)
  {
    length_ = len;
    a = new T[length_];
  }

  T& operator[](size_t i)
  {
    if (i >= length_) throw std::out_of_range{"Out of range"};
    return a[i];
  }

  // This is copy operator
  array<T>& operator=(array<T>& b)
  {
    if (a != nullptr) delete[] a;
    a = b.a;
    b.a = nullptr;
    length_ = b.length();
    return *this;
  }
  ~array(void){ delete[] a;}
};

template<typename T>
class array_stack {
private:
  array<T> a;
  size_t n;
public:
  array_stack(size_t size) : a(array<T>{size}), n(size) {}
  size_t size() { return n; }

  T& get(size_t i) { return a[i]; }

  T& peak(void) { return a[0]; };

  void push(T item) { add(n, item); }

  T& pop(void) { return remove(n - 1); }

  // Gives back the old value;
  T set(size_t i, T x)
  {
    T y = a[i];
    a[i] = x;
    return y;
  }

  void resize(void)
  {
    array<T> b{ std::max<size_t>(2 * n, 1)};
    for (size_t i = 0; i < n; i++) b[i] = a[i];
    a = b;
  }

  void add(size_t i, T x)
  {
    if (n + 1 > a.length()) resize ();
    // Push everything to the right by 1 spot, the previous call to
    // resize ensures that we'll always have enough space.
    for (size_t j = n; j > i; j--) a[j] = a[j - 1];
    a[i] = x;
    n++;
  }

  T& remove(size_t i)
  {
    T& x = a[i];
    for (size_t j = i; j < n - 1; j++) a[j] = a[j + 1];
    // Push everything to the left by one spot
    n--;
    // If the array is getting way too small then we resize
    if (a.length() >= 3 * n) resize();
    return x;
  }
};

template<typename T>
class fast_array_stack {
private:
  size_t n = 0;
  array<T> a = nullptr;

  void resize(void)
  {
    array<T> b{std::max<size_t>(1, 2 * n)};
    std::copy(a + 0, a + n, b + 0);
    a = b;
  }

  void add(size_t i, T x)
  {
    if (n + 1 > a.length()) resize();
    std::copy_backward(a + i, a + n, a + n + 1);
    a[i] = x;
    n++;
  }

};

template<typename T>
class array_queue {
private:
  array<T> a_;
  size_t j, n;
};

int main(void)
{
  using namespace std::string_literals;
  using std::string;

  array_stack<char> handle{10};
  handle.push('a');
  handle.push('b');
  handle.push('c');
  std::cout << handle.pop() << std::endl;
  std::cout << handle.pop() << std::endl;

  return 0;
}
