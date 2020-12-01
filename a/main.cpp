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
    vector<i64> a;

    while (!cin.eof()) {
        i64 t;
        cin >> t;
        a.push_back(t);
    }

    for (i64 i = 0; i < a.size(); i++) {
        for (i64 j = i + 1; j < a.size(); j++) {
            for (i64 k = j + 1; k < a.size(); k++) {
                if (a[i] + a[j] + a[k] == 2020) {
                    cout << a[i] * a[j] * a[k] << endl;
                }
            }
        }
    }


    return 0;
}