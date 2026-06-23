#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct booth {
    int *f;
    string s;
    booth(string &s) {
        this->s = s;
    }
    int run() {
        s.append(s);
        int n = s.length(), i, j, k = 0;
        f = new int[n];
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

void solve() {
    string s;
    cin >> s;
    booth b(s);
    cout << b.s.substr(b.run(), s.size());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}