#include <iostream>
#include <vector>

using namespace std;

class Handler {
  int n;
  bool inverted;
  vector<vector<int>> layers;

  int get (int i, int j) {
    if (inverted) {
      return (3 - layers[i][j]) % 3;
    } else {
      return layers[i][j];
    }
  }

  void add (int i, int j) {
    if (inverted) {
      layers[i][j] += 2;
    } else {
      layers[i][j] += 1;
    }
    layers[i][j] %= 3;
  }
  
public:
  Handler (int _n) : n(_n), inverted(false), layers(_n, vector<int> (0)) {
    int cur = 1;
    for (int i = 0; i < n; i++) {
      layers[i] = vector<int> (3 * cur);
      for (int j = 0; j < 3 * cur; j++) {
        layers[i][j] = j / cur;
      }
      cur *= 3;
    }
  }

  void rumba () {
    int last = 0, step = 1;
    for (int i = 0; i < n; i++) {
      for (int j = last; j < (int) layers[i].size(); j += step) {
        add(i, j);
        if (get(i, j) == 0) {
          last = j;
        }
      }
      step *= 3;
    }
  }

  void samba () {
    inverted = !inverted;
  }

  int get (int pos) {
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
      ans *= 3;
      ans += get(i, pos % (int) layers[i].size());
    }
    return ans;
  }
};

int main () {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;

  string s;
  cin >> s;

  Handler hd (n);
  for (char c : s) {
    switch (c) {
    case 'R':
      hd.rumba();
      break;
    case 'S':
      hd.samba();
      break;
    }
  }

  int cnt = 1;
  for (int i = 0; i < n; i++) {
    cnt *= 3;
  }

  for (int i = 0; i < cnt; i++) {
    cout << hd.get(i) << " ";
  }
  cout << '\n';
}
