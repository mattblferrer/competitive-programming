#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n, k;
    cin >> k >> n;
    int high = (n + 1) / 2, low = (n + 2) / 3;
    if (k > high || k < low) {
        cout << "*";
        return;
    }
    int diff = k - low, chars = 0;
    for (int i = 0; i < n / 3 - diff * 2; i++) {
        cout << "-X-";
        chars += 3;
    }
    int curr = chars;
    for (int i = curr; i < n - 1; i += 2) {
        cout << "X-";
        chars += 2;
    }
    int parity = (n - chars) % 3;
    if (parity == 1) cout << "X";
    if (parity == 2) cout << "-X";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}