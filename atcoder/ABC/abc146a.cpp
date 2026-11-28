#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<string> days = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    string day;
    cin >> day;
    for (int i = 0; i < 7; i++) {
        if (day == days[i]) cout << 7 - i;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}