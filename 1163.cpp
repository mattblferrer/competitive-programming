#include <iostream>
#include <iterator>
#include <map>
#include <set>

void CSES1163() {
    long long x, n, p_i, left, right;
    std::cin >> x >> n;
    std::set<int> lights;
    std::map<int, int> gaps;
    lights.insert(0);
    lights.insert(x);
    gaps[x] = 1;

    for (long long i = 0; i < n; i++) {
        std::cin >> p_i;
        left = *std::prev(lights.lower_bound(p_i));
        right = *lights.upper_bound(p_i);
        lights.insert(p_i);

        gaps[right - left]--;
        gaps[p_i - left]++;
        gaps[right - p_i]++;
        if (!gaps[right - left]) {
            gaps.erase(right - left);
        }

        std::cout << (*std::prev(gaps.end())).first << " ";
    }
}

int main() {
    CSES1163();
    return 0;
}