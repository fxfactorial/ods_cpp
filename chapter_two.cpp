#include <iostream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include <numeric>
#include <list>
#include <random>

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

  T& peak(void) { return a[n - 1]; };

  // Neat way to add items at the end of the array, and it just pushes
  // stuff to the left.
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
    // Push everything to the left by one spot
    for (size_t j = i; j < n - 1; j++) a[j] = a[j + 1];
    n--;
    // If the array is getting way too small then we resize
    if (a.length() >= 3 * n) resize();
    return x;
  }
};

// This one uses std::copy* funcs to improve speed,
// C would have used memmove, or memcpy
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
  array<T> a;
  size_t j, n;

  void resize(void)
  {
    array<T> b(std::max<size_t>(1, 2 *n));
    for (size_t k = 0; k < n; k++)
      b[k] = a[(j + k) % a.length()];
    a = b;
    j = 0;
  }

  T& remove(void)
  {
    T& x = a[j];
    j = (j + 1) % a.length();
    n--;
    if (a.length() >= 3 * n) resize();
    return x;
  }

  bool add(T x)
  {
    if (n + 1 > a.length()) resize();
    a[(j + n) % a.length()] = x;
    n++;
    return true;
  }
};


template<typename T>
class array_deque {
private:
  array<T> a;
  size_t j, n;
public:
  T& get(size_t i)
  {
    return a[(j + i) % a.length()];
  }

  T& set(size_t i, T x)
  {
    T& y = a[(j + 1) % a.length()];
    a[(j + i) % a.length()] = x;
    return y;
  }

  void resize(void)
  {

  }

  void add(size_t i, T x)
  {
    if (n + 1 > a.length()) resize();
    // shift a[0], ..., a[i - 1] left one position
    if (i < n / 2) {
      j = (j == 0) ? a.length() - 1 : j - 1;
      for (size_t k = 0; k <= i - 1; k++)
	a[(j + k) % a.length()] = a[(j + k + 1) % a.length()];
    }
    // Otherwise we shift a[i], ..., a[n - 1] right one position
    else {
      for (size_t k = n; k > i; k--)
	a[(j + k) % a.length()] = a[(j + k - 1) % a.length()];
    }
    a[(j + 1) % a.length()] = x;
    n++;
  }

  T& remove(size_t i)
  {
    T& x = a[(j + 1) % a.length()];
    if (i < n / 2) {
      for (size_t k = i; k > 0; k--)
	a[(j + k) % a.length()] = a[(j + k - 1) % a.length()];
      j = (j + 1) % a.length();
    } else {
      for (size_t k = i; k < n - 1; k++)
	a[(j + k) % a.length()] = a[(j + k + 1) % a.length()];
    }
    n--;
    if (3 * n < a.length()) resize();
    return x;
  }
};

template<typename T>
class dual_array_deque {
private:
  array_stack<T> front, back;
public:
  size_t size(void) { return front.size() + back.size();}

  T& get(size_t i)
  {
    if (i < front.size())
      return front.get(front.size() - i - 1);
    else
      return back.get(i - front.size());
  }

  T& set(size_t i, T x)
  {
    if (i < front.size())
      return front.set(front.size() - i - 1, x);
    else
      return back.set(i - front.size(), x);
  }

};

auto&& range(size_t upto)
{
  std::vector<int> handle(upto);
  std::iota(std::begin(handle), std::end(handle), 0);
  return std::move(handle);
}

int main(void)
{
  using namespace std::string_literals;
  using std::string;

  for (auto& h : range(10))
    std::cout << "Data: " << h;
  // std::cout << std::endl;
  // std::vector<int> x(10);
  // std::iota(std::begin(x), std::end(x), 0);
  // for (auto h : x) std::cout << "Data: " << h << std::endl;

  // std::list<int> l(10);
  // std::iota(l.begin(), l.end(), 0);

  // std::vector<std::list<int>::iterator> v(l.size());

  // std::iota(v.begin(), v.end(), l.begin());

  // std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});

  // std::cout << "Contents of the list: ";
  // for(auto n: l) std::cout << n << ' ';
  // std::cout << '\n';

  // std::cout << "Contents of the list, shuffled: ";
  // for(auto i: v) std::cout << *i << ' ';
  // std::cout << '\n';


  return 0;
}
