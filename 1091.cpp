#include <iostream>
#include <iterator>
#include <map>

int main() { 
    int n, m, h_i;
    std::cin >> n >> m; 
    std::map<int, int> h{{-1, 10000000}};
    int* t = new int[m];
    
    for (int i = 0; i < n; i++) {
        std::cin >> h_i;
        if (h.count(h_i)) {
            h[h_i]++;
        }
        else {
            h[h_i] = 1;
        }
    }
    for (int i = 0; i < m; i++) {
        std::cin >> t[i];
    }

    for (int i = 0; i < m; i++) {
        int ticket = std::prev(h.upper_bound(t[i]))->first;
        std::cout << ticket << "\n";
        h[ticket]--;

        if (h[ticket] == 0) {
            h.erase(ticket);
        }      
    }   
    return 0;
}