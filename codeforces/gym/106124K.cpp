#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    // your solution here
    int n; cin >> n;
    auto convert_num = [&](string s)
        {
            int num = 0;
            for (int i = 0; i < s.size(); i++)
            {
                num *= 10;
                num += s[i] - '0';
            }
            return num;
        };

    int cur_max = 0;
    for (int i = 0; i < n; i++)
    {
        string s; cin >> s;
        if (s[0] == '/')
        {
            int hypothesized_speed = (cur_max / 10 + 1) * 10;
            cout << hypothesized_speed << '\n';
        }
        else
        {
            int cur_speed = convert_num(s);
            cout << cur_speed << "\n";
            cur_max = max(cur_max, convert_num(s));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}