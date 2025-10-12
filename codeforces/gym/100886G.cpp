#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll dp[20][2][2][2];
ll digit[20][2][2][2];
string a, b;
ll n;

ll find(ll pos, ll lb, ll ub, ll lead) {
    if (pos == n) return lead ? 1 : -1;
    if (dp[pos][lb][ub][lead] != -1) return dp[pos][lb][ub][lead];
    
    ll low = lb ? a[pos] : 0;
    ll high = ub ? b[pos] : 9;
    ll bestd = -1;
    ll prod = -1;

    for (ll d = low; d <= high; d++) {
        ll nlb = lb && (d == low);
        ll nub = ub && (d == high);
        ll nlead = lead || (d != 0);
        ll sub = find(pos + 1, nlb, nub, nlead);
        if (sub == -1) continue;
        ll curr = sub;
        if (nlead) {
            curr = (lead ? d : (d == 0 ? 1 : d)) * sub;
        }
        if (curr > prod) {
            prod = curr;
            bestd = d;
        }
    }
    digit[pos][lb][ub][lead] = bestd;
    return dp[pos][lb][ub][lead] = prod;
}

void solve() {
    ll ai, bi;
    cin >> ai >> bi;
    a = to_string(ai), b = to_string(bi);
    while (a.size() < b.size()) a = '0' + a;
    n = b.size();
    for (int i = 0; i < n; i++) {
        a[i] -= '0';
        b[i] -= '0';
    }
    memset(dp, -1, sizeof(dp));
    memset(digit, -1, sizeof(digit));
    find(0, 1, 1, 0);

    string ans = "";
    ll pos = 0, lb = 1, ub = 1, lead = 0;
    while (pos < n) {
        ll d = digit[pos][lb][ub][lead];
        ll low = lb ? a[pos] : 0;
        ll high = ub ? b[pos] : 9;
        ll nlb = lb && (d == low);
        ll nub = ub && (d == high);
        ll nlead = lead || (d != 0);
        ans.push_back(d + '0');
        lb = nlb; 
        ub = nub; 
        lead = nlead; 
        pos++;
    }
    lead = 1;
    for (ll i = 0; i < n; i++) {
        if (ans[i] != '0') lead = 0;
        if (!lead) cout << ans[i];  
    }
    
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}