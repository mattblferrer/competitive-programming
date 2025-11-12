#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n1, n2;
    cin >> n1;
    vector<string> s1(n1);
    for (ll i = 0; i < n1; i++) cin >> s1[i];
    cin >> n2;
    vector<string> s2(n2);
    for (ll i = 0; i < n2; i++) cin >> s2[i];
    multiset<string> m1(s1.begin(), s1.end());
    multiset<string> m2(s2.begin(), s2.end());
    multiset<string> both;
    for (string s: m1) {
        if (m2.count(s)) both.insert(s);
    }
    cout << both.size() << "\n";
    for (string s: both) {
        cout << s << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}