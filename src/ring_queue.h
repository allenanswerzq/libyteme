#include <bits/stdc++.h>
using namespace std;

template <class T, int N>
struct RingQueue {
  int head = 0;
  int tail = 0;
  vector<T> v;

  RingQueue() {
    // Waste one storage.
    v.resize(N + 1);
  }

  bool empty() { return head == tail; }

  bool full() { return (tail + 1) % (N + 1) == head; }

  int size() { return (tail - head + (N + 1)) % (N + 1); }

  void push(const T& val) {
    assert(!full());
    tail = (tail + 1) % (N + 1);
    v[tail] = val;
  }

  void pop() {
    assert(!empty());
    head = (head + 1) % (N + 1);
  }

  T front() {
    assert(!empty());
    return v[(head + 1) % (N + 1)];
  }
};
