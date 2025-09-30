#include <bits/stdc++.h>

void problem4B() {
    int d, sumTime, minTimeSum = 0, maxTimeSum = 0;
    std::cin >> d >> sumTime;
    std::vector<int> minTime(d), maxTime(d), time(d);
    for (int i = 0; i < d; i++) {
        std::cin >> minTime[i] >> maxTime[i];
        time[i] = minTime[i];
        minTimeSum += minTime[i];
        maxTimeSum += maxTime[i];
    }
    if (sumTime < minTimeSum || sumTime > maxTimeSum) {
        std::cout << "NO";
        return;
    }
    std::cout << "YES\n";
    sumTime -= minTimeSum;
    for (int i = 0; i < d; i++) {
        if (sumTime == 0) break;
        while (time[i] < maxTime[i]) {
            time[i]++;
            sumTime--;
            if (sumTime == 0) break;
        }
    }
    for (int t: time) {
        std::cout << t << " ";
    }
}

int main() {
    problem4B();
    return 0;
}