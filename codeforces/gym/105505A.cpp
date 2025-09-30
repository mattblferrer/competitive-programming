#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

int solve() {
    string s;
    cin >> s;
    set<char> unique;
    for (int i = 0; i < s.size(); i++) {
        unique.insert(s[i]);
    }
    return s.size() - unique.size();
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << solve() << "\n";
    return 0;
}