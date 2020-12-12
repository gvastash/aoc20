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

char turnLeft(char d) {
    switch (d) {
    case 'E':
        return 'N';
    case 'W':
        return 'S';
    case 'N':
        return 'W';
    case 'S':
        return 'E';
    }

    throw 1;
}

char turnRight(char d) {
    switch (d) {
    case 'E':
        return 'S';
    case 'W':
        return 'N';
    case 'N':
        return 'E';
    case 'S':
        return 'W';
    }

    throw 1;
}

pair<i64, i64> turnWaypointRight(pair<i64, i64> wp) {
    return {-wp.second, wp.first};
}

pair<i64, i64> turnWaypointLeft(pair<i64, i64> wp) {
    return { wp.second, -wp.first };
}

void handleMove(pair<i64, i64> e, i64& x, i64& y, char& d) {
    switch (e.first) {
    case 'N':
        y -= e.second;
        break;
    case 'S':
        y += e.second;
        break;
    case 'W':
        x -= e.second;
        break;
    case 'E':
        x += e.second;
        break;
    case 'L':
        for (i64 i = 0; i < e.second; i += 90) {
            d = turnLeft(d);
        }
        break;
    case 'R':
        for (i64 i = 0; i < e.second; i += 90) {
            d = turnRight(d);
        }
        break;
    case 'F':
        handleMove({ d, e.second }, x, y, d);
        break;
    default:
        throw 1;
    }
}


void handleWaypointMove(pair<i64, i64> e, i64& x, i64& y, i64& wpx, i64& wpy) {
    switch (e.first) {
    case 'N':
        wpy -= e.second;
        break;
    case 'S':
        wpy += e.second;
        break;
    case 'W':
        wpx -= e.second;
        break;
    case 'E':
        wpx += e.second;
        break;
    case 'L':
        for (i64 i = 0; i < e.second; i += 90) {
            auto t = turnWaypointLeft({ wpx, wpy });
            wpx = t.first;
            wpy = t.second;
        }
        break;
    case 'R':
        for (i64 i = 0; i < e.second; i += 90) {
            auto t = turnWaypointRight({ wpx, wpy });
            wpx = t.first;
            wpy = t.second;
        }
        break;
    case 'F':
        x += wpx * e.second;
        y += wpy * e.second;
        break;
    default:
        throw 1;
    }

}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    vector<pair<char, i64>> a;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            continue;
        }

        stringstream ss(line.substr(1));
        i64 val = 0;
        ss >> val;

        a.push_back({line[0], val});
    }

    /*
    i64 x = 0;
    i64 y = 0;
    char d = 'E';

    for (auto e : a) {
        handleMove(e, x, y, d);
        //cerr << x << " " << y << endl;
    }
    */

    i64 x = 0;
    i64 y = 0;
    i64 wpx = 10;
    i64 wpy = -1;
    for (auto e : a) {
        handleWaypointMove(e, x, y, wpx, wpy);
    }
    i64 R = abs(x) + abs(y);
    cout << R << endl;

    return 0;
}