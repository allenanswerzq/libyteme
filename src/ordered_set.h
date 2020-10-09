#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define all(x) (x).begin(), (x).end()
typedef long long ll;

using TreeSet = __gnu_pbds::tree<T, null_type, less<int>, rb_tree_tag,
                                 tree_order_statistics_node_update>;

template <class T>
struct OrderedSet : public TreeSet {
  using TreeSet::begin;
  using TreeSet::end;
  using TreeSet::find;
  using TreeSet::find_by_order;
  using TreeSet::order_of_key;
  using TreeSet::size;

  // Returns the `ith` element in a set zero index based.
  T at(int index) {
    assert(0 <= index && index < (int)size());
    return *find_by_order(index);
  }

  T operator[](int index) { return at(index); }

  // Returns the index of a value.
  int index(T val) {
    if (find(val) == end()) {
      return -1;
    }
    return order_of_key(val);
  }

  int count(T x) { return (find(x) == end() ? 0 : 1); }
};

using TreeMap = __gnu_pbds::tree<X, Y, less<int>, rb_tree_tag,
                                 tree_order_statistics_node_update>;

template <class X, class Y>
struct OrderedMap : public TreeMap {
  using TreeMap::begin;
  using TreeMap::end;
  using TreeMap::find;
  using TreeMap::find_by_order;
  using TreeMap::order_of_key;
  using TreeMap::size;

  typedef std::pair<X, Y> PXY;

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

#define TreeMultiSet                                             \
  tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, \
       tree_order_statistics_node_update>

template <class T>
struct OrderedMultiSet : public TreeMultiSet {
  using TreeMultiSet::find_by_order;
  using TreeMultiSet::insert;
  using TreeMultiSet::lower_bound;
  using TreeMultiSet::order_of_key;
  using TreeMultiSet::size;

  using iterator = typename TreeMultiSet::iterator;
  using const_iterator = typename TreeMultiSet::const_iterator;

  int id = 0;

  void insert(T x) { insert({x, id++}); }

  T at(int index) {
    assert(0 <= index && index < (int)size());
    return find_by_order(index)->first;
  }

  // Get the `index`th element.
  const_iterator att(int index) const {
    assert(0 <= index && index < (int)size());
    return find_by_order(index);
  }

  iterator att(int index) {
    assert(0 <= index && index < (int)size());
    return find_by_order(index);
  }

  // Get the index of a specific key `x`.
  int index(int x) { return order_of_key({x, 0}); }

  void erase(iterator it) { TreeMultiSet::erase(it); }

  void erase(int index) { erase(att(index)); }

  // O(logc + count(x))
  void erase_all(T x) {
    int lo = lower_bound(x);
    int hi = upper_bound(x);
    int cnt = hi - lo;
    for (int i = 0; i < cnt; i++) {
      erase(lo);
    }
  }

  int lower_bound(T x) { return order_of_key({x, 0}); }

  int upper_bound(T x) { return order_of_key({x + 1, 0}); }

  int count(T x) {
    int d = upper_bound(x) - lower_bound(x);
    // assert(d >= 1);
    return d;
  }
};
