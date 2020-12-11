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

map<string, map<string, i64>> q;

map<string, bool> dp;

bool contains(string cur, string prv) {
    if (dp.count(cur)) {
        return dp[cur];
    }
    for (auto nxt : q[cur]) {
        if (nxt.first == prv) {
            continue;
        }
        if (!contains(nxt.first, cur)) {
            continue;
        }
        dp[cur] = true;
        break;
    }
    return dp[cur];
}

i64 dfs(string cur, string prv) {
    i64 R = 1;
    for (auto nxt : q[cur]) {
        if (nxt.first == prv) {
            continue;
        }
        R += dfs(nxt.first, cur) * nxt.second;
    }
    return R;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            continue;
        }

        vector<string> z;

        stringstream ss(line);
        while (!ss.eof()) {
            string t;
            ss >> t;
            z.push_back(t);
        }

        string key = z[0] + " " + z[1];

        i64 i = 4;
        if (z[i] == "no") {
            q[key];
            continue;
        }

        while (i < z.size()) {
            stringstream ss(z[i]);
            i64 cnt = 0;
            ss >> cnt;

            string val = z[i + 1] + " " + z[i + 2];
            q[key][val] = cnt;
            i += 4;
        }
    }

    for (auto t : q) {
        cerr << t.first << ": ";
        for (auto e : t.second) {
            cerr << e.first << "=" << e.second << " ";
        }
        cerr << endl;
    }
    dp["shiny gold"] = 1;

    i64 R = 0;
    for (auto t : q) {
        R += contains(t.first, "") ? 1 : 0;
    }

    cout << R - 1 << endl;

    i64 Q = dfs("shiny gold", "");
    cout << Q - 1 << endl;

    return 0;
}