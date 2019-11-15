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
struct ordered_map : public OD_MAP {
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
struct ordered_set : public OD_SET {
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
struct ordered_multiset : public OD_MSET {
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
    assert(d >= 1);
    return d;
  }
};

void test_ordered_map() {
  ordered_map<int, vector<int>> omp;
  omp[9] = {2};
  omp[8] = {1};
  omp[3] = {0};
  // trace(omp.at(0));
  assert(omp.at(0) == make_pair(3, vector<int>{0}));
  assert(omp.at(1) == make_pair(8, vector<int>{1}));
  assert(omp.at(2) == make_pair(9, vector<int>{2}));
  assert(omp.index(3) == 0);
  assert(omp.index(8) == 1);
}

void test_ordered_multiset() {
  ordered_multiset<int> omst;
  // Insert
  omst.insert(1);
  omst.insert(2);
  omst.insert(3);
  omst.insert(1);
  omst.insert(5);
  omst.insert(1);
  trace(omst);
  // Access
  assert(omst.at(0) == 1);
  assert(omst.at(1) == 1);
  assert(omst.at(2) == 1);
  assert(omst.at(3) == 2);
  assert(omst.at(4) == 3);
  assert(omst.at(5) == 5);
  // Index
  // assert(omst.index(1) == 2);
  // assert(omst.index(2) == 3);
  // assert(omst.index(3) == 4);
  // assert(omst.index(5) == 5);
  trace(omst.order_of_key({2, 0}));
  trace(omst.order_of_key({4, 0}));
  // Erase a single key
  omst.erase(omst.att(1));
  trace(omst);
  assert(omst.count(1) == 2);
  // Erase all values for a key
  omst.erase_all(1);
  omst.insert(3);
  omst.insert(3);
  omst.insert(3);
  trace(omst);
  omst.erase_all(3);
  trace(omst);
  // lower_bound
  assert(omst.lower_bound(2) == 0);
  assert(omst.lower_bound(1) == 0);
  assert(omst.lower_bound(10) == 2);
  // upper_bound
  assert(omst.upper_bound(2) == 1);
  assert(omst.upper_bound(1) == 0);
  assert(omst.upper_bound(10) == 2);
}

void test_ordered_set() {
  ordered_set<int> ost;
  // Insert
  ost.insert(1);
  ost.insert(2);
  ost.insert(3);
  ost.insert(4);
  ost.insert(5);
  // Erase
  ost.erase(5);
  trace(ost.size(), ost);
  // Access
  for (int i = 0; i < 4; i++) {
    assert(ost.at(i) == i + 1);
  }
  // Index
  int k = 0;
  for (auto v : ost) {
    assert(ost.index(v) == k++);
  }
  assert(ost.index(18) == -1);
  // Count
  assert(ost.count(2) == 1);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  // test_ordered_set();
  test_ordered_multiset();
  // test_ordered_map();
  return 0;
}
