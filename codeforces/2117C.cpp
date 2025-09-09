#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

ll problem2117C() {
    ll n;
    std::cin >> n;
    std::vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::set<ll> prev, curr;
    ll ans = 1, curr_cnt = 0;
    prev.insert(a[1]);
    for (ll i = 2; i <= n; i++) {
        if (curr.count(a[i]) == 1) continue;
        curr.insert(a[i]);
        if (curr.count(a[i]) == prev.count(a[i])) curr_cnt++;
        if (curr_cnt == prev.size()) {
            prev = curr;
            curr.clear();
            curr_cnt = 0;
            ans++;
        }
        
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2117C() << "\n";
    }
    return 0;
}