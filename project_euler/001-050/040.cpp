#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> idxs = {1, 10, 100, 1000, 10000, 100000, 1000000};
    ll ans = 1;
    vector<ll> transitions = {0};
    ll ctr = 1;
    ll curr = 0;
    while (curr < idxs.back()) {
        curr += 9 * ctr * pow(10, ctr - 1);
        ctr++;
        transitions.push_back(curr);
    }
    for (int i = 0; i < idxs.size(); i++) {
        int curr_trans = 0;
        while (idxs[i] > transitions[curr_trans]) curr_trans++;
        int adj = idxs[i] - transitions[curr_trans - 1] - 1;
        int int_part = adj / curr_trans + pow(10, curr_trans - 1);
        int digit_index = adj % curr_trans;
        int digit = to_string(int_part)[digit_index] - '0';
        ans *= digit;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}