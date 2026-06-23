#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

struct KMP {
    vector<int> par;
    int n;
    string s, f;
    KMP(string &s, string &f) {
        this->n = s.size(); this->s = s; this->f = f;
        if (f.size() > s.size()) return;

        par.resize(max(n, 2), 0);
        par[0] = -1, par[1] = 0;
        int i = 2, j = 0;
        while (i <= f.size()) {
            if (f[i - 1] == f[j]) par[i++] = ++j;
            else if (j > 0) j = par[j];
            else par[i++] = 0;
        }
    }
    vector<int> run() {
        if (f.size() > s.size()) return {};

        int i = 0, j = 0; vector<int> ans;
        while (i + j < s.size()) {
            if (s[i + j] == f[j]) {
                if (++j == f.size()) {
                    ans.push_back(i);
                    i += j - par[j];
                    if (j > 0) j = par[j];
                }
            }
            else {
                i += j - par[j];
                if (j > 0) j = par[j];
            }
        }
        return ans;
    }
};

struct booth {
    int *f;
    string s;
    booth(string &s) {
        this->s = s;
    }
    int run() {
        s.append(s);
        int n = s.length(), i, j, k = 0;
        memset(f, -1, sizeof(int) * n);
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
