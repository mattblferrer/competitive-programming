#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

vector<int> bills = {1, 2, 5, 10, 20, 50, 100, 200, 500};

bool is_splittable(vector<int> cnt) {
    int x = 0, y = 0;
    for (int i = 8; i >= 0; i--) {
        while (cnt[i] > 0) {
            if (x > y) y += bills[i];
            else x += bills[i];
            cnt[i]--;
        }
    }
    return x == y;
}

bool solve(int n) {
    for (int i = 0; i < (1 << 9); i++) {
        int used = 0, total = 0, curr = n;
        vector<int> cnt(9);
        for (int j = 8; j >= 0; j--) {
            if (i & (1 << j)) {
                cnt[j] = curr / bills[j];
                curr -= cnt[j] * bills[j];
                used += cnt[j];
                total += cnt[j] * bills[j];
            }
        }
        if (total != n) continue;
        if (!is_splittable(cnt)) {
            cout << used << "\n";
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < cnt[j]; k++) cout << bills[j] << " ";
            }
            return false;
        }
    }
    cout << "splittable\n";
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int n;
    cin >> n;
    solve(n);
    return 0;
}