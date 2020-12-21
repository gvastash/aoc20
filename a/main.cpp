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

set<string> Intersect(set<string>& a, set<string>& b) {
    set<string> res;

    for (auto e : a) {
        if (!b.count(e)) {
            continue;
        }
        res.insert(e);
    }

    return res;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }


    map<set<string>, set<string>> q;

    i64 tile = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            break;
        }

        line.pop_back();
        auto i = line.find('(');

        stringstream nss(line.substr(0, i - 1));
        stringstream gss(line.substr(i + 1));

        set<string> names;
        while (!nss.eof()) {
            string name;
            nss >> name;
            names.insert(name);
        }

        set<string> gens;
        while (!gss.eof()) {
            string gen;
            gss >> gen;
            if (gen == "contains") {
                continue;
            }
            if (gen.back() == ',') {
                gen.pop_back();
            }
            gens.insert(gen);
        }

        q[names] = gens;
    }

    map<string, i64> allNames;
    set<string> allGens;
    for (auto& e : q) {
        for (auto& name : e.first) {
            allNames[name] += 1;
        }
        for (auto& gen : e.second) {
            allGens.insert(gen);
        }
    }

    cerr << allNames.size() << endl;
    cerr << allGens.size() << endl;

    map<string, string> tags;

    //i64 T = 100;
    //for (i64 tt = 1; tt <= T; tt++) {
    while (tags.size() < allGens.size()) {
        map<string, vector<set<string>>> z;
        for (auto& e : q) {
            for (auto gen : e.second) {
                z[gen].push_back(e.first);
            }
        }


        for (auto& e : z) {
            while (e.second.size() != 1) {
                auto r = Intersect(e.second.back(), e.second[e.second.size() - 2]);
                e.second.pop_back();
                e.second.pop_back();
                e.second.push_back(r);
            }

            if (e.second.front().size() == 1) {
                auto name = *e.second.front().begin();
                if (tags.count(name) && tags[name] != e.first) {
                    throw 1;
                }
                tags[name] = e.first;
            }
        }

        map<set<string>, set<string>> nq;

        for (auto& e : q) {
            auto keys = e.first;
            auto vals = e.second;

            for (auto t : tags) {
                if (!keys.count(t.first)) {
                    continue;
                }
                keys.erase(t.first);
                if (t.second.empty()) {
                    continue;
                }
                vals.erase(t.second);
            }

            nq[keys] = vals;

            /*

            if (!vals.empty()) {
                continue;
            }

            for (auto& name : keys) {
                if (tags.count(name) && tags[name] != "") {
                    throw 1;
                }
                tags[name] = "";
            }

            */
        }

        q = nq;
    }

    /*
    i64 R = 0;
    for (auto& e : allNames) {
        if (tags.count(e.first)) {
            continue;
        }
        R += e.second;
    }
    cout << R << endl;
    */

    vector<pair<string, string>> w;
    for (auto& e : tags) {
        w.push_back({ e.second, e.first });
    }
    sort(w.begin(), w.end());

    stringstream ss;
    for (i64 i = 0; i < w.size(); i++) {
        if (i > 0) {
            ss << ",";
        }
        ss << w[i].second;
    }

    cout << ss.str() << endl;

    return 0;
}