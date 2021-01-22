#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
#define all(x) (x).begin(), (x).end()
using ll = long long;

template <class T>
class OrderedSet : public TreeSet<T> {
public:
  using TreeSet<T>::begin;
  using TreeSet<T>::end;
  using TreeSet<T>::find;
  using TreeSet<T>::erase;
  using TreeSet<T>::find_by_order;
  using TreeSet<T>::order_of_key;
  using TreeSet<T>::size;
  using iterator = typename TreeSet<T>::iterator;

  T at(int index) {
    assert(0 <= index && index < (int)size());
    return *find_by_order(index);
  }

  T operator[](int index) { return at(index); }

  int count(T x) { return (find(x) == end() ? 0 : 1); }

  int lower_bound(T x) { return order_of_key(x); }
};

// clang-format off
template <class T>
using TreeSet = tree<T,
                null_type, less<int>,
                rb_tree_tag,
                tree_order_statistics_node_update>;
// clang-format on

template <class T> class OrderedSet : public TreeSet<T> {
public:
  using TreeSet<T>::begin;
  using TreeSet<T>::end;
  using TreeSet<T>::find;
  using TreeSet<T>::erase;
  using TreeSet<T>::find_by_order;
  using TreeSet<T>::order_of_key;
  using TreeSet<T>::size;
  using iterator = typename TreeSet<T>::iterator;

  T at(int index) {
    assert(0 <= index && index < (int)size());
    return *find_by_order(index);
  }

  T operator[](int index) { return at(index); }

  int count(T x) { return (find(x) == end() ? 0 : 1); }

  int lower_bound(T x) { return order_of_key(x); }
};

// clang-format off
template <class X, class Y>
using TreeMap = tree<X, Y, less<int>,
                rb_tree_tag,
                tree_order_statistics_node_update>;
// clang-format on

template <class X, class Y> struct OrderedMap : public TreeMap<X, Y> {
  using Base = TreeMap<X, Y>;
  using Base::begin;
  using Base::end;
  using Base::find;
  using Base::find_by_order;
  using Base::order_of_key;
  using Base::size;

  using PXY = std::pair<X, Y>;

  // Returns the `ith` element in a set zero index based.
  PXY at(int index) {
    assert(0 <= index && index < (int)size());
    return *find_by_order(index);
  }

  // Returns the index of a value.
  int index(X key) {
    if (find(key) == end()) {
      return -1;
    }
    return order_of_key(key);
  }

  int count(X key) { return (find(key) == end() ? 0 : 1); }
};

// clang-format off
template <class T>
using TreeMultiSet = tree<pair<T, int>,
                     null_type, less<pair<T, int>>,
                     rb_tree_tag,
                     tree_order_statistics_node_update>;
// clang-format on

template <class T> struct OrderedMultiSet : public TreeMultiSet<T> {
public:
  using TreeMultiSet<T>::find_by_order;
  using TreeMultiSet<T>::insert;
  using TreeMultiSet<T>::lower_bound;
  using TreeMultiSet<T>::order_of_key;
  using TreeMultiSet<T>::size;
  using TreeMultiSet<T>::end;

  using iterator = typename TreeMultiSet<T>::iterator;

  void insert(T x) { insert(make_pair(x, id_++)); }

  T at(int index) {
    assert(0 <= index && index < (int)size());
    return find_by_order(index)->first;
  }

  T operator[](int index) { return at(index); }

  void erase(iterator it) { TreeMultiSet<T>::erase(it); }

  void erase(int index) { erase(find(at(index))); }

  iterator find(T x) {
    size_t p = lower_bound(x);
    if (p < size()) {
      return find_by_order(p);
    } else {
      return end();
    }
  }

  int lower_bound(T x) { return order_of_key({x, 0}); }

private:
  size_t id_ = 0;
};
