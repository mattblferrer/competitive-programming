#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;

void solve() {
    map<char, int> p;
    p['Q'] = 9;
    p['R'] = 5;
    p['B'] = 3;
    p['N'] = 3;
    p['P'] = 1;
    p['K'] = 0;
    p['.'] = 0;

    vector<string> board(8);
    for (int i = 0; i < 8; i++) cin >> board[i];
    int black = 0, white = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (islower(board[i][j])) black += p[toupper(board[i][j])];
            else white += p[board[i][j]];
        }
    }
    if (black < white) cout << "White";
    else if (black > white) cout << "Black";
    else cout << "Draw";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}