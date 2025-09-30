#include <iostream>
#include <set>
#include <string>

void problem639A() {
    int n, k, q, type_i, id_i;
    std::cin >> n >> k >> q;
    int* t = new int[n];
    bool* online = new bool[n];
    std::set<int> disp;

    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
        online[i] = false;
    }

    for (int i = 0; i < q; i++) {
        std::cin >> type_i >> id_i;
        id_i--;

        if (type_i == 1) { // friend id_i becomes online
            disp.insert(t[id_i]);
            online[id_i] = true;
            if (disp.size() > k) {
                disp.erase(disp.upper_bound(0));
            }
        }
        else if (type_i == 2) { // check whether id_i is displayed
            if (!online[id_i] || disp.upper_bound(t[id_i]) == disp.begin()) {
                std::cout << "NO" << std::endl;
            }
            else {
                std::cout << "YES" << std::endl;
            }
        }
    }
}

int main() {
    problem639A();	
    return 0;
}