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

using TPassport = map<string, vector<string>>;

i64 calcDigits(i64 v) {
    i64 res = 0;
    while (v) {
        res += 1;
        v /= 10;
    }
    return res;
}

bool validateInt(string val, i64 l, i64 r) {
    i64 limit = calcDigits(l);
    if (calcDigits(r) != limit) {
        throw 1;
    }

    if (val.size() != limit) {
        return false;
    }
    
    for (auto c : val) {
        if ('0' <= c && c <= '9') {
            continue;
        }
        return false;
    }

    stringstream ss(val);
    i64 v;
    ss >> v;

    return l <= v && v <= r;
}

bool validaiteHeight(string val) {
    if (val.size() < 3) {
        return false;
    }

    string num = val.substr(0, val.size() - 2);
    string type = val.substr(val.size() - 2);
    if (type == "cm") {
        return validateInt(num, 150, 193);
    }
    if (type == "in") {
        return validateInt(num, 59, 76);
    }
    return false;
}

bool validateHairColor(string val) {
    if (val.size() != 7) {
        return false;
    }
    if (val[0] != '#') {
        return false;
    }

    for (i64 i = 1; i < 7; i++) {
        if ('0' <= val[i] && val[i] <= '9') {
            continue;
        }
        if ('a' <= val[i] && val[i] <= 'f') {
            continue;
        }
        return false;
    }
    return true;
}

bool validateEyeColor(string val) {
    set<string> available = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
    return available.count(val);
}

bool validatePassportId(string val) {
    if (val.size() != 9) {
        return false;
    }
    for (auto c : val) {
        if ('0' <= c && c <= '9') {
            continue;
        }
        return false;
    }
    return true;
}

bool isValid(const TPassport& data) {
    vector<string> required = {
        "byr",
        "iyr",
        "eyr",
        "hgt",
        "hcl",
        "ecl",
        "pid",
        // "cid",
    };

    for (auto key : required) {
        if (!data.count(key)) {
            return false;
        }
    }

    bool res = true;

    res &= validateInt(data.at("byr").front(), 1920, 2002);
    res &= validateInt(data.at("iyr").front(), 2010, 2020);
    res &= validateInt(data.at("eyr").front(), 2020, 2030);
    res &= validaiteHeight(data.at("hgt").front());
    res &= validateHairColor(data.at("hcl").front());
    res &= validateEyeColor(data.at("ecl").front());
    res &= validatePassportId(data.at("pid").front());

    return res;
}

int main(int argc, char* argv[]) {
    vector<TPassport> a;
    a.push_back(TPassport());

    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            a.push_back(TPassport());
            continue;
        }

        stringstream ss(line);
        while (!ss.eof()) {
            string data;
            ss >> data;
            auto i = data.find(':');
            string key = data.substr(0, i);
            string val = data.substr(i + 1);

            a.back()[key].push_back(val);
        }
    }

    i64 R = 0;
    for (auto& data : a) {
        R += isValid(data) ? 1 : 0;
    }

    cout << R << endl;


    return 0;
}