#include <iostream>

void ABC112C() {
    int N;
    std::cin >> N;
    int* x = new int[N];
    int* y = new int[N];
    int* h = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> x[i] >> y[i] >> h[i];
    }
    int height;
    bool found = false;

    for (int cx = 0; cx <= 100; cx++) {
        for (int cy = 0; cy <= 100; cy++) {
            for (int c = 0; c < N; c++) { 
                height = h[c] + abs(x[c] - cx) + abs(y[c] - cy);
                if (h[c] != 0) {
                    break;
                }
            }
            found = true;
            for (int c = 0; c < N; c++) {
                if (h[c] != std::max(0, height - abs(x[c] - cx) - abs(y[c] - cy))) {
                    found = false;
                    break;
                }
            }
            if (found) {
                std::cout << cx << " " << cy << " " << height;  
                return;
            }
        }
    }
}

int main() {
    ABC112C();
    return 0;
}