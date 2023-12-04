#include <bits/stdc++.h>
using namespace std;

vector<string> read_lines() {
  vector<string> res;
  string str;
  while (true) {
    getline(cin, str);
    if (str.empty())
      break;
    res.push_back(str);
  }
  return res;
}

vector<string> split(string s, char c = ' ') {
  vector<string> res;
  string cur = "";
  for (char ch : s) {
    if (ch == c) {
      if (!cur.empty())
        res.push_back(cur);
      cur = "";
    } else {
      cur += ch;
    }
  }
  if (!cur.empty()) {
    res.push_back(cur);
  }
  return res;
}

string rltrim(string s, char c = ' ') {
  int lo = -1, hi = -1;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] != c) {
      lo = i;
      break;
    }
  }
  for (int i = (int)s.size() - 1; i >= 0; i--) {
    if (s[i] != c) {
      hi = i;
      break;
    }
  }
  if (lo != -1 and hi != -1) {
    string res = "";
    for (int i = lo; i <= hi; i++)
      res += s[i];
    return res;
  }
  return "";
}

int64_t silver(vector<string> lines) {
  int64_t ans = 0;
  for (auto &line : lines) {
    auto div_p = split(line, ':');
    auto tot = split(div_p[1], '|');
    auto win_c = rltrim(tot[0]), have_c = rltrim(tot[1]);

    map<string, int64_t> win, have;
    for (auto &e : split(win_c)) {
      string s = rltrim(e);
      if (!s.empty() and '0' <= s[0] and s[0] <= '9') {
        win[s]++;
      }
    }

    for (auto &e : split(have_c)) {
      string s = rltrim(e);
      if (!s.empty() and '0' <= s[0] and s[0] <= '9') {
        have[s]++;
      }
    }

    int64_t cnt = 0;
    for (auto &[k, v] : have) {
      cnt += min(v, win[k]);
    }
    if (cnt >= 1)
      ans += (1LL << (cnt - 1));
  }
  return ans;
}

template <typename T> class BIT {
public:
  vector<T> bit;
  int n;

  BIT() { n = 0; }

  BIT(int _n) {
    n = _n;
    bit.assign(n, 0);
  }

  // increase the value of element at idx idxex i.e a[idx]
  void inc(int idx, T val) {
    assert(0 <= idx and idx < n);
    for (int i = idx + 1; i <= n; i += (i & -i))
      bit[i - 1] += val;
  }

  // sum of all the elements in [0..idx]
  T query(int idx) {
    assert(0 <= idx and idx < n);
    T res = 0;
    for (int i = idx + 1; i > 0; i -= (i & -i))
      res += bit[i - 1];
    return res;
  }

  // get the value of element at idx index i.e a[idx]
  T at(int idx) {
    assert(0 <= idx and idx < n);
    return query(idx) - (idx - 1 >= 0 ? query(idx - 1) : 0);
  }

  // sum of all the element [l..r]
  T at(int l, int r) {
    assert(0 <= l and l <= r and r < n);
    return query(r) - (l - 1 >= 0 ? query(l - 1) : 0);
  }
};

template <typename T> class FT {
public:
  BIT<T> f1, f2;
  int n;

  FT() { n = 0; }

  FT(int _n) {
    n = _n;
    f1 = f2 = BIT<T>(_n + 1);
  }

  // increase the value of element at idx idxex i.e a[idx]
  void inc(int idx, T val) {
    assert(0 <= idx and idx < n);
    inc(idx, idx, val);
  }

  // increase all the elements in [l..r] by val
  void inc(int l, int r, T val) {
    assert(0 <= l and l <= r and r < n);
    f1.inc(l, val);
    f1.inc(r + 1, -val);
    f2.inc(l, val * (l - 1));
    f2.inc(r + 1, -val * r);
  }

  // sum of all the elements in [0..idx]
  T query(int idx) {
    assert(0 <= idx and idx < n);
    return f1.query(idx) * idx - f2.query(idx);
  }

  // get the value of element at idx index i.e a[idx]
  T at(int idx) {
    assert(0 <= idx and idx < n);
    return query(idx) - (idx - 1 >= 0 ? query(idx - 1) : 0);
  }

  // sum of all the element [l..r]
  T at(int l, int r) {
    assert(0 <= l and l <= r and r < n);
    return query(r) - (l - 1 >= 0 ? query(l - 1) : 0);
  }
};

int64_t gold(vector<string> lines) {
  int64_t ans = 0;
  const int n = (int)lines.size();
  FT<int64_t> fw(n);
  fw.inc(0, n - 1, 1);
  for (int j = 0; j < n; j++) {
    auto &line = lines[j];
    auto div_p = split(line, ':');
    auto tot = split(div_p[1], '|');
    auto win_c = rltrim(tot[0]), have_c = rltrim(tot[1]);

    map<string, int64_t> win, have;
    for (auto &e : split(win_c)) {
      string s = rltrim(e);
      if (!s.empty() and '0' <= s[0] and s[0] <= '9') {
        win[s]++;
      }
    }

    for (auto &e : split(have_c)) {
      string s = rltrim(e);
      if (!s.empty() and '0' <= s[0] and s[0] <= '9') {
        have[s]++;
      }
    }

    int64_t cnt = 0;
    for (auto &[k, v] : have) {
      cnt += min(v, win[k]);
    }

    if (j != n - 1) {
      int len = n - j - 1;
      int times = cnt / len;
      int rem = cnt % len;
      fw.inc(j + 1, n - 1, times * fw.at(j));
      if (rem >= 1) {
        fw.inc(j + 1, j + rem, fw.at(j));
      }
    }
  }
  return fw.at(0, n - 1);
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';

  return 0;
}
