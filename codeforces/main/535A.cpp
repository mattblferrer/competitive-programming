#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<string> tens = {"", "", "twenty", "thirty", "forty", "fifty",
        "sixty", "seventy", "eighty", "ninety"};
    vector<string> teens = {"ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    vector<string> ones = {"", "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine"};
    if (n == 0) {
        cout << "zero";
        return;
    }
    if (n < 10) {
        cout << ones[n];
        return;
    }
    if (n < 20) {
        cout << teens[n - 10];
        return;
    }
    if (n % 10 == 0) {
        cout << tens[n / 10];
        return;
    }
    cout << tens[n / 10] << "-" << ones[n % 10];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}