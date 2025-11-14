#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<string> planets = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
    string p1, p2;
    cin >> p1 >> p2;
    ll k1, k2;
    for (ll i = 0; i < 8; i++) {
        if (planets[i] == p1) k1 = i;
        if (planets[i] == p2) k2 = i;
    }
    if (k1 == k2) cout << "THE SAME\n";
    else if (k1 < k2) cout << "CLOSER\n";
    else cout << "FARTHER AWAY\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}