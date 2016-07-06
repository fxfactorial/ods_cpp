#include <string>
#include <algorithm>
#include <iostream>

#include "chapter_two.cpp"

template<typename T>
struct node {
  T data;
  node *next, *prev;
};

template<typename T>
struct double_linked_list {
private:
  node<T> dummy;
  size_t n;
  auto get_node_at_index(size_t i)
  {
    node<T> *p;
    if (i < n / 2) {
      p = dummy.next;
      for (size_t j = 0; j < i; j++) p = p->next;
    } else {
      p = &dummy;
      for (size_t j = n; j > i; j--) p = p->prev;
    }
    return p;
  }

public:
  double_linked_list(void) { dummy.next = &dummy; dummy.prev = &dummy; }

  auto get(size_t index) { return get_node_at_index(index); }

  auto set(size_t index, T new_item)
  {
    node<T> *u = get_node_at_index(index);
    T y = u->data;
    u->data = new_item;
    return y;
  }

  auto add_before(node<T> *w, T x)
  {
    node<T> *u = new node<T>;
    u->data = x;
    u->prev = w ->prev;
    u->next = w;
    u->next->prev = u;
    u->prev->next = u;
    n++;
    return u;
  }

  auto add(size_t i, T x)
  {
    add_before(get_node_at_index(i), x);
  }

  auto remove(size_t i)
  {
    node<T> *w = get_node_at_index(i);
    T x = w->data;
    w->prev->next = w->next;
    w->next->prev = w->prev;
    delete w;
    n--;
    return x;
  }

};

template <typename T>
class bounded_deque : public array_deque<T> {
public:

  bounded_deque(size_t b)
  {
    this->n = 0;
    this->j = 0;
    array<T> z(b + 1);
    this->a = z;
  }

  void add(size_t i, T x) { array_deque<T>::add(i, x); }
  bool add(T x) { array_deque<T>::add(this->size(), x); return true;}
  void resize() { }

};


int main(void)
{
  using std::string;

  {
    using namespace std::string_literals;
    double_linked_list<string> handle{};
    array<string> foo{10};
    handle.add(0, "Hello");
    // handle.remove(1);
    // handle.cycle(3, [](auto item){ std::cout << "Data: " << item << std::endl; });
  }

  {
    bounded_deque<string> b_queue{5};
  }

  return 0;
}
