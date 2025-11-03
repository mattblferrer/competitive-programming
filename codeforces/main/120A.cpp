#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string dir, rail;
    getline(input, dir);
    getline(input, rail);
    if (dir == "front") {
        if (rail == "1") output << "L";
        else output << "R";
    }
    else {
        if (rail == "1") output << "R";
        else output << "L";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}