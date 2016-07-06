// A binary tree is a connected, undirected, finite graph with no
// cycles and no vertex of degree greater than three
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>

#include "chapter_two.cpp"

template<typename T>
int compare(T x, T y)
{ if (x < y) return -1; else if (x > y) return 1; else return 0;}

template <typename T>
struct node {
  node *left = nullptr, *right = nullptr, *parent = nullptr;
  T data = nullptr;
  node(T d) : data(d) {}
  node(void) {}

};

template <typename T>
struct binary_tree {
  node<T> *root = nullptr;
  size_t total_size = 0;

  void splice(node<T> *u)
  {
    node<T> *s, *p;
    if (u->left != nullptr)
      s = u->left;
    else
      s = u->right;
    if (u == root) {
      root = s;
      p = nullptr;
    } else {
      p = u->parent;
      if (p->left == u)
	p->left = s;
      else
	p->right = s;
    }
    if (s != nullptr)
      s->parent = p;
    total_size--;
  }

  binary_tree(T data) : root(new node<T>{data}), total_size(1) {}

  void traverse_bfs(std::function<void(node<T>*)> cb)
  {
    array_deque<node<T>*> q;

    if (root != nullptr) q.add(q.size(), root);

    while (q.size() > 0) {
      node<T> *u = q.remove(q.size() - 1);
      cb(u);
      if (u->left != nullptr) q.add(q.size(), u->left);
      if (u->right != nullptr) q.add(q.size(), u->right);
    }

  }

  bool add_child(node<T> *p, node<T> *u)
  {
    if (p == nullptr)
      root = u;
    else {
      switch (compare(u->data, p->data)) {
      case -1:
	p->left = u;
	break;
      case 1:
	p->right = u;
	break;
      default:
	return false;
      }
      u->parent = p;
    }
    total_size++;
    return true;
  }

  bool add(T x)
  {
    node<T> *p = find_last(x), *u = new node<T>;
    u->data = x;
    return add_child(p, u);
  }

  node<T> *find_last(T x)
  {
    node<T> *w = root, *prev = nullptr;

    while (w != nullptr) {
      prev = w;
      switch (compare(x, w->data)) {
      case -1:
	w = w->left;
	break;
      case 1:
	w = w->right;
	break;
      default:
	return w;
      }
    }
    return prev;
  }

};

int main(void)
{

  using namespace std::string_literals;

  binary_tree<std::string> tree{"A"};

  tree.add("F");

  return 0;
}
