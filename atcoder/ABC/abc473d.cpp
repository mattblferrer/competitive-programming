#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

vector<vector<ll>> seqs;
vector<ll> curr;

void find_seq(vector<ll> &seq, ll n, ll k) {
    if (seq.size() == n - 1) {
        if (k % n == 0) {
            seq.push_back(k / n);
            seqs.push_back(seq);
            seq.pop_back();
        }
        return;
    }
    for (ll i = 0; i <= k; i += seq.size() + 1) {
        seq.push_back(i / (seq.size() + 1));
        find_seq(seq, n, k - i);
        seq.pop_back();
    }
}

void solve() {
    ll n, k;
    cin >> n >> k;
    find_seq(curr, n, k);

    for (ll i = 0; i < seqs.size(); i++) {
        for (ll j = 0; j < n; j++) {
            cout << seqs[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}