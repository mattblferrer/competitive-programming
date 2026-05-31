#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ifstream file("p042_words.txt");
    string all_words;
    vector<string> words;
    getline(file, all_words);
    string curr_word = "";
    for (int i = 0; i < all_words.size(); i++) {
        if (all_words[i] == ',') {
            words.push_back(curr_word);
            curr_word = "";
        }
        else if (all_words[i] == '"') continue;
        else curr_word.push_back(all_words[i]);
    }
    set<int> triangles;
    for (int i = 0; i < 1000; i++) {
        triangles.insert(i * (i + 1) / 2);
    }
    int ans = 0;
    for (int i = 0; i < words.size(); i++) {
        int curr = 0;
        for (int j = 0; j < words[i].size(); j++) {
            curr += words[i][j] - 'A' + 1;
        }
        if (triangles.count(curr)) ans++;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}