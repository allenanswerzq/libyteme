#include <bits/stdc++.h>
using namespace std;

template <int N, class T>
struct BinaryHeapGeneric {
  int hs = 0;  // heap size
  vector<T> heap;

  explicit BinaryHeapGeneric() { heap.resize(N); }

  explicit BinaryHeapGeneric(const vector<T>& v) {
    heap.resize(N);
    for (int i = 0; i < (int)v.size(); i++) {
      insert(v[i]);
    }
  }

  void insert(T v) {
    assert(hs + 1 < N);
    heap[++hs] = v;
    swim(hs);
  }

  void swim(int cur) {
    int root = cur / 2;
    while (root && heap[cur] < heap[root]) {
      swap(heap[root], heap[cur]);
      cur = root;
      root = cur / 2;
    }
  }

  void swim_rec(int cur) {
    if (!cur) {
      return;
    }
    int root = cur / 2;
    if (heap[root] <= heap[cur]) {
      return;
    }
    swap(heap[root], heap[cur]);
    swim_rec(root);
  }

  T top() {
    T val = heap[1];
    assert(hs >= 1);
    heap[1] = heap[hs--];
    sink(1);
    return val;
  }

  void sink(int root) {
    int lhs = root * 2;
    while (lhs <= hs) {
      int rhs = lhs + 1;
      int mi = lhs;
      if (rhs <= hs && heap[rhs] < heap[lhs]) {
        mi = rhs;
      }
      if (heap[root] <= heap[mi]) {
        break;
      }
      swap(heap[root], heap[mi]);
      root = mi;
      lhs = mi * 2;
    }
  }

  void sink_rec(int root) {
    int lhs = root * 2;
    if (root > hs || lhs > hs) {
      return;
    }
    int rhs = root * 2 + 1;
    int mi = lhs;
    if (rhs <= hs && heap[rhs] < heap[lhs]) {
      mi = rhs;
    }
    if (heap[root] <= heap[mi]) {
      return;
    }
    swap(heap[root], heap[mi]);
    sink_rec(mi);
  }

  // TODO(zq7): Erase a value out.
  void erase(T v) {}
};

template <int N>
using BinaryHeap = BinaryHeapGeneric<N, int>;
