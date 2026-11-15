#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve()
{
    string s; cin >> s;
    ll m; cin >> m;
    ll total = 0;
    ll cur_a = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'A') cur_a++;
        else total += cur_a;
    }
    ll ans = max(0ll, total - m);
    cout << ans << '\n';
}
int main(void)
{
    solve();
    return 0;
}