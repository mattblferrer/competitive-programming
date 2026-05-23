#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_leap_year(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

void solve() {
    vector<int> month_days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<int> leap_days = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int start = 1901;
    int end = 2000;
    int curr_day = 2;  // 0 = sunday, 1 = monday, 2 = tuesday, ... 
    int ans = 0;
    for (int year = start; year <= end; year++) {
        for (int month = 0; month < 12; month++) {
            if (curr_day % 7 == 0) ans++;
            if (is_leap_year(year)) curr_day = (curr_day + leap_days[month]) % 7;
            else curr_day = (curr_day + month_days[month]) % 7;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}