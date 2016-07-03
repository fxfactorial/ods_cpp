#include <iostream>
#include <string>
#include <exception>
#include <algorithm>

template <typename T>
class node {
public:
  T data;
  node *next;
  node(T x0) : data(x0), next(nullptr) {}
};

template<typename T>
class list {
private:
  node<T> *head, *tail;
  size_t n;
public:
  auto& push(T x)
  {
    auto *u = new node<T>{x};
    u->next = head;
    head = u;
    if (n == 0)
      tail = u;
    n++;
    return x;
  }

  auto pop(void)
  {
    if (n == 0) throw std::out_of_range{"Fucked"};
    T x = head->data;
    node<T> *u = head;
    head = head->next;
    delete u;
    if (--n == 0) tail = nullptr;
    return x;
  }

  auto add(T x)
  {
    auto *u = new node<T>{x};
    n == 0 ? head = u : tail->next = u;
    tail = u;
    n++;
    return true;
  }

};

int main(void)
{
  using std::string;
  auto handle = new list<string>{};
  handle->add("Hello");
  handle->add("More");

  return 0;
}
