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


map<i64, vector<vector<i64>>> rules;
map<i64, char> terms;

set<i64> match(string& s, i64 rule, i64 i, i64 lvl) {
    if (lvl > 100) {
        return {};
    }

    if (i >= s.size()) {
        return {};
    }
    if (terms.count(rule)) {
        if (terms[rule] != s[i]) {
            return {};
        }
        else {
            return {i + 1};
        }
    }



    set<i64> z;
    for (auto& parts : rules[rule]) {
        set<i64> q = { i };

        for (auto part : parts) {
            set<i64> nq;
            for (auto j : q) {
                auto m = match(s, part, j, lvl + 1);
                for (auto k : m) {
                    nq.insert(k);
                }
            }
            q = nq;
        }

        for (auto k : q) {
            z.insert(k);
        }

    }

    return z;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    i64 R = 0;
    i64 cnt = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);
        if (line.empty()) {
            cnt++;
            if (cnt > 1) {
                break;
            }
            else {
                auto vmax = max(rules.rbegin()->first, terms.rbegin()->first);
                terms[vmax + 1] = '#';
                rules[-1].push_back({});
                rules[-1].back().push_back(0);
                rules[-1].back().push_back(vmax + 1);
            }
            continue;
        }

        if (!cnt) {
            auto colon = line.find(':');
            stringstream rss(line.substr(0, colon));
            i64 rule;
            rss >> rule;
            string data = line.substr(colon + 1);

            if (rule == 8) {
                data = data + " | 42 8";
            }
            if (rule == 11) {
                data = data + " | 42 11 31";
            }

            auto quote = data.find('"');
            if (quote != string::npos) {
                terms[rule] = data[quote + 1];
                continue;
            }

            vector<string> parts;
            auto pipe = data.find('|');
            if (pipe != string::npos) {
                parts.push_back(data.substr(0, pipe));
                parts.push_back(data.substr(pipe + 1));
            }
            else {
                parts.push_back(data);
            }

            for (auto part : parts) {
                stringstream ss(part);

                i64 v1 = 0;
                i64 v2 = 0;
                i64 v3 = 0;
                ss >> v1 >> v2 >> v3;


                rules[rule].push_back({});
                rules[rule].back().push_back(v1);
                if (v2) {
                    rules[rule].back().push_back(v2);
                }
                if (v3) {
                    rules[rule].back().push_back(v3);
                }
            }
        }
        else {

            line += '#';
            i64 i = 0;
            auto m = match(line, -1, i, 0);
            if (m.size()) {
                cerr << line << endl;
                R += 1;
            }
        }
    }

    cout << R << endl;



    return 0;
}