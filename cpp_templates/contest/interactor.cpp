// Contents
//   rnd    random integer in [lo, hi], O(1)
//   wrong  reject the solution: print the reason to stderr and exit with code 1
//   main   example interactor (guess a hidden number with "? y" queries), for interact.py

// local interactor for interactive problems; interact.py runs it as "interactor seed" and joins its stdin / stdout to
// the solution's stdout / stdin. It makes the hidden test from the seed, exits with code 0 to accept (1 to reject) and
// can leave a message on stderr. Replace main with the problem's protocol and flush after every write (endl does)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
mt19937_64 rng;

// random integer in [lo, hi], O(1)
ll rnd(ll lo, ll hi) {
    return lo + rng() % (hi - lo + 1);
}

// reject the solution: print the reason to stderr and exit with code 1
[[noreturn]] void wrong(const string &msg) {
    cerr << "wrong answer: " << msg << endl;
    exit(1);
}

int main(int argc, char **argv) {
    rng.seed(atoll(argv[argc - 1]));

    // example protocol: print n, then answer "? y" with <, > or = (is the hidden x below, above or at y), at most 30
    // times, until the solution prints "! x"
    ll n = rnd(1, 1e9), x = rnd(1, n), queries = 0;
    cout << n << endl;
    while (true) {
        string type;
        ll y;
        if (!(cin >> type >> y)) wrong("the solution stopped before answering");
        if (type == "!") {
            if (y != x) wrong("answered " + to_string(y) + ", hidden number was " + to_string(x));
            break;
        }
        if (type != "?") wrong("unknown command " + type);
        if (++queries > 30) wrong("more than 30 queries");
        cout << (x < y ? "<" : x > y ? ">" : "=") << endl;
    }
    cerr << "ok: " << queries << " queries" << endl;
    return 0;
}
