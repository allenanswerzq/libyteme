#include <bits/stdc++.h>
using namespace std;

// A string prase function, split string using `delim`.
vector<string> split(string& s, char delim = ",") {
  vector<string> ret;
  int start = 0;
  for (int i = 0; i < s.size() + 1; i++) {
    if (i == s.size() || s[i] == delim) {
      ret.push_back(s.substr(start, i - start));
    }
    start = i + 1;
  }
  return ret;
}

void test() {
  string s = "1,28,300.1,San Francisco";
  trace(split(s));
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  test();
  return 0;
}
