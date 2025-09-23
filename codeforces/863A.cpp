#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

string solve() {
    string s;
    cin >> s;
    while (s.back() == '0') s.pop_back();
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != s[s.size() - i - 1]) return "NO";
    }
    return "YES";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

        cout << solve() << "\n";
    return 0;
}