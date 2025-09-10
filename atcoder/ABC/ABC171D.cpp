#include <iostream>
#include <map>

void ABC171D() {
    long long n, q, sum_a, a_i, b_i, c_i;
    sum_a = 0;
    std::cin >> n;
    std::map<long long, long long> a;
    for (int i = 0; i < n; i++) {  
        std::cin >> a_i;
        sum_a += a_i;
        if (a.count(a_i)) {
            a[a_i]++;
        }
        else {
            a[a_i] = 1;
        }
    }
    std::cin >> q;

    for (int i = 0; i < q; i++) {
        std::cin >> b_i >> c_i;
        a[c_i] += a[b_i];
        sum_a += (c_i - b_i) * a[b_i];
        std::cout << sum_a << std::endl;
        a.erase(b_i);
    }
}   

int main() { 
    ABC171D();
    return 0;
}