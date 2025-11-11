#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct car {
    string name;
    ll fe, ts;
};

void solve() {
    ll n;
    cin >> n;
    vector<car> cars(n);
    for (ll i = 0; i < n; i++) {
        string name;
        ll fe, ts;
        cin >> name >> fe >> ts;
        cars[i] = {name, fe, ts};
    }
    sort(cars.begin(), cars.end(), [](car a, car b){
        ll sc_a = a.fe * a.ts;
        ll sc_b = b.fe * b.ts;
        if (sc_a == sc_b) return a.name < b.name;
        return sc_a < sc_b;
    });
    for (ll i = 0; i < n; i++) {
        cout << cars[i].name << " " << cars[i].fe << " " << cars[i].ts << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}