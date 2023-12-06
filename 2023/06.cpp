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

  auto line_0 = split(rltrim(split(lines[0], ':')[1]));
  vector<int64_t> times;
  for (auto &e : line_0)
    times.push_back(stoll(rltrim(e)));

  auto line_1 = split(rltrim(split(lines[1], ':')[1]));
  vector<int64_t> dist;
  for (auto &e : line_1)
    dist.push_back(stoll(rltrim(e)));

  assert(times.size() == dist.size());
  const int n = (int)times.size();
  vector<int64_t> res(n, 0);

  for (int64_t i = 0; i < n; i++) {
    for (int64_t j = 0; j <= times[i]; j++) {
      int64_t left = times[i] - j;
      int64_t trev = j * left;
      if (trev > dist[i])
        res[i]++;
    }
  }

  ans = 1;
  for (auto &e : res)
    ans *= e;

  return ans;
}

int64_t gold(vector<string> lines) {
  int64_t ans = 0;

  auto line_0 = split(rltrim(split(lines[0], ':')[1]));
  string s_time = "";
  for (auto &e : line_0)
    s_time += rltrim(e);

  auto line_1 = split(rltrim(split(lines[1], ':')[1]));
  string s_dist = "";
  for (auto &e : line_1)
    s_dist += rltrim(e);

  int64_t time = stoll(s_time), dist = stoll(s_dist);

  for (int64_t i = 0; i <= time; i++) {
    int64_t left = time - i;
    int64_t trev = left * i;
    if (trev > dist)
      ans++;
  }

  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';
  return 0;
}
