#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdint.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <string>

#include <algorithm>
#include <functional>
#include <bitset>
#include <functional>
#include <chrono>
#include <random>

#define sqr(x) (x) * (x)

typedef unsigned int u32;
typedef int i32;
typedef unsigned long long int u64;
typedef long long int i64;
typedef uint16_t u16;
typedef int i16;
typedef uint8_t u8;
typedef int8_t i8;

using namespace std;
using namespace std::chrono;

const i64 mod = 1'000'000'000ll + 7;
//const i64 mod = 998'244'353ll;

const i64 inf = 1'000'000'000'000'000'000ll;

const long double eps = 1e-8;

void solve() {
    string s = "789465123";
    char c = s.front();

    for (i64 tt = 1; tt <= 100; tt++) {
        stringstream qs;
        for (i64 i = 0; i < s.size(); i++) {
            if (s[i] == c) {
                for (i64 j = 1; j <= 3; j++) {
                    qs << s[(i + j) % s.size()];
                }
                break;
            }
        }
        string q = qs.str();
        char p = c - 1;
        while (true) {
            if (p == '0') {
                p = '9';
                continue;
            }

            bool ok = true;
            for (auto t : q) {
                if (t == p) {
                    p -= 1;
                    ok = false;
                    break;
                }
            }


            if (ok) {
                break;
            }
        }

        stringstream ss;
        for (i64 i = 0; i < s.size(); i++) {
            bool ok = true;
            for (i64 j = 0; j < q.size(); j++) {
                if (q[j] == s[i]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                continue;
            }
            ss << s[i];
            if (s[i] == p) {
                ss << q;
            }
        }

        s = ss.str();
        for (i64 i = 0; i < s.size(); i++) {
            if (s[i] == c) {
                c = s[(i + 1) % s.size()];
                break;
            }
        }

        cerr << s << endl;
    }

    for (i64 i = 0; i < s.size(); i++) {
        if (s[i] == '1') {
            stringstream ss;
            for (i64 j = 1; j < s.size(); j++) {
                ss << s[(i + j) % s.size()];
            }
            cout << ss.str() << endl;
            break;
        }
    }
}

void solve2() {
    string s = "789465123";

    const i64 m = 1'000'000; // s.size();

    vector<i64> l(m + 1);
    vector<i64> r(m + 1);

    for (i64 i = 0; i < s.size(); i++) {
        if (i > 0) {
            l[(i64)s[i] - '0'] = (i64)s[i - 1] - '0';
        }

        if (i < s.size() - 1) {
            r[(i64)s[i] - '0'] = (i64)s[i + 1] - '0';
        }
    }

    for (i64 i = s.size() + 1; i <= m; i++) {
        if (i > s.size()) {
            l[i] = i - 1;
        }
        if (i < m) {
            r[i] = i + 1;
        }
    }

    if (m > s.size()) {
        l[(i64)s.front() - '0'] = m;
        r[m] = (i64)s.front() - '0';

        r[(i64)s.back() - '0'] = s.size() + 1;
        l[s.size() + 1] = (i64)s.back() - '0';
    }
    else {
        l[(i64)s.front() - '0'] = (i64)s.back() - '0';
        r[(i64)s.back() - '0'] = (i64)s.front() - '0';
    }

    i64 c = (i64)s.front() - '0';

    if (false) {
        i64 v = c;
        do {
            cerr << v << " ";
            v = r[v];
        } while (v != c);
        cerr << endl;
    }

    if (false) {
        i64 v = c;
        do {
            cerr << v << " ";
            v = l[v];
        } while (v != c);
        cerr << endl;
    }

    for (i64 tt = 1; tt <= 10'000'000; tt++) {
        set<i64> q;
        i64 ql = 0;
        i64 qr = 0;

        if (false) {
            i64 v = c;
            do {
                cerr << v << " ";
                v = r[v];
            } while (v != c);
            cerr << endl;
        }


        i64 t = c;
        for (i64 i = 0; i < 3; i++) {
            t = r[t];
            if (!ql) {
                ql = t;
            }
            qr = t;
            q.insert(t);
        }

        t = r[t];

        r[c] = t;
        l[t] = c;

        if (false) {
            i64 v = c;
            do {
                cerr << v << " ";
                v = r[v];
            } while (v != c);
            cerr << endl;
        }

        //l[ql] = 0;
        //r[qr] = 0;

        i64 p = c - 1;
        while (true) {
            if (!p) {
                p = m;
                continue;
            }

            if (q.count(p)) {
                p -= 1;
                continue;
            }

            break;
        }

        i64 np = r[p];

        r[p] = ql;
        l[ql] = p;


        l[np] = qr;
        r[qr] = np;


        if (false) {
            i64 v = c;
            do {
                cerr << v << " ";
                v = r[v];
            } while (v != c);
            cerr << endl;
        }

        c = r[c];
    }

    if (false) {
        i64 v = c;
        do {
            cerr << v << " ";
            v = r[v];
        } while (v != c);
        cerr << endl;
    }

    i64 v1 = r[1];
    i64 v2 = r[r[1]];
    cerr << v1 << " " << v2 << endl;
    cout << v1 * v2 << endl;
}


int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    solve2();

    return 0;
}