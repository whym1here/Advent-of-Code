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

  int64_t to = 2;

  vector<string> a = lines;
  const int n = (int)a.size(), m = (int)a[0].size();
  vector<int64_t> row(n, 0), col(m, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '#') {
        row[i]++;
        col[j]++;
      }
    }
  }
  vector<int> t_rows(n, 0), t_cols(m, 0);
  for (int i = 0; i < n; i++) {
    t_rows[i] = (row[i] == 0) + (i - 1 >= 0 ? t_rows[i - 1] : 0);
  }
  for (int j = 0; j < m; j++) {
    t_cols[j] = (col[j] == 0) + (j - 1 >= 0 ? t_cols[j - 1] : 0);
  }

  vector<int64_t> x, y;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '#') {
        int64_t cx = i, cy = j;
        if (i - 1 >= 0)
          cx += (to - 1) * t_rows[i - 1];
        if (j - 1 >= 0)
          cy += (to - 1) * t_cols[j - 1];

        x.push_back(cx);
        y.push_back(cy);
      }
    }
  }

  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  int64_t tot_x = accumulate(x.begin(), x.end(), (int64_t)0);
  int64_t tot_y = accumulate(y.begin(), y.end(), (int64_t)0);

  const int len = (int)x.size();
  for (int i = 0; i < len; i++) {
    int64_t cx = x[i], cy = y[i];

    tot_x -= cx;
    ans += tot_x - (len - i - 1) * cx;

    tot_y -= cy;
    ans += tot_y - (len - i - 1) * cy;
  }

  return ans;
}

int64_t gold(vector<string> lines) {
  int64_t ans = 0;

  int64_t to = 1000000;

  vector<string> a = lines;
  const int n = (int)a.size(), m = (int)a[0].size();
  vector<int64_t> row(n, 0), col(m, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '#') {
        row[i]++;
        col[j]++;
      }
    }
  }
  vector<int> t_rows(n, 0), t_cols(m, 0);
  for (int i = 0; i < n; i++) {
    t_rows[i] = (row[i] == 0) + (i - 1 >= 0 ? t_rows[i - 1] : 0);
  }
  for (int j = 0; j < m; j++) {
    t_cols[j] = (col[j] == 0) + (j - 1 >= 0 ? t_cols[j - 1] : 0);
  }

  vector<int64_t> x, y;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '#') {
        int64_t cx = i, cy = j;
        if (i - 1 >= 0)
          cx += (to - 1) * t_rows[i - 1];
        if (j - 1 >= 0)
          cy += (to - 1) * t_cols[j - 1];

        x.push_back(cx);
        y.push_back(cy);
      }
    }
  }

  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  int64_t tot_x = accumulate(x.begin(), x.end(), (int64_t)0);
  int64_t tot_y = accumulate(y.begin(), y.end(), (int64_t)0);

  const int len = (int)x.size();
  for (int i = 0; i < len; i++) {
    int64_t cx = x[i], cy = y[i];

    tot_x -= cx;
    ans += tot_x - (len - i - 1) * cx;

    tot_y -= cy;
    ans += tot_y - (len - i - 1) * cy;
  }

  return ans;
}

int main() {
  vector<string> lines = read_lines();
  cout << silver(lines) << '\n';
  cout << gold(lines) << '\n';
  return 0;
}
