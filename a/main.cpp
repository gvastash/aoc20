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

struct TOp {
    string Cmd;
    i64 Val;
};

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    vector<TOp> ops;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        TOp op;
        ss >> op.Cmd >> op.Val;

        ops.push_back(op);
    }

    for (i64 i = 0; i < ops.size(); i++) {
        cerr << i << ": " << ops[i].Cmd << " " << ops[i].Val << endl;
    }

    for (i64 i = 0; i < ops.size(); i++) {
        if (ops[i].Cmd == "nop") {
            ops[i].Cmd = "jmp";
        }
        else if (ops[i].Cmd == "jmp") {
            ops[i].Cmd = "nop";
        }
        else {
            continue;
        }
        i64 acc = 0;
        i64 eip = 0;
        vector<bool> visited(ops.size());
        while (0 <= eip && eip < ops.size()) {
            if (visited[eip]) {
                break;
            }
            visited[eip] = 1;
            auto& cop = ops[eip];
            if (cop.Cmd == "nop") {
                eip += 1;
                continue;
            }
            if (cop.Cmd == "jmp") {
                eip += cop.Val;
                continue;
            }
            if (cop.Cmd == "acc") {
                acc += cop.Val;
                eip += 1;
                continue;
            }
            cerr << cop.Cmd << endl;
            throw 1;
        }
        if (ops[i].Cmd == "nop") {
            ops[i].Cmd = "jmp";
        }
        else if (ops[i].Cmd == "jmp") {
            ops[i].Cmd = "nop";
        }
        if (eip != ops.size()) {
            continue;
        }
        cout << acc << endl;
    }

    return 0;
}