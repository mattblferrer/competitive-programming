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
    vector<ll> pos, neg, zero;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        if (ai > 0) pos.push_back(ai);
        else if (ai < 0) neg.push_back(ai);
        else zero.push_back(ai);
    }
    vector<ll> s1, s2, s3;
    if (neg.size() % 2 == 0) {
        s3.push_back(neg[0]);
        s1.push_back(neg[1]);
        for (ll i = 2; i < neg.size(); i++) s2.push_back(neg[i]);
    }
    else {
        s1.push_back(neg[0]);
        if (neg.size() > 1) {
            for (ll i = 1; i < 3; i++) s2.push_back(neg[i]);
            for (ll i = 3; i < neg.size(); i++) s1.push_back(neg[i]);
        }
        else {
            for (ll i = 1; i < neg.size(); i++) s2.push_back(neg[i]);
        }
        
    }
    for (ll i = 0; i < pos.size(); i++) s2.push_back(pos[i]);
    for (ll i = 0; i < zero.size(); i++) s3.push_back(zero[i]);
    cout << s1.size() << " ";
    for (ll i = 0; i < s1.size(); i++) cout << s1[i] << " ";
    cout << "\n";
    cout << s2.size() << " ";
    for (ll i = 0; i < s2.size(); i++) cout << s2[i] << " ";
    cout << "\n";
    cout << s3.size() << " ";
    for (ll i = 0; i < s3.size(); i++) cout << s3[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}