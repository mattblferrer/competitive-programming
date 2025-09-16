#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int q, c, x;
    cin >> q;
    deque<int> d;
    for (int i = 0; i < q; i++) {
        cin >> c;
        if (c == 0) {
            cin >> x;
            d.push_front(x);
        }
        if (c == 1) {
            cin >> x;
            d.push_back(x);
        }
        if (c == 2) d.pop_front();
        if (c == 3) d.pop_back();
        if (c == 4) {
            cin >> x;
            cout << d[x] << "\n";
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}