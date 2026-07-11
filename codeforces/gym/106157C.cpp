#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<char> two_holes = {'B'};
vector<char> one_hole = {'A', 'D', 'O', 'P', 'Q', 'R'};
const int H = 5;
vector<vector<char>> grid(H);

void add_special(string &s, int holes)
{
    if (holes == 0)
    {
        for (int i = 0; i < H; i++)
        {
            for (char c : s) grid[i].push_back(c);
        }
    }
    else if (holes == 1)
    {
        for (char c : s)
        {
            grid[0].push_back(c);
            grid[4].push_back(c);
        }

        for (int i = 0; i < s.size(); i++)
        {
            for (int j = 1; j <= 3; j++)
            {
                if (i == 0 || i == s.size() - 1)
                {
                    grid[j].push_back('X');
                }
                else
                {
                    grid[j].push_back('.');
                }
            }
        }
    }
    else if (holes == 2)
    {
        for (char c : s)
        {
            grid[0].push_back(c);
            grid[2].push_back(c);
            grid[4].push_back(c);
        }

        for (int i = 0; i < s.size(); i++)
        {
            if (i == 0 || i == s.size() - 1)
            {
                grid[1].push_back('X');
                grid[3].push_back('X');
            }
            else
            {
                grid[1].push_back('.');
                grid[3].push_back('.');
            }
        }
    }
}

void add(int holes)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (holes == 2)
            {
                if (i == 1 && (j == 1 || j == 3)) grid[j].push_back('.');
                else grid[j].push_back('X');
            }
            else if (holes == 1)
            {
                if (i == 1 && (j == 2)) grid[j].push_back('.');
                else grid[j].push_back('X');
            }
            else
            {
                grid[j].push_back('X');
            }
        }
    }
}

void add_space()
{
    for (int i = 0; i < H; i++)
    {
        grid[i].push_back('.');
    }
}

int get_hole_count(char check)
{
    for (char c : two_holes) if (c == check) return 2;
    for (char c : one_hole) if (c == check) return 1;
    return 0;
}

void solve() {
    // your solution here
    string c1, c2;
    cin >> c1 >> c2;

    vector<int> hole_count;
    for (int i = 0; i < c1.size(); i++)
    {
        hole_count.push_back(get_hole_count(c1[i]));
    }

    for (int i = 0; i < hole_count.size(); i++)
    {
        if (i == 0) add_special(c2, hole_count[i]);
        else add(hole_count[i]);

        add_space();
    }

    for (int i = 0; i < H; i++)
    {
        for (char c : grid[i]) cout << c;
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}