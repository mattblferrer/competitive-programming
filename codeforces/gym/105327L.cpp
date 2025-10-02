#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> bits(32);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < 32; j++) {
            if (a[i] & (1 << j)) bits[j]++;
        }
    }
    for (int i = 0; i < n; i++) {
        ll curr = 0;
        for (int j = 0; j < 32; j++) if (bits[j] > i) curr += 1 << j;
        cout << curr << " ";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}