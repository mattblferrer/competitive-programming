#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ifstream file("p022_names.txt");
    string all_names;
    vector<string> names;
    getline(file, all_names);
    string curr_name = "";
    for (ll i = 0; i < all_names.size(); i++) {
        if (all_names[i] == ',') {
            names.push_back(curr_name);
            curr_name = "";
        }
        else if (all_names[i] == '"') continue;
        else curr_name.push_back(all_names[i]);
    }
    names.push_back(curr_name);  // push back last name in file

    ll ans = 0;
    sort(names.begin(), names.end());
    for (ll i = 0; i < names.size(); i++) {
        ll curr = 0;
        for (ll j = 0; j < names[i].size(); j++) {
            curr += (names[i][j] - 'A' + 1);
        }
        curr *= (i + 1);
        ans += curr;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}