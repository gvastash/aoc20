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

    vector<i64> a;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        i64 val;
        ss >> val;
        a.push_back(val);
    }

    const i64 w = 25;
    i64 target = 0;
    for (i64 i = w; i < a.size(); i++) {
        bool valid = false;
        for (i64 j = i - w; j < i; j++) {
            for (i64 k = j + 1; k < i; k++) {
                valid |= a[j] + a[k] == a[i];
            }
        }
        if (!valid) {
            target = a[i];
            break;
        }
    }

    for (i64 i = 0; i < a.size(); i++) {
        i64 s = 0;
        for (i64 j = i; j < a.size(); j++) {
            s += a[j];
            if (s == target) {
                if (i == j) {
                    break;
                }
                i64 low = a[i];
                i64 high = a[i];
                for (i64 k = i; k <= j; k++) {
                    low = min(low, a[k]);
                    high = max(high, a[k]);
                }
                cout << low + high << endl;
            }
        }
    }

    return 0;
}