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
  string path = lines[0];
  map<string, int> id;
  map<int, string> rid;
  vector<tuple<int, int, int>>
      edges; // directed graph (from, to, dir) [-1 left, +1 right]

  for (int i = 2; i < (int)lines.size(); i++) {
    string line = lines[i];
    auto parts = split(line, '=');
    string from = rltrim(parts[0]);
    auto rest = split(rltrim(rltrim(rltrim(parts[1]), ')'), '('), ',');
    string left = rltrim(rest[0]), right = rltrim(rest[1]);

    if (id.find(from) == id.end()) {
      int cid = (int)id.size();
      id[from] = cid;
      rid[cid] = from;
    }

    if (id.find(left) == id.end()) {
      int cid = (int)id.size();
      id[left] = cid;
      rid[cid] = left;
    }

    if (id.find(right) == id.end()) {
      int cid = (int)id.size();
      id[right] = cid;
      rid[cid] = right;
    }

    edges.emplace_back(id[from], id[left], 0);  // 0 -> left
    edges.emplace_back(id[from], id[right], 1); // 1 -> right
  }

  int src = id["AAA"], dest = id["ZZZ"];
  const int N = (int)id.size();
  vector<vector<int>> adj(N, vector<int>(2));
  for (auto &[u, v, dir] : edges) {
    adj[u][dir] = v;
  }

  int u = src;
  int ptr = 0;
  while (u != dest) {
    char c = path[ptr];
    int dir = (c == 'L' ? 0 : 1);
    u = adj[u][dir];
    ptr = (ptr + 1) % path.size();
    ans++;
  }

  return ans;
}

int64_t gold(vector<string> lines) {
  int64_t ans = 0;
  string path = lines[0];
  map<string, int> id;
  map<int, string> rid;
  vector<tuple<int, int, int>>
      edges; // directed graph (from, to, dir) [-1 left, +1 right]

  for (int i = 2; i < (int)lines.size(); i++) {
    string line = lines[i];
    auto parts = split(line, '=');
    string from = rltrim(parts[0]);
    auto rest = split(rltrim(rltrim(rltrim(parts[1]), ')'), '('), ',');
    string left = rltrim(rest[0]), right = rltrim(rest[1]);

    if (id.find(from) == id.end()) {
      int cid = (int)id.size();
      id[from] = cid;
      rid[cid] = from;
    }

    if (id.find(left) == id.end()) {
      int cid = (int)id.size();
      id[left] = cid;
      rid[cid] = left;
    }

    if (id.find(right) == id.end()) {
      int cid = (int)id.size();
      id[right] = cid;
      rid[cid] = right;
    }

    edges.emplace_back(id[from], id[left], 0);  // 0 -> left
    edges.emplace_back(id[from], id[right], 1); // 1 -> right
  }

  const int N = (int)id.size();
  vector<vector<int>> adj(N, vector<int>(2));
  for (auto &[u, v, dir] : edges) {
    adj[u][dir] = v;
  }

  auto find = [&](int src) -> int64_t {
    int u = src;
    int ptr = 0;
    int64_t res = 0;
    while (rid[u].back() != 'Z') {
      char c = path[ptr];
      int dir = (c == 'L' ? 0 : 1);
      u = adj[u][dir];
      ptr = (ptr + 1) % path.size();
      res++;
    }
    return res;
  };

  vector<int64_t> values;
  for (auto &[k, v] : id) {
    if (k.back() == 'A') {
      values.push_back(find(id[k]));
    }
  }

  ans = values.front();
  for (auto &e : values)
    ans = (ans * e) / __gcd(ans, e);

  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';
  return 0;
}
