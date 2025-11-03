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
        for (ll i = 0; i < n; i++) enc += a[i] + 'a' - 1;
        cout << enc;
    }
    else {
        string enc;
        cin >> enc;
        ll n = enc.size();
        vector<ll> a(n);
        for (ll i = 0; i < n; i++) a[i] = enc[i] - 'a' + 1;
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