#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

string tstr = R"(75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
)";

void solve() {
    vector<vector<int>> triangle;
    vector<int> row;
    string curr = "";
    for (int i = 0; i < tstr.size(); i++) {
        if (tstr[i] == ' ') {
            row.push_back(stoi(curr));
            curr = "";
        }
        else if (tstr[i] == '\n') {
            row.push_back(stoi(curr));
            triangle.push_back(row);
            row.clear();
            curr = "";
        }
        else curr += tstr[i];
    }
    int n = triangle.size();
    vector<vector<int>> sum(n, vector<int>(n));
    sum[0][0] = triangle[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) sum[i][j] = sum[i - 1][j] + triangle[i][j];
            else if (j == i) sum[i][j] = sum[i - 1][j - 1] + triangle[i][j];
            else sum[i][j] = max(sum[i - 1][j - 1], sum[i - 1][j]) + triangle[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, sum[n - 1][i]);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}