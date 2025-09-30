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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> left(n), right(n);
    ll curr = INF;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) curr = 0;
        left[i] = curr;
        curr++;
    }
    curr = INF;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == 0) curr = 0;
        right[i] = curr;
        curr++;
    }
    for (int i = 0; i < n; i++) {
        cout << min(left[i], right[i]) << " ";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}