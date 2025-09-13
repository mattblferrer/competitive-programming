#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int k;
    string s;
    cin >> k >> s;
    int n = s.size(), ans = 0, len = 0;
    if (k == 2) {
        string s1, s2;
        for (int i = 0; i < n / 2; i++) {
            s1 += "10";
            s2 += "01";
        }
        if (n % 2 == 1) {
            s1 += "1";
            s2 += "0";
        } 
        int s1_score = 0, s2_score = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != s1[i]) s1_score++;
            if (s[i] != s2[i]) s2_score++;
        }
        if (s1_score < s2_score) cout << s1_score << " " << s1;
        else cout << s2_score << " " << s2;
        return;
    }

    char prev = s[0];
    vector<int> runs;
    for (int i = 0; i < n; i++) {
        if (s[i] == prev) len++;
        else {
            runs.push_back(len);
            len = 1;
        }
        prev = s[i];
    }
    runs.push_back(len);

    int curr = -1;
    for (int i = 0; i < runs.size(); i++) {
        while (runs[i] > k) {
            curr += k;
            if (s[curr] == '1') s[curr] = '0';
            else s[curr] = '1';
            runs[i] -= k;
            ans++;
        }
        if (runs[i] == k) {
            curr += k - 1;
            if (s[curr] == '1') s[curr] = '0';
            else s[curr] = '1';
            runs[i] -= k - 1;
            ans++;
        }
        curr += runs[i];
    }

    cout << ans << " " << s;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}