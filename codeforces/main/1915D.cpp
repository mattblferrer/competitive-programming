#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    int n;
    string s;
    cin >> n >> s;
    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        if (cnt == 2 && (s[i + 1] == 'a' || s[i + 1] == 'e')) {
            cout << '.';
            cnt = 0;
        }
        else if (cnt == 3) {
            cout << '.';
            cnt = 0;
        }
        cout << s[i];
        cnt++;
    }
    cout << s[n - 1] << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}