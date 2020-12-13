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

    i64 t;
    cin >> t;
    string line;
    cin >> line;
    replace(line.begin(), line.end(), ',', ' ');

    vector<i64> a;
    stringstream ss(line);
    while (!ss.eof()) {
        string z;
        ss >> z;
        if (z.empty()) {
            break;
        }
        stringstream tss(z);
        i64 val = 0;
        tss >> val;
        //if (val) {
            a.push_back(val);
        //}
    }


    /*
    i64 bv = inf;
    i64 bi = 0;
    for (auto e : a) {
        i64 v = t % e == 0 ? 0 : e - t % e;
        if (bv > v) {
            bv = v;
            bi = e;
        }
    }

    cerr << bv << " " << bi << endl;
    cout << bv * bi << endl;
    */

    i64 m = 0;
    i64 d = a.front();
    for (i64 i = 1; i < a.size(); i++) {
        if (!a[i]) {
            continue;
        }
        for (i64 j = 0; j < a[i]; j++) {
            i64 v = (d * j + m) % a[i];
            if (v > 0) {
                v = a[i] - v;
            }
            if (v != i % a[i]) {
                continue;
            }
            m = (d * j + m) % (d * a[i]);
            d *= a[i];
            break;
        }
    }

    cout << m << endl;

    return 0;
}