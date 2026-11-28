#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    deque<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    bool flip = false;
    while (!a.empty()) {
        if (flip) {
            if (a.back() == 1) a.pop_back();
            else if (a.front() == 1) { a.pop_front(); flip = false; }
            else {
                cout << "No\n";
                return;
            }
        }
        else {
            if (a.back() == 0) a.pop_back();
            else if (a.front() == 0) { a.pop_front(); flip = true; }
            else {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}