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

    vector<string> a;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            continue;
        }

        a.push_back(line);
    }

    i64 n = a.size();
    i64 m = a.front().size();

    while (true) {
        auto b = a;
        for (i64 i = 0; i < n; i++) {
            for (i64 j = 0; j < m; j++) {
                auto getOccuped = [&]() {
                    i64 occuped = 0;
                    for (i64 x = -1; x <= 1; x++) {
                        for (i64 y = -1; y <= 1; y++) {
                            if (x == 0 && y == 0) {
                                continue;
                            }
                            for (i64 k = 1; true; k++) {
                                i64 r = i + x * k;
                                i64 c = j + y * k;
                                if (0 > r || r >= n) {
                                    break;
                                }
                                if (0 > c || c >= m) {
                                    break;
                                }
                                if (a[r][c] == '.') {
                                    continue;
                                }

                                if (a[r][c] == '#') {
                                    occuped += 1;
                                }
                                break;
                            }
                        }
                    }
                    return occuped;
                };
                switch (a[i][j]) {
                    case '.':
                        continue;
                    case 'L': {
                        if (!getOccuped()) {
                            b[i][j] = '#';
                        }
                        break;
                    }
                    case '#': {
                        if (getOccuped() >= 5) {
                            b[i][j] = 'L';
                        }
                        break;
                    }
                }
            }
        }
        if (a == b) {
            break;
        }
        a = b;
    }

    for (auto e : a) {
        cerr << e << endl;
    }

    i64 occuped = 0;
    for (auto e : a) {
        for (auto c : e) {
            occuped += (c == '#' ? 1 : 0);
        }
    }
    cout << occuped << endl;



    return 0;
}