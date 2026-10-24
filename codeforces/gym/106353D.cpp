#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
int main() {
    ll n; cin >> n;
    ll ans = 0;
    ll max_k;
    for (ll k = max(0ll, n / 2 - 10000); k <= n / 2; k++)
    {
        ll cur_gcd = gcd(k, n);
        ll skips = n / cur_gcd;
        ll cur_ans = skips * k;
        if (cur_ans > ans)
        {
            ans = cur_ans;
            max_k = k;
        }
    }
    cout << max_k;

}