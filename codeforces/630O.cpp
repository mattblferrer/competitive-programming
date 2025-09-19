#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    double px, py, vx, vy, a, b, c, d;
    cin >> px >> py >> vx >> vy >> a >> b >> c >> d;
    vector<pair<double, double>> points(7);

    double vx_norm = vx / sqrt(vx * vx + vy * vy);
    double vy_norm = vy / sqrt(vx * vx + vy * vy);
    points[0] = {px + vx_norm * b, py + vy_norm * b};
    points[1] = {px - vy_norm * (a / 2), py + vx_norm * (a / 2)};
    points[2] = {px - vy_norm * (c / 2), py + vx_norm * (c / 2)};
    points[3] = {px - vy_norm * (c / 2) - vx_norm * d, py + vx_norm * (c / 2) - vy_norm * d};
    points[4] = {px + vy_norm * (c / 2) - vx_norm * d, py - vx_norm * (c / 2) - vy_norm * d};
    points[5] = {px + vy_norm * (c / 2), py - vx_norm * (c / 2)};
    points[6] = {px + vy_norm * (a / 2), py - vx_norm * (a / 2)};

    for (int i = 0; i < 7; i++) {
        cout << points[i].first << " " << points[i].second << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}