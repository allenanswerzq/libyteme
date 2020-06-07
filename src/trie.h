struct Trie {
  int p = 1;
  vector<int> leaf;
  vector<vector<int>> node;

  Trie(int n) {
    leaf.resize(n);
    node.resize(n, vector<int>(26));
  }

  int get_pos(char ch) {
    return ch - 'a';
  }

  void add(const string& s) {
    int u = 0;
    for (auto& ch : s) {
      if (!node[u][get_pos(ch)]) {
        node[u][get_pos(ch)] = p++;
      }
      u = node[u][get_pos(ch)];
    }
    leaf[u]++;
  }

  bool search(const string& s) {
    int u = 0;
    for (auto& ch : s) {
      if (!node[u][get_pos(ch)]) {
        return false;
      }
      u = node[u][get_pos(ch)];
    }
    return leaf[u] > 0;
  }
};
