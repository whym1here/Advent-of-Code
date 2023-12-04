#include <bits/stdc++.h>
using namespace std;

vector<string> read_lines() {
  vector<string> res;
  string str;
  while (true) {
    getline(cin, str);
    if (str.size() == 0)
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
      if (cur.size() > 0)
        res.push_back(cur);
      cur = "";
    } else {
      cur += ch;
    }
  }
  if (cur.size() > 0) {
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
  for (int i = (int)s.size() - 1; i >= 0; i++) {
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
        // cout << s << ":";
      }
    }
    // cout << '\n';

    for (auto &e : split(have_c)) {
      string s = rltrim(e);
      if (!s.empty() and '0' <= s[0] and s[0] <= '9') {
        have[s]++;
        // cout << s << ":";
      }
    }
    // cout << '\n';

    int64_t cnt = 0;
    for (auto &[k, v] : have) {
      cnt += min(v, win[k]);
    }
    // cout << "cnt = " << (1 << cnt) << '\n';
    if (cnt >= 1)
      ans += (1LL << (cnt - 1));
  }
  return ans;
}

int gold(vector<string> lines) {
  int64_t ans = 0;
  const int n = (int)lines.size();
  vector<int64_t> cards(n), times(n, 1);
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
        // cout << s << ":";
      }
    }
    // cout << '\n';

    for (auto &e : split(have_c)) {
      string s = rltrim(e);
      if (!s.empty() and '0' <= s[0] and s[0] <= '9') {
        have[s]++;
        // cout << s << ":";
      }
    }
    // cout << '\n';

    int64_t cnt = 0;
    for (auto &[k, v] : have) {
      cnt += min(v, win[k]);
    }

    int t = cnt, ptr = j + 1;
    if (ptr != n) {
      while (t--) {
        if (ptr == n)
          ptr = j + 1;
        times[ptr] += times[j];
        ptr++;
      }
    }
    // cout << "cnt = " << (1 << cnt) << '\n';
  }
  return accumulate(times.begin(), times.end(), (int64_t)0);
}

int main() {
  vector<string> lines = read_lines();
  // cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';

  return 0;
}
