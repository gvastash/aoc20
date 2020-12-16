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

    map<string, pair<pair<i64, i64>, pair<i64, i64>>> a;
    vector<vector<i64>> b;

    i64 cnt = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            cnt += 1;
            if (cnt == 3) {
                break;
            }
            else {
                continue;
            }
        }

        if (cnt == 0) {
            auto i = line.find(':');
            string prefix = line.substr(0, i);
            string postfix = line.substr(i + 1);

            stringstream ss(postfix);
            vector<string> q;
            while (!ss.eof()) {
                string t;
                ss >> t;
                if (t.empty()) {
                    break;
                }
                q.push_back(t);
            }

            vector<i64> z;
            for (i64 i = 0; i <= 2; i += 2) {
                auto j = q[i].find('-');
                stringstream ss1(q[i].substr(0, j));
                stringstream ss2(q[i].substr(j + 1));

                pair<i64, i64> p;
                ss1 >> p.first;
                ss2 >> p.second;

                if (i == 0) {
                    a[prefix].first = p;
                }
                else {
                    a[prefix].second = p;
                }
            }
        }
        else {
            auto i = line.find(':');
            if (i != string::npos) {
                continue;
            }

            replace(line.begin(), line.end(), ',', ' ');
            b.push_back(vector<i64>());

            stringstream ss(line);
            while (!ss.eof()) {
                i64 v;
                ss >> v;
                b.back().push_back(v);
            }
        }
    }

    vector<set<string>> z(b.front().size());
    for (i64 i = 0; i < b.front().size(); i++) {
        for (auto& e : a) {
            z[i].insert(e.first);
        }
    }

    vector<bool> discard(b.size());

    for (i64 i = 1; i < b.size(); i++) {
        for (i64 j = 0; j < b[i].size(); j++) {
            i64 v = b[i][j];
            bool f = false;
            for (auto& e : a) {
                if (e.second.first.first <= v && v <= e.second.first.second) {
                    f = true;
                }
                if (e.second.second.first <= v && v <= e.second.second.second) {
                    f = true;
                }
            }
            if (!f) {
                discard[i] = 1;
            }
        }
    }

    for (i64 j = 0; j < b.front().size(); j++) {
        for (auto& e : a) {
            bool f = true;
            for (i64 i = 0; i < b.size(); i++) {
                if (discard[i]) {
                    continue;
                }

                i64 v = b[i][j];

                if (e.second.first.first <= v && v <= e.second.first.second) {
                    continue;
                }
                if (e.second.second.first <= v && v <= e.second.second.second) {
                    continue;
                }
                f = false;
            }
            if (!f) {
                z[j].erase(e.first);
            }
        }
    }

    bool moved = true;
    while (moved) {
        moved = false;

        for (i64 i = 0; i < z.size(); i++) {
            if (z[i].size() == 1) {
                auto v = *z[i].begin();

                for (i64 j = 0; j < z.size(); j++) {
                    if (i == j) {
                        continue;
                    }
                    if (!z[j].count(v)) {
                        continue;
                    }
                    z[j].erase(v);
                    moved = true;
                }
                break;
            }
        }

        for (auto& e : a) {
            vector<i64> met;
            for (i64 i = 0; i < z.size(); i++) {
                if (z[i].count(e.first)) {
                    met.push_back(i);
                }
            }

            if (met.size() == 1 && z[met.front()].size() > 1) {
                auto it = z[met.front()].begin();
                while (it != z[met.front()].end()) {
                    if (*it == e.first) {
                        it++;
                    }
                    else {
                        z[met.front()].erase(it++);
                    }
                }
                moved = true;
                break;
            }
        }
    }

    for (i64 i = 0; i < z.size(); i++) {
        cerr << i << ": " << z[i].size();
        for (auto e : z[i]) {
            cerr << " " << e;
        }
        cerr << endl;
    }


    i64 R = 1;
    for (i64 i = 0; i < z.size(); i++) {
        if (z[i].begin()->find("departure") == string::npos) {
            continue;
        }
        R *= b[0][i];
    }
    cout << R << endl;
    

    return 0;
}