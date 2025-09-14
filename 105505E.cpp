#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> fl(n), fr(n);
    int curr = 0;
    for (int i = 0; i < n; i++) {
        fr[i] = curr;
        if (a[i] != 0) curr = i;
    }
    curr = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        fl[i] = curr;
        if (a[i] != 0) curr = i;
    }

    int left = 0, right = n - 1;
    for (int i = 1; i <= n; i++) {
        if (a[left] == 0 && a[right] == 0) {
            if (a[fl[left]] < a[fr[right]]) {
                a[left] = i;
                left++;
            }
            else if (a[fl[left]] > a[fr[right]]) {
                a[right] = i;
                right--;
            }
            else if (fl[left] - left < right - fr[right]) {
                a[left] = i;
                left++;
            }
            else {
                a[right] = i;
                right--;
            }
        }
        else if (a[left] == i) left++;
        else if (a[right] == i) right--;
        else if (a[left] == 0) {
            a[left] = i;
            left++;
        }
        else if (a[right] == 0) {
            a[right] = i;
            right--;
        }
        else {
            cout << "*";
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}