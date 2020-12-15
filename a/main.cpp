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

    string s;
    cin >> s;
    replace(s.begin(), s.end(), ',', ' ');

    vector<i64> a;
    stringstream ss(s);
    while (!ss.eof()) {
        i64 t;
        ss >> t;

        a.push_back(t);
    }

    //for (auto e : a) {
    //    cerr << e << " ";
    //}

    map<i64, i64> q;
    map<i64, i64> z;

    i64 tm = 1;
    i64 last = -1;
    for (i64 i = 0; i < a.size(); i++) {
        q[last = a[i]] = tm++;
        //cerr << last << endl;
    }

    while (tm <= 30'000'000) {
        if (q.count(last) && z.count(last)) {
            last = q[last] - z[last];
        }
        else {
            last = 0;
        }

        if (q.count(last)) {
            z[last] = q[last];
        }
        q[last] = tm++;
        //cerr << last << endl;
    }

    cout << last << endl;



    return 0;
}