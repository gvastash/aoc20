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

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    set<pair<i64, i64>> q;

    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            break;
        }

        i64 x = 0;
        i64 y = 0;


        for (i64 i = 0; i < line.size(); i++) {
            switch (line[i]) {
            case 'e':
                x -= 1;
                break;
            case 'w':
                x += 1;
                break;
            case 'n':
                i += 1;
                if (line[i] == 'e') {
                    y -= 1;
                }
                else if (line[i] == 'w') {
                    y -= 1;
                    x += 1;
                }
                else {
                    throw 1;
                }
                break;
            case 's':
                i += 1;
                if (line[i] == 'e') {
                    y += 1;
                    x -= 1;
                }
                else if (line[i] == 'w') {
                    y += 1;
                }
                else {
                    throw 1;
                }
                break;
            default:
                throw 1;
            }
        }

        pair<i64, i64> p = { x, y };
        if (q.count(p)) {
            q.erase(p);
        }
        else {
            q.insert(p);
        }
    }

    cout << q.size() << endl;


    const i64 m = 200;
    const vector<pair<i64, i64>> z = { {-1, 0}, {1, 0}, {0, -1}, {1, -1}, {-1, 1}, {0, 1} };
    for (i64 tt = 1; tt <= 100; tt++) {
        set<pair<i64, i64>> nq;

        for (i64 y = -m; y <= m; y++) {
            for (i64 x = -m; x <= m; x++) {
                i64 b = 0;
                for (auto e : z) {
                    b += q.count({ x + e.first, y + e.second });
                }

                if (q.count({ x, y })) {
                    if (0 < b && b <= 2) {
                        nq.insert({ x, y });
                    }
                }
                else {
                    if (b == 2) {
                        nq.insert({ x, y });
                    }
                }
            }
        }

        q = nq;
        cout << q.size() << endl;
    }



    return 0;
}