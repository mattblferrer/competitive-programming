#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// prefix function, O(n): pi[i] = length of the longest proper prefix of s[0..i] that is also a suffix
vector<int> prefix_function(const string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// start indices of all occurrences of f in s, O(|s| + |f|)
vector<int> kmp(const string &s, const string &f) {
    if (f.empty()) return {};
    int m = f.size();
    vector<int> pi = prefix_function(f + '\0' + s), ans;  // '\0' must not appear in f
    for (int i = 2 * m; i < (int)pi.size(); i++) {
        if (pi[i] == m) ans.push_back(i - 2 * m);
    }
    return ans;
}

// Booth's algorithm for the lexicographically smallest rotation in O(n)
//   Booth(s)   stores s, O(n)
//   run()      start index of the lexicographically smallest rotation of s, O(n)
struct Booth {
    string s;
    Booth(const string &s): s(s) {}
    int run() {
        string s = this->s + this->s;
        int n = s.length(), i, j, k = 0;
        vector<int> f(n, -1);
        for (j = 1; j < n; j++) {
            i = f[j - k - 1];
            while (i != -1 && s[j] != s[k + i + 1]) {
                if (s[j] < s[k + i + 1]) k = j - i - 1;
                i = f[i];
            }
            if (i == -1 && s[j] != s[k + i + 1]) {
                if (s[j] < s[k + i + 1]) k = j;
                f[j - k] = -1;
            }
            else f[j - k] = i + 1;
        }
        return k;
    }
};
