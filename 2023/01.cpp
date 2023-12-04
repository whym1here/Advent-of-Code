#include <bits/stdc++.h>
using namespace std;

vector<string> nums = {"zero", "one", "two",   "three", "four",
                       "five", "six", "seven", "eight", "nine"};

int is_digit(string &s, int i) {
  for (int n = 0; n <= 9; n++) {
    auto &num = nums[n];
    int ptr = 0;
    for (int j = i; j < (int)s.size(); j++) {
      if (ptr < (int)num.size() and num[ptr] == s[j]) {
        ptr++;
      } else {
        break;
      }
    }
    if (ptr == (int)num.size()) {
      return n;
    }
  }
  return -1;
}

int silver(vector<string> &a) {
  const int n = (int)a.size();
  int ans = 0;
  for (auto &r : a) {
    int f = -1, l = -1;
    const int len = (int)r.size();
    for (int i = 0; i < len; i++) {
      if ('0' <= r[i] and r[i] <= '9') {
        f = r[i] - '0';
        break;
      }
    }
    for (int i = len - 1; i >= 0; i--) {
      if ('0' <= r[i] and r[i] <= '9') {
        l = r[i] - '0';
        break;
      }
    }
    ans += f * 10 + l;
  }
  return ans;
}

int gold(vector<string> &a) {
  const int n = (int)a.size();
  int ans = 0;
  for (auto &r : a) {
    int f = -1, l = -1;
    const int len = (int)r.size();
    for (int i = 0; i < len; i++) {
      int v = is_digit(r, i);
      if ('0' <= r[i] and r[i] <= '9') {
        f = r[i] - '0';
        break;
      } else if (v != -1) {
        f = v;
        break;
      }
    }
    for (int i = len - 1; i >= 0; i--) {
      int v = is_digit(r, i);
      if ('0' <= r[i] and r[i] <= '9') {
        l = r[i] - '0';
        break;
      } else if (v != -1) {
        l = v;
        break;
      }
    }
    ans += f * 10 + l;
  }
  return ans;
}

int main() {
  int n;
  cin >> n;
  vector<string> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  cout << silver(a) << '\n';
  cout << gold(a) << '\n';
  return 0;
}
