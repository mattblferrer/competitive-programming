#include <bits/stdc++.h>
using namespace std;

struct cont {
    string name;
    int pts, time;
};

int main() {
    int n;
    cin >> n;
    vector<cont> conts(n);
    for (int i = 0; i < n; ++i) {
        string name;
        int a, b, c, d;
        cin >> name >> a >> b >> c >> d;
        conts[i] = {name, a + c, b + d};
    }
    sort(conts.begin(), conts.end(), [](cont x, cont y) {
        if (x.pts != y.pts) return x.pts > y.pts;
        if (x.time != y.time) return x.time < y.time;
        return x.name < y.name;
    });
    for (const auto& cont: conts) {
        cout << cont.name << "\n";
    }
    return 0;
}