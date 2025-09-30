#include <bits/stdc++.h>

void problem1157C1() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::string s;
    int left = 0, right = n - 1, last = 0;
    while (left <= right) {
        if (a[left] <= a[right]) {
            if (a[left] > last) {
                s += 'L';
                last = a[left];
                left++;
                continue;
            }
            else if (a[right] > last) {
                s += 'R';
                last = a[right];
                right--;
                continue;
            }
        }
        else {
            if (a[right] > last) {
                s += 'R';
                last = a[right];
                right--;
                continue;
            }
            else if (a[left] > last) {
                s += 'L';
                last = a[left];
                left++;
                continue;
            }
        }
        break;
    }

    std::cout << s.size() << "\n";
    for (int i = 0; i < s.size(); i++) {
        std::cout << s[i]; 
    }
}

int main() {
    problem1157C1();
    return 0;
}