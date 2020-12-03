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

using namespace std;

typedef long long int i64;

const i64 inf = 1'000'000'000'000'000'000ll + 7;

int main(int argc, char* argv[]) {
    vector<string> a;
    while (!cin.eof()) {
        string t;
        cin >> t;
        a.push_back(t);
    }

    i64 R = 1;
    for (i64 i = 0; i < a.front().size(); i++) {
        for (pair<i64, i64> e : vector<pair<i64, i64>>({ {1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1} })) {
            i64 res = 0;

            i64 r = 0;
            i64 c = i;

            while (r < a.size()) {
                res += a[r][c] == '#' ? 1 : 0;
                r += e.first;
                c += e.second;
                c %= a.front().size();
            }

            cerr << res << endl;
            R *= res;
        }
        break;
    }

    cout << R << endl;

    return 0;
}