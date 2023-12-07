#include <bits/stdc++.h>
using namespace std;

vector<string> read_lines(string file_name = "input.txt") {
  vector<string> res;
  string line;
  ifstream file(file_name);
  if (file.is_open()) {
    while (getline(file, line)) {
      res.push_back(line);
    }
    file.close();
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

  map<char, int> pw;
  int ptr = 0;
  for (char c : "23456789TJQKA") {
    pw[c] = ptr++;
  }

  auto type = [&](string s) -> int {
    map<char, int64_t> cnt;
    for (char c : s)
      cnt[c]++;
    int len = (int)cnt.size();
    vector<int64_t> freq;
    for (auto &[k, v] : cnt)
      freq.push_back(v);
    sort(freq.begin(), freq.end());
    if (len == 1 and *max_element(freq.begin(), freq.end()) == 5) {
      return 6;
    }
    if (len == 2 and *max_element(freq.begin(), freq.end()) == 4) {
      return 5;
    }
    if (len == 2 and *max_element(freq.begin(), freq.end()) == 3) {
      return 4;
    }
    if (len == 3 and *max_element(freq.begin(), freq.end()) == 3) {
      return 3;
    }
    if (len == 3 and freq[2] == freq[1] and freq[2] == 2) {
      return 2;
    }
    if (len == 4 and freq[3] == 2) {
      return 1;
    }
    if (len == 5 and freq[4] == 1) {
      return 0;
    }
    assert(false);
    return -1;
  };

  auto gr = [&](string &s, string &t) -> bool {
    const int n = (int)s.size();
    assert((int)t.size() == n);
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
      l[i] = pw[s[i]];
      r[i] = pw[t[i]];
    }
    return l < r;
  };

  vector<pair<string, int64_t>> opt;
  for (auto &line : lines) {
    vector<string> parts = split(line, ' ');
    opt.emplace_back(parts[0], stoll(parts[1]));
  }

  sort(opt.begin(), opt.end(), [&](auto &left, auto &right) -> bool {
    string &l = left.first;
    string &r = right.first;
    int t_l = type(l), t_r = type(r);
    if (t_l == t_r)
      return gr(l, r);
    return t_l < t_r;
  });

  ptr = 1;
  for (auto &[k, v] : opt) {
    ans += v * 1LL * ptr;
    ptr++;
  }
  return ans;
}

string replace(string s, char current, char next) {
  string res = "";
  for (char c : s) {
    if (c == current)
      res += next;
    else
      res += c;
  }
  return res;
}

int64_t gold(vector<string> lines) {
  int64_t ans = 0;

  map<char, int> pw;
  int ptr = 0;

  string all = "J23456789TQKA";
  for (char c : all) {
    pw[c] = ptr++;
  }

  auto type = [&](string s) -> int {
    map<char, int64_t> cnt;
    for (char c : s)
      cnt[c]++;
    int len = (int)cnt.size();
    vector<int64_t> freq;
    for (auto &[k, v] : cnt)
      freq.push_back(v);
    sort(freq.begin(), freq.end());
    if (len == 1 and *max_element(freq.begin(), freq.end()) == 5) {
      return 6;
    }
    if (len == 2 and *max_element(freq.begin(), freq.end()) == 4) {
      return 5;
    }
    if (len == 2 and *max_element(freq.begin(), freq.end()) == 3) {
      return 4;
    }
    if (len == 3 and *max_element(freq.begin(), freq.end()) == 3) {
      return 3;
    }
    if (len == 3 and freq[2] == freq[1] and freq[2] == 2) {
      return 2;
    }
    if (len == 4 and freq[3] == 2) {
      return 1;
    }
    if (len == 5 and freq[4] == 1) {
      return 0;
    }
    assert(false);
    return -1;
  };

  auto gr = [&](string &s, string &t) -> bool {
    const int n = (int)s.size();
    assert((int)t.size() == n);
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
      l[i] = pw[s[i]];
      r[i] = pw[t[i]];
    }
    return l < r;
  };

  vector<tuple<string, string, int64_t>> opt;
  for (auto &line : lines) {
    vector<string> parts = split(line, ' ');
    opt.emplace_back(parts[0], parts[0], stoll(parts[1]));
  }

  int id = 0;
  for (auto &[cur, next, value] : opt) {
    string s = "";
    int js = count(cur.begin(), cur.end(), 'J');
    if (js > 0) {
      map<char, int> cnt;
      for (char c : cur)
        cnt[c]++;
      vector<tuple<int, int, char>> p;
      for (auto &[k, v] : cnt) {
        if (k != 'J')
          p.emplace_back(v, pw[k], k);
      }
      sort(p.begin(), p.end());
      if (js == 5) {
        s = replace(cur, 'J', 'A');
      } else {
        s = replace(cur, 'J', get<2>(p.back()));
      }
    } else {
      s = cur;
    }
    next = s;
    id++;
  }

  sort(opt.begin(), opt.end(), [&](auto &left, auto &right) -> bool {
    int t_l = type(get<1>(left)), t_r = type(get<1>(right));
    if (t_l == t_r)
      return gr(get<0>(left), get<0>(right));
    return t_l < t_r;
  });

  ptr = 1;
  for (auto &[k, _, v] : opt) {
    ans += v * 1LL * ptr;
    ptr++;
  }
  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';
  return 0;
}
