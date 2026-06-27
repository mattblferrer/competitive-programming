#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll n, d, l;
    cin >> n >> d >> l;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (ll i = 0; i < n; i++) {
        ll ni;
        cin >> ni;
        pq.push(ni);
    }
    while (pq.size() != 1) {
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();
        pq.push(max(a, b) + d);
    }
    cout << pq.top() + l;
}

int main() {
    solve();
    return 0;
}