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
    string s;
    cin >> s;
    vector<ll> a_pos, b_pos;
    ll a = 0, b = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == 'a') {
            a_pos.push_back(i - a);
            a++;
        }
        else {
            b_pos.push_back(i - b);
            b++;
        }
    }
    ll med_a, med_b;
    if (a_pos.size()) med_a = a_pos[a_pos.size() / 2];
    else med_a = 0;
    if (b_pos.size()) med_b = b_pos[b_pos.size() / 2];
    else med_b = 0;
    ll min_a = 0, min_b = 0;
    a = 0, b = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == 'a') {
            min_a += abs(med_a - a_pos[a]);
            a++;
        }
        else {
            min_b += abs(med_b - b_pos[b]);
            b++;
        }
    }
    cout << min(min_a, min_b) << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}