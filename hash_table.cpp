#include "chapter_two.cpp"
#include "single_list.cpp"

template <typename T>
class chained_hash_table {
private:
  array<list<T>> table;
  size_t total_number_of_items;
  // We maintain the invariant that total_number_of_items <= t.length
  // so that lists don't get too long
  void resize(void)
  {

  }

  auto hash(T x) {}

  auto find(T x)
  {
    size_t j = hash(x);
    for (size_t i = 0; i < table[j].size(); i++)
      if (x == table[j].get(i))
	return table[j].get(i);
    return nullptr;
  }

public:
  bool add(T x)
  {
    if (find(x) != nullptr) return false;
    if (total_number_of_items + 1 > table.length()) resize();
    table[hash(x)].add(x);
  }

  auto remove(T x)
  {
    size_t j = hash(x);
    for (int i = 0; i < table[j].size(); i++) {
      T *y = table[j].get(i);
      if (x == y) {
	table[j].remove(i);
	total_number_of_items--;
	return y;
      }
    }
    return nullptr;
  }
};

int main(void)
{
  return 0;
}
