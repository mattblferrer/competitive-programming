#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    set<string> names;
    for (ll i = 0; i < 3; i++) {
        string name;
        cin >> name;
        names.insert(name);
    }
    if (names.count("Alice") == 0) cout << "Alice";
    if (names.count("Bob") == 0) cout << "Bob";
    if (names.count("Cindy") == 0) cout << "Cindy";
    if (names.count("Dani") == 0) cout << "Dani";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}