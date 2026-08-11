#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 10'000'000'000'000;
const ll MOD = 1000000007;

ll max_subarray_sum(vector<ll> &vec) {
    ll curr = 0, ans = 0;
    for (ll i = 0; i < vec.size(); i++) {
        curr = max(vec[i], curr + vec[i]);
        ans = max(ans, curr);
    }
    return ans;
}

void solve() {
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    // if no blanks, kadane's and return a
    ll blanks = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') blanks++;
    }
    if (blanks == 0) {
        if (max_subarray_sum(a) == k) {
            cout << "Yes\n";
            for (ll i = 0; i < n; i++) cout << a[i] << " ";
            cout << "\n";
        }
        else cout << "No\n";
        return;
    }

    // get lowest subarray sum possible
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') a[i] = -INF;
    }
    if (max_subarray_sum(a) > k) {
        cout << "No\n";
        return;
    }
    ll low_i = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') {
            low_i = i;
            break;
        }
    }

    // binary search on answer
    ll left = -INF, right = INF;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        a[low_i] = mid;
        if (max_subarray_sum(a) <= k) left = mid;
        else right = mid;
    }
    a[low_i] = left;
    cout << "Yes\n";
    for (ll i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}