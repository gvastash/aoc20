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

    i64 amask = -1;
    i64 omask = 0;

    map<i64, i64> z;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        vector<string> tokens;

        while (!ss.eof()) {
            string t;
            ss >> t;
            tokens.push_back(t);
        }

        if (tokens.front() == "mask") {
            amask = -1;
            omask = 0;

            reverse(tokens.back().begin(), tokens.back().end());
            for (i64 i = 0; i < tokens.back().size(); i++) {
                if (tokens.back()[i] == '0') {
                    amask ^= (1ll << i);
                    omask &= ~(1ll << i);
                }
                if (tokens.back()[i] == '1') {
                    omask ^= (1ll << i);
                    amask |= (1ll << i);
                }
            }
        }
        else {
            auto b = tokens.front().find('[');
            auto e = tokens.front().find(']');
            stringstream ss1(tokens.front().substr(b + 1, e - b - 1));
            stringstream ss2(tokens.back());

            i64 adr;
            i64 val;

            ss1 >> adr;
            ss2 >> val;

            for (i64 i = 0; i < 36; i++) {
                if (omask & (1ll << i)) {
                    adr |= (1ll << i);
                }
            }

            vector<i64> adrs;
            adrs.push_back(adr);
            for (i64 i = 0; i < 36; i++) {
                if (!(omask & (1ll << i)) && (amask & (1ll << i))) {
                    vector<i64> nadrs;
                    for (auto e : adrs) {
                        nadrs.push_back(e | (1ll << i));
                        nadrs.push_back(e & ~(1ll << i));
                    }
                    adrs = nadrs;
                }
            }

            for (auto m : adrs) {
                z[m] = val;
            }
        }
    }

    i64 R = 0;
    for (auto t : z) {
        R += t.second;
    }

    cout << R << endl;

    return 0;
}