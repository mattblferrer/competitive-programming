#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

long long problem922D() {
    int n;
    std::cin >> n;
    std::string t_i;
    std::vector<std::string> t;
    for (int i = 0; i < n; i++) {
        std::cin >> t_i;
        t.push_back(t_i);
    }
    std::sort(t.begin(), t.end(), [](std::string x, std::string y) {
        return (double)(std::count(x.begin(), x.end(), 'h')) / (double)(x.length()) < 
            (double)(std::count(y.begin(), y.end(), 'h')) / (double)(y.length());
    });
    long long noise = 0;
    int s = 0;
    int h = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t[i].length(); j++) {
            if (t[i][j] == 's') {
                s++;
            }
            else {
                noise += s;
                h++;
            }
        }
    }
    return noise;
}

int main() {
    std::cout << problem922D();
    return 0;
}