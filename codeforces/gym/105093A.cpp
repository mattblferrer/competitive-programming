#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    string a, b, c, d, e, f, g;
    getline(cin, a);
    getline(cin, b);
    getline(cin, c);
    getline(cin, d);
    getline(cin, e);
    getline(cin, f);
    getline(cin, g);

    map<int, char> lights;
    map<char, bool> on;
    char on1 = a.back(), on2 = b.back(), off1 = d.back();
    int r = stoi(f.substr(6, 1)) - 1;
    int s = stoi(g.substr(6, 1)) - 1;
    string s_state = g.substr(11, 4);
    on[on1] = true;
    on[on2] = true;
    char cold;
    for (char c = 'A'; c != 'D'; c++) {
        if (!on[c]) cold = c;
    }
    if (s_state == "HOT") {
        lights[s] = off1;
        if (on1 == off1) lights[r] = on2;
        else lights[r] = on1;
        lights[3 - s - r] = cold;
    }
    else {
        if (on1 == off1) {
            lights[3 - s - r] = on1;
            lights[r] = on2;
            lights[s] = cold;
        }
        else {
            lights[r] = on1;
            lights[3 - s - r] = on2;
            lights[s] = cold;
        }
    }
    cout << lights[0] << " " << lights[1] << " " << lights[2] << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}