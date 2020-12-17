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
            break;
        }
        a.push_back(line);
    }

    const i64 m = 6;
    i64 clen = 2 * m + a.size();
    vector<vector<vector<vector<char>>>> b(2 * m + 1, vector<vector<vector<char>>>(2 * m + 1, vector<vector<char>>(clen, vector<char>(clen, '.'))));
    for (i64 i = 0; i < a.size(); i++) {
        for (i64 j = 0; j < a[i].size(); j++) {
            b[m][m][m + i][m + j] = a[i][j];
        }
    }

    for (i64 qm = 0; qm < 6; qm++) {
        auto c = b;

        for (i64 h = 0; h < b.size(); h++) {
            for (i64 k = 0; k < b[h].size(); k++) {
                for (i64 i = 0; i < b[h][k].size(); i++) {
                    for (i64 j = 0; j < b[h][k][i].size(); j++) {

                        i64 cnt = 0;

                        for (i64 dw = -1; dw <= 1; dw++) {
                            for (i64 dz = -1; dz <= 1; dz++) {
                                for (i64 dx = -1; dx <= 1; dx++) {
                                    for (i64 dy = -1; dy <= 1; dy++) {
                                        if (dx == 0 && dy == 0 && dz == 0 && dw == 0) {
                                            continue;
                                        }

                                        i64 w = h + dw;
                                        i64 z = k + dz;
                                        i64 x = i + dx;
                                        i64 y = j + dy;

                                        if (0 > w || w >= b.size()) {
                                            continue;
                                        }
                                        if (0 > z || z >= b[h].size()) {
                                            continue;
                                        }
                                        if (0 > x || x >= b[h][k].size()) {
                                            continue;
                                        }
                                        if (0 > y || y >= b[h][k][i].size()) {
                                            continue;
                                        }

                                        if (b[w][z][x][y] == '#') {
                                            cnt += 1;
                                        }
                                    }
                                }
                            }
                        }

                        if (c[h][k][i][j] == '#') {
                            if (2 > cnt || cnt > 3) {
                                c[h][k][i][j] = '.';
                            }
                        }
                        else {
                            if (cnt == 3) {
                                c[h][k][i][j] = '#';
                            }
                        }
                    }
                }
            }
        }

        b = c;
    }

    i64 R = 0;
    for (i64 h = 0; h < b.size(); h++) {
        for (i64 k = 0; k < b[h].size(); k++) {
            for (i64 i = 0; i < b[h][k].size(); i++) {
                for (i64 j = 0; j < b[h][k][i].size(); j++) {
                    R += (b[h][k][i][j] == '.' ? 0 : 1);
                }
            }
        }
    }

    cout << R << endl;

    return 0;
}