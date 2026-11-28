#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    string s;
    cin >> n >> s;

    bool rev = false;
    for (ll i = 0; i < n; i++) {
        if (s[i] == 'o') rev = !rev;
    }
    deque<ll> a = {1};
    for (ll i = 0; i < n - 1; i++) {
        if (s[i] == 'o') rev = !rev;
        if (rev) a.push_front(i + 2);
        else a.push_back(i + 2);
    }
    for (ll i = 0; i < n; i++) cout << a[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}