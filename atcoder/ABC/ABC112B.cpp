#include <iostream>

void ABC112B() {
    int N, T;
    std::cin >> N >> T;
    int* c = new int[N];
    int* t = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> c[i] >> t[i];
    }

    int min_cost = 9999;
    for (int i = 0; i < N; i++) {
        if (t[i] <= T) {
            min_cost = std::min(min_cost, c[i]);
        }
    }
    if (min_cost == 9999) {
        std::cout << "TLE";
        return;
    }
    std::cout << min_cost;
}

int main() {
    ABC112B();
    return 0;
}