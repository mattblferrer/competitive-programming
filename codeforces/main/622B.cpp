#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    string time;
    int a;
    cin >> time >> a;
    int hh = stoi(time.substr(0, 2));
    int mm = stoi(time.substr(3, 2));
    int mins = hh * 60 + mm + a;
    int new_hh = (mins / 60) % 24;
    int new_mm = mins % 60;
    if (new_hh < 10) cout << 0 << new_hh << ':';
    else cout << new_hh << ':';
    if (new_mm < 10) cout << 0 << new_mm;
    else cout << new_mm;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}