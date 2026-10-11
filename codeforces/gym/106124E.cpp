#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<string> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    int total = 0;
    vector<string> ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            if (p[i][j] == '#') ans[i] += '#';
            else ans[i] += 'B';
            if (p[i][j] == 'C') total++;
        }
    }
    vector<string> ans2 = ans, ans3 = ans, ans4 = ans, ans5 = ans;
    if (total % 2 == 1) {
        cout << "impossible\n";
        return;
    }

    // case 1
    int a = 0;
    for (int j = 0; j < n - 1; j++) {
        for (int i = n - 1; i >= 0; i--) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') a++;
            ans[i][j] = 'A';
            if (a == total / 2) {
                for (int k = 0; k < n; k++) cout << ans[k] << "\n";
                return;
            }
        }
    }
    for (int j = n - 1; j < 2 * n - 1; j++) {
        if (p[n - 1][j] == 'C') a++;
        ans[n - 1][j] = 'A';
        if ((j != 2 * n - 3) && (a == total / 2)) {
            for (int k = 0; k < n; k++) cout << ans[k] << "\n";
            return;
        }
    }
    for (int j = 2 * n - 2; j >= n - 1; j--) {
        for (int i = n - 2; i >= 0; i--) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') a++;
            ans[i][j] = 'A';
            if (a == total / 2) {
                for (int k = 0; k < n; k++) cout << ans[k] << "\n";
                return;
            }
        }
    }

    // case 2
    int b = 0;
    for (int j = 2 * n - 2; j >= n + 1; j--) {
        for (int i = n - 1; i >= 0; i--) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') b++;
            ans2[i][j] = 'A';
            if (b == total / 2) {
                for (int k = 0; k < n; k++) cout << ans2[k] << "\n";
                return;
            }
        }
    }
    for (int j = n; j >= 0; j--) {
        if (p[n - 1][j] == 'C') b++;
        ans2[n - 1][j] = 'A';
        if ((j != 1) && (b == total / 2)) {
            for (int k = 0; k < n; k++) cout << ans2[k] << "\n";
            return;
        }
    }
    for (int j = 0; j < n - 1; j++) {
        for (int i = n - 2; i >= 0; i--) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') b++;
            ans2[i][j] = 'A';
            if (b == total / 2) {
                for (int k = 0; k < n; k++) cout << ans2[k] << "\n";
                return;
            }
        }
    }

    // case 3
    int c = 0;
    for (int i = 0; i < n - 1; i++) {
        if (p[i][n - 1] == 'C') c++;
        ans3[i][n - 1] = 'A';
        if (c == total / 2) {
            for (int k = 0; k < n; k++) cout << ans3[k] << "\n";
            return;
        }
        for (int j = n - 2; j >= 0; j--) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') c++;
            ans3[i][j] = 'A';
            if (c == total / 2) {
                for (int k = 0; k < n; k++) cout << ans3[k] << "\n";
                return;
            }
        }
        for (int j = n; j < 2 * n - 1; j++) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') c++;
            ans3[i][j] = 'A';
            if (c == total / 2) {
                for (int k = 0; k < n; k++) cout << ans3[k] << "\n";
                return;
            }
        }
    }

    // case 4
    int d = 0;
    for (int j = 0; j < 2 * n - 1; j++) {
        for (int i = n - 1; i >= 0; i--) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') d++;
            ans4[i][j] = 'A';
            if ((i == 1) && (j == n - 1)) continue;
            if (d == total / 2) {
                for (int k = 0; k < n; k++) cout << ans4[k] << "\n";
                return;
            }
        }
    }

    // case 5
    int e = 0;
    for (int j = 2 * n - 2; j >= 0; j--) {
        for (int i = n - 1; i >= 0; i--) {
            if (p[i][j] == '#') break;
            if (p[i][j] == 'C') e++;
            ans5[i][j] = 'A';
            if ((i == 1) && (j == n - 1)) continue;
            if (e == total / 2) {
                for (int k = 0; k < n; k++) cout << ans5[k] << "\n";
                return;
            }
        }
    }

    cout << "impossible\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}