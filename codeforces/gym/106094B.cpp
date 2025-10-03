#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n, t;
    cin >> n >> t;
    vector<ll> d(n);
    for (ll i = 0; i < n; i++) cin >> d[i];
    vector<ll> a(n), b(n), c(n);
    for (ll i = 0; i < n; i++) {
        c[i] = d[i] / 2;
        b[i] = (d[i] / 3 * 2) - c[i];
        a[i] = d[i] - b[i] - c[i];
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        t -= c[i];
        ans += 50;
    }
    vector<double> speeds(n, 2);
    priority_queue<tuple<ll, ll, double>, vector<tuple<ll, ll, double>>, 
        greater<tuple<ll, ll, double>>> pq;
    for (ll i = 0; i < n; i++) {
        pq.push({b[i], i, 1.5});
        pq.push({a[i], i, 1});
    }
    while (!pq.empty()) {
        ll mins = get<0>(pq.top());
        ll idx = get<1>(pq.top());
        double speed = get<2>(pq.top());
        pq.pop();
        if (t - mins < 0) break;
        t -= mins;
        ans += 25;
        speeds[idx] = speed;
    }

    cout << ans << '\n';
    for (ll i = 0; i < n; i++) {
        cout << speeds[i] << " ";
    }
    cout << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}