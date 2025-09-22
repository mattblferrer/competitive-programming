#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

string solve() {
    int n;
    string s;
    cin >> n >> s;
    s += '1';
    
    int cnt = 0;
    bool sub = (s[0] == '1');
	for (int i = 0; i <= n; i++) {
		if (s[i] == '0') cnt++;
		if (i != 0 && s[i] == s[i - 1] && s[i] == '0') sub = false;
		if (i != 0 && s[i] == s[i - 1] && s[i] == '1') {
			if (sub && cnt % 2 == 1) return "NO";
			sub = true;
			cnt = 0;
		}
	}
    return "YES";   
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) cout << solve() << "\n";
    return 0;
}