#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_palindrome_time(int hh, int mm) {
    return ((hh / 10 == mm % 10) && (hh % 10 == mm / 10));
}

void solve() {
    string time;
    ll x;
    cin >> time >> x;
    string hstr = time.substr(0, 2);
    string mstr = time.substr(3, 2);
    ll hh = stoi(hstr), mm = stoi(mstr);
    set<pll> seen;
    ll ans = 0;
    while (seen.count({hh, mm}) == 0) {
        if (is_palindrome_time(hh, mm)) ans++;
        seen.insert({hh, mm});
        mm += x;
        hh += (mm / 60);
        mm %= 60;
        hh %= 24;
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}