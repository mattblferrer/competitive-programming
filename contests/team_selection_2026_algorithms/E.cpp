#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int k, n;
    cin >> k >> n;
    vector<string> strs(n);
    for (int i = 0; i < n; i++) {
        cin >> strs[i];
    }

    vector<string> ans;
    for (int i = 0; i < pow(10, k); i++) {
        string code = "";
        int temp = i;
        while (temp != 0) {
            code += '0' + (temp % 10);
            temp /= 10;
        }
        while (code.size() < k) code += '0';
        reverse(code.begin(), code.end());

        int found = 0;
        for (int j = 0; j < n; j++) {
            int curr = 0;
            for (int si = 0; si < strs[j].size(); si++) {
                if (strs[j][si] == code[curr]) curr++;
                if (curr == k) {
                    found++;
                    break;
                }
            }
            if (found == j) break;
        }
        if (found == n) ans.push_back(code);
    }
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << "\n";
}

int main() {
    solve();
    return 0;
}