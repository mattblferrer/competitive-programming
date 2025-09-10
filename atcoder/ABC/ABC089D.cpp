#include <iostream>

void ABC089D() {
    int h, w, d, q, a_ij, l_i, r_i;
    int x_1, y_1, x_2, y_2, dist;
    std::cin >> h >> w >> d;
    int* grid = new int[h * w]; 
    int* grid_sum = new int[h * w + 1]; 
    
    for (int i = 0; i < h * w; i++) {
        std::cin >> a_ij;
        grid[a_ij] = i;
    }
    for (int i = 1; i <= d; i++) {
        grid_sum[i] = 0;
    }
    for (int i = d + 1; i <= h * w; i++) {
        x_1 = grid[i] % w;
        x_2 = grid[i - d] % w;
        y_1 = grid[i] / w;
        y_2 = grid[i - d] / w;
        dist = abs(x_1 - x_2) + abs(y_1 - y_2);
        grid_sum[i] = grid_sum[i - d] + dist;
    }
    
    std::cin >> q;
    for (int i = 0; i < q; i++) { 
        std::cin >> l_i >> r_i;
        std::cout << grid_sum[r_i] - grid_sum[l_i] << std::endl;
    }
}

int main() {  
    ABC089D();
    return 0;
}