#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8092, 16184, 32368, 64736, 129472, 258944, 517888, 1035776, 2071552, 4143104, 8286208, 16572416, 33144832, 66289664, 132579328, 265158656, 530317312, 1060634624, 2121269248, 4242538496, 8485076992, 16970153984, 33940307968};
    cout << a[n];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}