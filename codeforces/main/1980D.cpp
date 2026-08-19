#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<ll> gcd_sequence(vector<ll> a) {
    vector<ll> ans;
    int n = a.size();
    for (ll i = 0; i < n - 1; i++) {
        ans.push_back(gcd(a[i], a[i + 1]));
    }
    return ans;
}

bool is_nondec(vector<ll> &vec) {
    int s = vec.size();
    for (int i = 0; i < s - 1; i++) {
        if (vec[i] > vec[i + 1]) return false;
    }
    return true;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> b = gcd_sequence(a);
    ll found = -1;
    for (ll i = 0; i < n - 1; i++) {
        if (b[i] > b[i + 1]) {
            found = i + 1;
            break;
        }
    }
    if (found == -1) { cout << (is_nondec(b) ? "YES\n" : "NO\n"); return; }

    vector<ll> a1, a2, a3, b1, b2, b3;
    for (ll i = 0; i < n; i++) {
        if (i != found - 1) a1.push_back(a[i]);
        if (i != found) a2.push_back(a[i]);
        if (i != found + 1) a3.push_back(a[i]);
    }
    b1 = gcd_sequence(a1);
    b2 = gcd_sequence(a2);
    b3 = gcd_sequence(a3);
    if ((is_nondec(b1)) || (is_nondec(b2)) || (is_nondec(b3))) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}