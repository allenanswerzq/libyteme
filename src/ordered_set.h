#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define RB rb_tree_tag, tree_order_statistics_node_update
#define OD_MAP tree<X, Y, less<int>, RB>
#define OD_SET tree<T, null_type, less<int>, RB>
#define OD_MSET tree<pair<T, int>, null_type, less<pair<T, int>>, RB>
#define x first
#define y second
#ifndef LOCAL
#define trace(...)
#endif
typedef long long ll;

template <class X, class Y>
struct OrderedMap : public OD_MAP {
  using OD_MAP::find_by_order;
  using OD_MAP::order_of_key;
  using OD_MAP::size;
  using OD_MAP::find;
  using OD_MAP::end;
  using OD_MAP::begin;

  typedef std::pair<X, Y> PXY;

  // Returns the `ith` element in a set zero index based.
  PXY at(int index) {
    assert(0 <= index && index < (int) size());
    return *find_by_order(index);
  }

  // Returns the index of a value.
  int index(X key) {
    if (find(key) == end()) {
      return -1;
    }
    return order_of_key(key);
  }

  int count(X key) {
    return (find(key) == end() ? 0 : 1);
  }
};

template <class T>
struct OrderedSet : public OD_SET {
  using OD_SET::find_by_order;
  using OD_SET::order_of_key;
  using OD_SET::size;
  using OD_SET::find;
  using OD_SET::end;
  using OD_SET::begin;

  // Returns the `ith` element in a set zero index based.
  T at(int index) {
    assert(0 <= index && index < (int) size());
    return *find_by_order(index);
  }

  T operator[](int index) {
    return at(index);
  }

  // Returns the index of a value.
  int index(T val) {
    if (find(val) == end()) {
      return -1;
    }
    return order_of_key(val);
  }

  int count(T x) {
    return (find(x) == end() ? 0 : 1);
  }
};

template<class T>
struct OrderedMultiSet : public OD_MSET {
  using OD_MSET::find_by_order;
  using OD_MSET::insert;
  using OD_MSET::lower_bound;
  using OD_MSET::order_of_key;
  using OD_MSET::size;

  typedef typename OD_MSET::iterator iterator;
  typedef typename OD_MSET::const_iterator const_iterator;

  int id = 0;

  void insert(T x) {
    insert({x, id++});
  }

  T at(int index) {
    assert(0 <= index && index < (int) size());
    return find_by_order(index)->first;
  }

  // Get the `index`th element.
  const_iterator att(int index) const {
    assert(0 <= index && index < (int) size());
    return find_by_order(index);
  }

  iterator att(int index) {
    assert(0 <= index && index < (int) size());
    return find_by_order(index);
  }

  // Get the index of a specific key `x`.
  int index(int x) {
    return order_of_key({x, 0});
  }

  void erase(iterator it) {
    OD_MSET::erase(it);
  }

  void erase(int index) {
    erase(att(index));
  }

  // O(logc + count(x))
  void erase_all(T x) {
    int lo = lower_bound(x);
    int hi = upper_bound(x);
    int cnt = hi - lo;
    for (int i = 0; i < cnt; i++) {
      erase(lo);
    }
  }

  int lower_bound(T x) {
    return order_of_key({x, 0});
  }

  int upper_bound(T x) {
    return order_of_key({x + 1, 0});
  }

  int count(T x) {
    int d = upper_bound(x) - lower_bound(x);
    // assert(d >= 1);
    return d;
  }
};
