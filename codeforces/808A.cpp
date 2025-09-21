#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    string s;
    cin >> s;
    int n = stoi(s);
    int fd = s[0] - '0';
    int ans = (fd + 1) * pow(10, s.size() - 1) - n;
    cout << ans;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}