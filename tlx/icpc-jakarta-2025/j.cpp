#include <iostream>
using ll = long long;
static const ll MAX = 2e18;

int main() {
    ll n, a, b; std::cin >> n >> a >> b;
    if (a != b) { std::cout << "NO"; return 0; }

    ll short0 = MAX, short1 = MAX, cur0 = 0, cur1 = 0;
    bool bit = true;
    while (!(n & 1)) { n >>= 1; }
    while (n) {
        if (n & 1) {
            if (bit) { cur1++; }
            else { short0 = std::min(short0, cur0); cur1 = 1; bit = true; }
        }
        else {
            if (!bit) { cur0++; }
            else { short1 = std::min(short1, cur1); cur0 = 1; bit = false; }
        }
        n >>= 1;
    }
    short1 = std::min(short1, cur1);

    // std::clog << short0 << ' ' << short1 << '\n';

    if (std::max(short0, short1) < 2) { std::cout << "NO"; return 0; }
    std::cout << "YES";
}