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
    map<string, ll> scores;
    for (ll i = 0; i < n; i++) {
        string s1, s2, res;
        cin >> s1 >> s2 >> res;
        if (res == "W") scores[s1] += 3;
        else if (res == "T") {
            scores[s1]++;
            scores[s2]++;
        }
        else scores[s2] += 3;
    }
    vector<pair<string, ll>> score_sort;
    for (const auto& pair: scores) {
        score_sort.push_back(pair);
    }
    sort(score_sort.begin(), score_sort.end(), [](auto a, auto b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });
    for (const auto& pair: score_sort) {
        cout << pair.first << " " << pair.second << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}