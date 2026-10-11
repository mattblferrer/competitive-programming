#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    // your solution here
    int num; cin >> num;
    for (int i = -999; i <= 999; i++)
    {
        int j = num - i;
        if (i == 0) continue;
        if (-999 <= j && j <= 999 && j != 0)
        {
            cout << i << " " << j;
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}