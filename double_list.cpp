#include <string>
#include <algorithm>
#include <iostream>

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

int main(void)
{
  {
    using std::string;
    double_linked_list<string> handle{};
    handle.add(0, "Hello");
    handle.remove(1);
    // handle.cycle(3, [](auto item){ std::cout << "Data: " << item << std::endl; });
  }

  return 0;
}
