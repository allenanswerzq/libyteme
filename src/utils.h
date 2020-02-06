
template <class T>
vector<int> discrete(vector<T>& v, vector<T>* t, int* m, bool one = true) {
  int off = one ? 1 : 0;
  sort(t->begin() + off, t->end());
  t->erase(unique(t->begin() + off, t->end()), t->end());
  int vs = v.size();
  vector<int> idx(vs);
  for (int i = off; i < vs; i++) {
    idx[i] = lower_bound(t->begin(), t->end(), v[i]) - t->begin();
  }
  *m = t->size() - off;
  return idx;
}
