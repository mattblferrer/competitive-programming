#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    // your solution here
    ll n;
    cin >> n;

    ll pow_2 = 0;
    while (n > 0)
    {
        pow_2++;
        n /= 2;
    }

    ll num = 1;
    while (num < pow_2) num *= 2;

    if (num == 1) cout << "1 bit";
    else cout << num << " bits";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}