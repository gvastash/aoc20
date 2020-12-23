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

void Play(vector<vector<i64>>& q, vector<i64>& k) {
    while (k[0] < q[0].size() && k[1] < q[1].size()) {
        vector<i64> v = { q[0][k[0]], q[1][k[1]] };
        if (k[0] + v[0] < q[0].size() && k[1] + v[1] < q[1].size()) {
            vector<vector<i64>> nq(2);
            vector<i64> nk(2);

            for (i64 j = 0; j < 2; j++) {
                for (i64 i = k[j]; i < q[j].size(); i++) {
                    nq[j].push_back(q[j][k[j]]);
                }
            }

            Play(nq, nk);

            if (nk[0] < nq[0].size()) {
                q[0].push_back(q[0][k[0]]);
                q[0].push_back(q[1][k[1]]);
            }
            else {
                q[1].push_back(q[1][k[1]]);
                q[1].push_back(q[0][k[0]]);
            }
        }
        else {
            if (q[0][k[0]] > q[1][k[1]]) {
                q[0].push_back(q[0][k[0]]);
                q[0].push_back(q[1][k[1]]);
            }
            else {
                q[1].push_back(q[1][k[1]]);
                q[1].push_back(q[0][k[0]]);
            }
        }

        k[0] += 1;
        k[1] += 1;
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }


    vector<vector<i64>> q(2);

    i64 cnt = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            cnt += 1;
            if (cnt > 1) {
                break;
            }
            continue;
        }

        if (line.find("Player") != string::npos) {
            continue;
        }
        stringstream ss(line);
        i64 v = 0;
        ss >> v;
        q[cnt].push_back(v);
    }

    vector<i64> k(2);



    i64 R = 0;
    for (i64 j = 0; j < 2; j++) {
        for (i64 i = k[j]; i < q[j].size(); i++) {
            R += q[j][i] * (q[j].size() - i);
        }
    }

    cout << R << endl;

    return 0;
}