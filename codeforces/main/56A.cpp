#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_number(string s) {
    for (char c: s) if (!isdigit(c)) return false;
    return true;
}

void solve() {
    int n;
    cin >> n;
    int ans = 0;
    set<string> drinks = {"ABSINTH", "BEER", "BRANDY", 
        "CHAMPAGNE", "GIN", "RUM", "SAKE", "TEQUILA", "VODKA", 
        "WHISKEY", "WINE"};
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (is_number(s)) {
            if (stoi(s) < 18) ans++;
        }
        else if (drinks.count(s)) ans++;
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