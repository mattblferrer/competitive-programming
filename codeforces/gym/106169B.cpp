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
    bool askbefore = false;
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;
        vector<string> extra(4);
        if (cmd == "Ask") {
            askbefore = true;
            for (ll j = 0; j < 3; j++) cin >> extra[j];
        }
        else if (cmd == "Set") {
            string name;
            cin >> name;
            if (askbefore) ans += name.size(); 
            askbefore = false;
            for (ll j = 0; j < 2; j++) cin >> extra[j];
            if (extra[1] == "answer") continue;
            for (ll j = 2; j < 4; j++) cin >> extra[j];
        }
        else if (cmd == "Say") {
            askbefore = false;
            cin >> extra[0];
        }
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}