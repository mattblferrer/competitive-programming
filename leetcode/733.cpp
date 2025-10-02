#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int m, n;
    bool is_valid(int x, int y) {
        if (x < 0 || x >= m) return false;
        if (y < 0 || y >= n) return false;
        return true;
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        m = image.size(), n = image[0].size();
        vector<int> xs = {1, 0, -1, 0}, ys = {0, 1, 0, -1};

        vector<vector<bool>> seen(m, vector<bool>(n));
        queue<pair<int, int>> q;
        q.push({sr, sc});
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int x = curr.first;
            int y = curr.second;
            seen[x][y] = true;
            for (int i = 0; i <= 3; i++) {
                int xn = x + xs[i];
                int yn = y + ys[i];
                if (!is_valid(xn, yn)) continue;
                if (image[x][y] != image[xn][yn]) continue;
                if (seen[xn][yn]) continue;
                q.push({xn, yn});
            }
            image[x][y] = color;
        }
        return image;
    }
};