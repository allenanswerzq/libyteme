template <class T>
struct MinQueue {
  stack<pair<T, T>> in, out;

  void push(T x) {
    if (in.empty()) {
      in.push({x, x});
      return;
    }
    in.push({x, min(x, in.top().second)});
  }

  void fix() {
    if (out.empty()) {
      out.push({in.top().first, in.top().first});
      in.pop();
      while (!in.empty()) {
        out.push({in.top().first, min(in.top().first, out.top().second)});
        in.pop();
      }
    }
  }

  void pop() {
    assert(in.size() + out.size());
    fix();
    out.pop();
  }

  T peek() {
    fix();
    return out.top().first;
  }

  T getmin() {
    assert(in.size() + out.size());
    if (in.empty()) {
      return out.top().second;
    }
    if (out.empty()) {
      return in.top().second;
    }
    return min(in.top().second, out.top().second);
  }
};
