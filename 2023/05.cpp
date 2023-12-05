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
  vector<int64_t> seeds;
  auto line_0 = split(split(lines[0], ':')[1]);
  for (auto &e : line_0) {
    seeds.push_back(stoll(rltrim(e)));
  }

  vector<pair<string, string>> type;
  vector<vector<tuple<int64_t, int64_t, int64_t>>> mappings;

  int ptr = 1;
  while (ptr < (int)lines.size()) {
    if (lines[ptr].empty()) {
      ptr++;
      auto first_part = split(lines[ptr])[0];
      auto parsed = split(first_part, '-');
      type.emplace_back(parsed[0], parsed[2]);
      mappings.emplace_back();
    } else {
      auto parsed = split(lines[ptr]);
      vector<int64_t> nums;
      for (auto &e : parsed) {
        nums.push_back(stoll(rltrim(e)));
      }
      mappings.back().emplace_back(nums[0], nums[1], nums[2]);
    }
    ptr++;
  }

  int len = (int)type.size();
  vector<set<int64_t>> dp(2);
  for (auto &e : seeds) {
    dp[1].insert(e);
  }

  for (int i = 0; i < len; i++) {
    int p = (i & 1);
    auto &cur = dp[p];
    auto &prv = dp[1 - p];

    for (auto &[a, b, c] : mappings[i]) {
      int64_t l = b, r = b + c - 1;
      // a + x = b => x = b - a
      int64_t shift = a - b;
      auto lo = prv.lower_bound(l);
      while (lo != prv.end() and *lo <= r) {
        cur.insert(*lo + shift);
        prv.erase(lo);
        lo = prv.lower_bound(l);
      }
    }
    for (auto &e : prv) {
      cur.insert(e);
    }
    ans = *cur.begin();
    prv.clear();
  }
  return ans;
}

int64_t gold(vector<string> lines) {
  int64_t ans = 0;
  vector<int64_t> seeds;
  auto line_0 = split(split(lines[0], ':')[1]);
  for (auto &e : line_0) {
    seeds.push_back(stoll(rltrim(e)));
  }

  vector<pair<string, string>> type;
  vector<vector<tuple<int64_t, int64_t, int64_t>>> mappings;

  int ptr = 1;
  while (ptr < (int)lines.size()) {
    if (lines[ptr].empty()) {
      ptr++;
      auto first_part = split(lines[ptr])[0];
      auto parsed = split(first_part, '-');
      type.emplace_back(parsed[0], parsed[2]);
      mappings.emplace_back();
    } else {
      auto parsed = split(lines[ptr]);
      vector<int64_t> nums;
      for (auto &e : parsed) {
        nums.push_back(stoll(rltrim(e)));
      }
      mappings.back().emplace_back(nums[0], nums[1], nums[2]);
    }
    ptr++;
  }

  int len = (int)type.size();
  vector<set<pair<int64_t, int64_t>>> dp(2);
  for (int i = 0; i < (int)seeds.size(); i += 2) {
    int64_t l = seeds[i], r = seeds[i] + seeds[i + 1] - 1;
    dp[1].emplace(l, r);
  }

  for (int i = 0; i < len; i++) {
    int p = (i & 1);
    auto &cur = dp[p];
    auto &prv = dp[1 - p];

    for (auto &[a, b, c] : mappings[i]) {
      int64_t l = b, r = b + c - 1;
      // a + x = b => x = b - a
      int64_t shift = a - b;
      set<pair<int64_t, int64_t>> to_remove, to_add;
      for (auto &[L, R] : prv) {
        if (l <= L and R <= r) {
          to_remove.emplace(L, R);
          cur.emplace(L + shift, R + shift);
        } else if (l <= L and L <= r) {
          to_remove.emplace(L, R);
          cur.emplace(L + shift, r + shift);
          to_add.emplace(r + 1, R);
        } else if (l <= R and R <= r) {
          to_remove.emplace(L, R);
          cur.emplace(l + shift, R + shift);
          to_add.emplace(L, l - 1);
        }
      }

      for (auto &e : to_remove)
        prv.erase(e);
      for (auto &e : to_add)
        prv.insert(e);
    }
    for (auto &e : prv) {
      cur.insert(e);
    }
    ans = cur.begin()->first;
    prv.clear();
  }
  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';

  return 0;
}
