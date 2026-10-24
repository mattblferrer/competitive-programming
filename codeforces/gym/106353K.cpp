#include <bits/stdc++.h> 
using namespace std;

int main() {
    int h, w, k, i, t;
    cin >> h >> w >> k >> i >> t;
    vector<vector<char>> grid(h, vector<char>(w, '*'));
    grid[h - 1][0] = 'K'; grid[h - 1][1] = 'I'; grid[h - 1][2] = 'T';
    k--; i--; t--;
    for (int j = h - 1; j >= 0; j--)
    {
        int cur_y = j; int cur_x = 0;
        while (cur_y < h && cur_x < w)
        {
            if (grid[cur_y][cur_x] == '*')
            {
                if (k > 0)
                {
                    grid[cur_y][cur_x] = 'K'; k--;
                }
                else if (t > 0)
                {
                    grid[cur_y][cur_x] = 'T'; t--;
                }
                else
                {
                    grid[cur_y][cur_x] = 'I'; i--;
                }
            }

            cur_y += 1; cur_x += 1;
        }
    }

    for (int j = 1; j < w; j++)
    {
        int cur_y = 0; int cur_x = j;
        while (cur_y < h && cur_x < w)
        {
            if (grid[cur_y][cur_x] == '*')
            {
                if (k > 0)
                {
                    grid[cur_y][cur_x] = 'K'; k--;
                }
                else if (t > 0)
                {
                    grid[cur_y][cur_x] = 'T'; t--;
                }
                else
                {
                    grid[cur_y][cur_x] = 'I'; i--;
                }
            }

            cur_y += 1; cur_x += 1;
        }
    }

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            cout << grid[i][j];
        }
        cout << "\n";
    }
}