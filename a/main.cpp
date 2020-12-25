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

//const i64 mod = 1'000'000'000ll + 7;
//const i64 mod = 998'244'353ll;

const i64 inf = 1'000'000'000'000'000'000ll;

const long double eps = 1e-8;

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    i64 p = 16915772;
    i64 q = 18447943;
    //i64 p = 5764801;
    //i64 q = 17807724;
    i64 m = 20201227;
    i64 d = 7;

    i64 pc = 0;
    i64 qc = 0;

    {
        i64 c = 1;
        while (true) {
            pc += 1;
            c *= d;
            c %= m;
            if (c == p) {
                break;
            }
        }
    }

    {
        i64 c = 1;
        while (true) {
            qc += 1;
            c *= d;
            c %= m;
            if (c == q) {
                break;
            }
        }
    }

    cerr << pc << " " << qc << endl;

    {
        i64 d = q;
        i64 c = 1;
        for (i64 tt = 1; tt <= pc; tt++) {
            c *= d;
            c %= m;
        }

        cout << c << endl;
    }

    {
        i64 d = p;
        i64 c = 1;
        for (i64 tt = 1; tt <= qc; tt++) {
            c *= d;
            c %= m;
        }

        cout << c << endl;
    }


    return 0;
}