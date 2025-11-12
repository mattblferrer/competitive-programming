#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string run;
    cin >> run;
    if (run == "first") {
        ll n;
        cin >> n;
        vector<ll> a(n);
        for (ll i = 0; i < n; i++) cin >> a[i];
        string enc = "";
        for (ll i = 0; i < n; i++) {
            string curr = "aaaaaaaaaa";
            for (ll j = 0; j <= 9; j++) {
                curr[j] = (a[i] % 10) + 'a';
                a[i] /= 10;
            }
            enc += curr;
        }
        cout << enc;
    }
    else {
        string enc;
        cin >> enc;
        ll n = enc.size() / 10;
        vector<ll> a(n);
        for (ll i = 0; i < n; i++) {
            ll p = 1;
            for (ll j = 0; j <= 9; j++) {
                a[i] += (enc[i*10 + j] - 'a') * p;
                p *= 10;
            }
        }
        cout << n << "\n";
        for (ll i = 0; i < n; i++) cout << a[i] << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}