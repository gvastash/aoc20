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

i64 Calculate(string a) {
    stack<char> q;
    stringstream ss;
    for (auto c : a) {
        if (c == ' ') {
            continue;
        }
        if ('0' <= c && c <= '9') {
            ss << c;
            continue;
        }
        if (c == ')') {
            while (true) {
                char t = q.top();
                q.pop();
                if (t == '(') {
                    break;
                }
                ss << t;
            }
            continue;
        }
        if (c != '(') {
            while (!q.empty() && q.top() != '(' && (c == q.top() || (c == '*' && q.top() == '+'))) {
                ss << q.top();
                q.pop();
            }
        }
        q.push(c);
    }
    while (!q.empty()) {
        ss << q.top();
        q.pop();
    }

    string b = ss.str();
    stack<i64> v;
    for (auto c : b) {
        if ('0' <= c && c <= '9') {
            v.push((i64)c - '0');
            continue;
        }
        i64 v2 = v.top();
        v.pop();
        i64 v1 = v.top();
        v.pop();
        if (c == '+') {
            v.push(v1 + v2);
        }
        else if (c == '*') {
            v.push(v1 * v2);
        }
        else {
            throw 1;
        }
    }

    if (v.size() != 1) {
        throw 1;
    }

    return v.top();
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    vector<string> a;
    while (!cin.eof()) {
        string line;
        getline(cin, line);
        if (line.empty()) {
            break;
        }
        a.push_back(line);
    }

    i64 R = 0;
    for (auto& e : a) {
        R += Calculate(e);
    }
    cout << R << endl;


    return 0;
}