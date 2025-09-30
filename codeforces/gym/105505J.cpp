#include <bits/stdc++.h>
using namespace std;
struct interval
{
    int left;
    long double right;
};
interval intersect(const interval& left, const interval& right)
{
    if (left.right < right.left || right.right < left.left) return {-1, -1};
    else return {min(left.left, right.left), max(left.right, right.right)};
}
bool interval_sorter(const interval& left, const interval& right)
{
    return left.left <= right.left;
}
const long double PI = 3.141592653589793238;
const int MAX = 300'001;
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(19);
    long double angle;
    int people;
    cin >> angle >> people;
    long double angle_radians = angle / (long double) 180 * PI;
    long double ratio = (long double) 1 / tan(angle_radians);
    vector<interval> intervals(MAX, {-1, -1});
    for (int i = 0; i < people; i++)
    {   
        int x, h;
        cin >> x >> h;
        intervals[x] = {x, (long double) x + (long double) h * ratio};
    }
    long double total_distance = 0;
    interval overarching_interval = intervals[0];
    for (int i = 0; i < MAX; i++)
    {
        if (intervals[i].left == -1) continue;
        interval new_interval = intersect(overarching_interval, intervals[i]);
        if (new_interval.left == -1)
        {
            total_distance += overarching_interval.right - (long double) overarching_interval.left;
            overarching_interval = intervals[i];
        }
        else overarching_interval = new_interval;
    }
    total_distance += overarching_interval.right - (long double) overarching_interval.left;
    cout << total_distance;
}