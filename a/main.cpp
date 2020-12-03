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

int main(int argc, char* argv[]) {
    i64 R = 0;
    while (!cin.eof()) {
        vector<string> q(3);
        for (i64 i = 0; i < 3; i++) {
            cin >> q[i];
        }

        auto i = q[0].find('-');
        q[0][i] = ' ';

        stringstream ss(q[0]);
        i64 l, r;
        ss >> l >> r;

        char c = q[1][0];

        string s = q[2];

        R += ((s[l - 1] == c ? 1 : 0) + (s[r - 1] == c ? 1 : 0)) % 2;
    }

    cout << R << endl;



    return 0;
}