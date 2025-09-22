#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    ll n, a_i;
    cin >> n;
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        cin >> a_i;
        cnt[a_i]++;
    }
    vector<pll> freq;
    for (pll pair: cnt) {
        freq.push_back(pair);
    }
    sort(freq.begin(), freq.end(), [](pll a, pll b) {
        return a.second > b.second;
    });

    ll alice = 0, bob = 0, turn = 1;
    for (pll pair: freq) {
        if (pair.first % 2 == 0) {
            alice += (pair.first / 2) * pair.second;
            bob += (pair.first / 2) * pair.second;
        }
        else {
            alice += (pair.first / 2 + turn) * pair.second;
            bob += (pair.first / 2 + (1 - turn)) * pair.second;
            turn = 1 - turn;
        }
    }
    cout << alice << " " << bob << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}