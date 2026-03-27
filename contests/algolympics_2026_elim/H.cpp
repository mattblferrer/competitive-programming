#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 998244353;

const ll MAXN = 5005;
vector<ll> fact(MAXN), inv_fact(MAXN);

ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

ll modinv_p(ll a, ll p) {
    return binexp(a, p - 2, p);
}

void precompute() {
    fact[0] = 1;
    for (ll i = 1; i < MAXN; i++) fact[i] = (fact[i - 1] * i) % MOD;
    inv_fact[MAXN - 1] = modinv_p(fact[MAXN - 1], MOD);
    for (ll i = MAXN - 2; i >= 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
}

void solve() {
    ll n, a;
    cin >> n >> a;
    vector<ll> secret(n); 
    for (ll i = 0; i < n; i++) cin >> secret[i];
    string s;
    cin >> s;

    ll g = 0, w = 0;
    vector<ll> g_pos, w_pos;
    for (ll i = 0; i < s.size(); i++) {
        if (s[i] == 'G') {
            g++;
            g_pos.push_back(i);
        }
        else if (s[i] == 'W') {
            w++;
            w_pos.push_back(i);
        }
    }

    bool valid = true;
    ll first_g;
    if (g == 0) first_g = n;
    else first_g = g_pos.front(); 
    for (ll i = 0; i < first_g; i++) {
        if (s[i] == 'Y') {
            cout << "0\n";
            return;
        }
    }
    ll wf = 1;
    for (ll i = 0; i < w; i++) {
        ll v = a - n - i;
        if (v <= 0) {
            wf = 0;
            break;
        }
        wf = (wf * (v % MOD)) % MOD;
    }
    if (g == 0) {
        cout << wf << "\n";
        return;
    }

    vector<ll> c(g + 1);
    for (ll k = 0; k < g; k++) {
        ll en = (k + 1 < g) ? g_pos[k + 1] : n;
        for (ll i = g_pos[k] + 1; i < en; i++) {
            if (s[i] == 'Y') c[k + 1]++;
        }
    }

    vector<ll> c_pref(g + 1);
    for (ll k = 1; k <= g; k++) c_pref[k] = c_pref[k - 1] + c[k];
    ll ng = n - g;
    vector<ll> dp(ng + 1);
    dp[0] = 1;
    for (ll k = 1; k <= g; k++) {
        vector<ll> ps(ng + 2);
        for (ll r = 0; r <= ng; r++) ps[r + 1] = (ps[r] + dp[r]) % MOD;
        fill(dp.begin(), dp.end(), 0);
        for (ll r = c_pref[k]; r <= ng; r++) {
            ll m = r - c_pref[k - 1];
            dp[r] = (((fact[m] * inv_fact[m - c[k]]) % MOD) * ps[r + 1]) % MOD;
        }
    }
    ll ans = 0;
    for (ll x: dp) {
        ans = (ans + x) % MOD;
    }
    cout << (ans * wf) % MOD << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    precompute();
    int t; cin >> t; while (t--) solve();
    return 0;
}