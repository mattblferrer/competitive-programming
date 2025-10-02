#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

struct hole {
    ll v, t;
};

void solve() {
    ll n, sum = 0;
    cin >> n;
    vector<hole> holes(n + 1);
    holes[0] = {0, 0};
    for (int i = 1; i <= n; i++) {
        cin >> holes[i].v;
        sum += holes[i].v;
    }
    for (int i = 1; i <= n; i++) cin >> holes[i].t;
    sort(holes.begin(), holes.end(), [](hole a, hole b) {
        if (a.v * b.t == b.v * a.t) return a.t < b.t;
        return a.v * b.t > b.v * a.t; 
    });
    vector<hole> pref(n + 1);
    pref[0] = {sum, 0};
    for (int i = 1; i <= n; i++) {
        pref[i] = {pref[i - 1].v - holes[i - 1].v, holes[i].t};
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += pref[i].t * pref[i].v;
    }
    cout << ans << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}