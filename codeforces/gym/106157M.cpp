#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    // your solution here
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    vector<ll> dist(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        dist[i] = nums[i + 1] - nums[i];
    }

    vector<ll> prefix_max(n - 1);
    vector<ll> suffix_max(n - 1);
    prefix_max[0] = dist[0];
    suffix_max[n - 2] = dist[n - 2];
    for (int i = 1; i < n - 1; i++)
    {
        prefix_max[i] = max(prefix_max[i - 1], dist[i]);
    }

    for (int i = n - 3; i >= 0; i--)
    {
        suffix_max[i] = max(suffix_max[i + 1], dist[i]);
    }

    ll ans = LLONG_MAX;
    for (int i = 0; i < n - 2; i++)
    {
        ll cur_max = 0;
        ll new_sum = dist[i] + dist[i + 1];
        cur_max = max(new_sum, cur_max);
        if (i > 0) cur_max = max(cur_max, prefix_max[i - 1]);
        if (i + 2 < n - 1) cur_max = max(cur_max, suffix_max[i + 2]);
        ans = min(cur_max, ans);
    }

    cout << ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}