#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct laptop {
    ll speed, ram, hdd, cost, idx;
};

void solve() {
    ll n;
    cin >> n;
    vector<laptop> a(n);
    for (ll i = 0; i < n; i++) {
        ll speed, ram, hdd, cost;
        cin >> speed >> ram >> hdd >> cost;
        a[i] = {speed, ram, hdd, cost, i};
    }
    vector<laptop> f;
    for (ll i = 0; i < n; i++) {
        bool valid = true;
        laptop x = a[i];
        for (ll j = 0; j < n; j++) {
            laptop y = a[j];
            if (x.speed < y.speed && x.ram < y.ram && x.hdd < y.hdd) valid = false;
        }
        if (valid) f.push_back(x);
    }
    sort(f.begin(), f.end(), [](laptop a, laptop b){
        return a.cost < b.cost;
    });
    cout << f[0].idx + 1 << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}