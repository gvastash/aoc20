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
    i64 R = 0;
    map<char, i64> a;
    i64 c = 0;

    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            for (auto e : a) {
                if (e.second != c) {
                    continue;
                }
                R += 1;
            }
            a.clear();
            c = 0;
            continue;
        }

        c += 1;
        for (auto c : line) {
            a[c] += 1;
        }
    }
    for (auto e : a) {
        if (e.second != c) {
            continue;
        }
        R += 1;
    }
    cout << R << endl;


    return 0;
}