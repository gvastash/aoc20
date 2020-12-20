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

map<string, vector<pair<i64, i64>>> q;
map<i64, vector<string>> tiles;

void add(string s, i64 tile, i64 flag) {
    q[s].push_back({ tile, flag });
    reverse(s.begin(), s.end());
    q[s].push_back({ tile, flag });
}

string Get(i64 tile, i64 flag) {
    if (flag == 0) {
        return tiles[tile].front();
    }
    else if (flag == 1) {
        stringstream bss;
        for (i64 i = 0; i < tiles[tile].size(); i++) {
            bss << tiles[tile][i].back();
        }
        return bss.str();
    }
    else if (flag == 2) {
        return tiles[tile].back();
    }
    else if (flag == 3) {
        stringstream fss;
        for (i64 i = 0; i < tiles[tile].size(); i++) {
            fss << tiles[tile][i].front();
        }
        return fss.str();
    }
    else {
        throw 1;
    }
}

void Rotate(i64 tile) {
    vector<string> res;
    for (i64 i = 0; i < tiles[tile].front().size(); i++) {
        stringstream ss;
        for (i64 j = 0; j < tiles[tile].size(); j++) {
            ss << tiles[tile][j][i];
        }
        res.push_back(ss.str());
        reverse(res.back().begin(), res.back().end());
    }
    tiles[tile] = res;
}

void FlipRows(i64 tile) {
    i64 i = 0;
    i64 j = tiles[tile].size() - 1;

    while (i < j) {
        swap(tiles[tile][i++], tiles[tile][j--]);
    }
}

void FlipCols(i64 tile) {
    for (i64 k = 0; k < tiles[tile].size(); k++) {
        i64 i = 0;
        i64 j = tiles[tile].size() - 1;
        while (i < j) {
            swap(tiles[tile][k][i++], tiles[tile][k][j--]);
        }
    }
}

i64 CountPattern(i64 tile) {
    vector<string> pattern = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };

    i64 R = 0;
    /*
    for (i64 i = 0; i <= tiles[tile].size() - pattern.size(); i++) {
        for (i64 j = 0; j <= tiles[tile][i].size() - pattern.front().size(); j++) {
        }
    }
    */
    for (i64 i = 0; i < tiles[tile].size(); i++) {
        for (i64 j = 0; j < tiles[tile][i].size(); j++) {
            i64 cnt = 0;
            for (i64 x = 0; x < pattern.size(); x++) {
                if (i + x >= tiles[tile].size()) {
                    break;
                }
                for (i64 y = 0; y < pattern[x].size(); y++) {
                    if (j + y >= tiles[tile][i].size()) {
                        break;
                    }
                    cnt += 1;
                    if (pattern[x][y] != '#') {
                        continue;
                    }
                    if (tiles[tile][i + x][j + y] != '#' && tiles[tile][i + x][j + y] != 'O') {
                        cnt -= 1;
                    }
                }
            }

            if (cnt == pattern.size() * pattern.front().size()) {
                for (i64 x = 0; x < pattern.size(); x++) {
                    for (i64 y = 0; y < pattern[x].size(); y++) {
                        if (pattern[x][y] != '#') {
                            continue;
                        }

                        tiles[tile][i + x][j + y] = 'O';
                    }
                }
                R += 1;
            }
        }
    }

    if (R > 0) {
        cerr << R << endl;
        for (auto e : tiles[tile]) {
            cerr << e << endl;
        }

        R = 0;
        for (auto e : tiles[tile]) {
            for (auto c : e) {
                if (c == '#') {
                    R += 1;
                }
            }
        }

        cout << R << endl;
        exit(0);
    }

    return R;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(15); cout.setf(ios::fixed); cerr.precision(15); cerr.setf(ios::fixed);

    if (sizeof(i64) != sizeof(long long int)) {
        cerr << "i64 != long long int" << endl;
    }

    i64 tile = 0;
    while (!cin.eof()) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            if (tile) {
                tile = 0;
                continue;
            }
            break;
        }

        if (!tile) {
            stringstream ss(line.substr(line.find(' ')));
            ss >> tile;
            continue;
        }

        tiles[tile].push_back(line);
    }

    for (auto& e : tiles) {
        add(e.second.front(), e.first, 0);
        add(e.second.back(), e.first, 2);

        {
            stringstream fss;
            stringstream bss;
            for (i64 i = 0; i < e.second.size(); i++) {
                fss << e.second[i].front();
                bss << e.second[i].back();
            }
            add(fss.str(), e.first, 3);
            add(bss.str(), e.first, 1);
        }
    }

    map<i64, set<i64>> z;

    for (auto& e : q) {
        if (e.second.size() == 2) {
            for (auto t : e.second) {
                z[t.first].insert(t.second);
            }
            continue;
        }
        if (e.second.size() == 1) {
            continue;
        }
        cerr << "sameCnt = " << e.second.size() << endl;
    }

    i64 R = 1;
    i64 cnt = 0;
    for (auto t : z) {
        if (t.second.size() != 2) {
            continue;
        }
        cnt += 1;
        R *= t.first;
    }
    cerr << cnt << endl;
    cout << R << endl;

    vector<vector<i64>> puzzle;
    puzzle.push_back(vector<i64>());

    for (auto t : z) {
        if (t.second.size() == 2 && t.second.count(1) && t.second.count(2)) {
            puzzle.back().push_back(t.first);
        }
    }

    if (puzzle.back().size() != 1) {
        throw 1;
    }

    //cerr << puzzle.back().back() << " ";
    
    if (false) {
        i64 tile = puzzle.back().back();
        auto origTile = tiles[tile];
        do {
            for (auto e : tiles[tile]) {
                cerr << e << endl;
            }
            cerr << endl;
            Rotate(tile);
        } while (origTile != tiles[tile]);

        do {
            for (auto e : tiles[tile]) {
                cerr << e << endl;
            }
            cerr << endl;
            FlipRows(tile);
        } while (origTile != tiles[tile]);

        do {
            for (auto e : tiles[tile]) {
                cerr << e << endl;
            }
            cerr << endl;
            FlipCols(tile);
        } while (origTile != tiles[tile]);
    }

    set<i64> v;
    while (true) {
        i64 tile = puzzle.back().back();
        v.insert(tile);

        auto right = Get(tile, 1);

        i64 nextTile = -1;
        for (auto e : q[right]) {
            if (e.first == tile) {
                continue;
            }
            if (v.count(e.first)) {
                continue;
            }
            if (nextTile != -1) {
                throw 1;
            }
            nextTile = e.first;
        }

        if (nextTile == -1) {
            i64 tile = puzzle.back().front();
            auto down = Get(tile, 2);

            for (auto e : q[down]) {
                if (e.first == tile) {
                    continue;
                }
                if (v.count(e.first)) {
                    continue;
                }
                if (nextTile != -1) {
                    throw 1;
                }
                nextTile = e.first;
            }

            if (nextTile == -1) {
                break;
            }

            if (true) {
                auto origTile = tiles[nextTile];
                if (down != Get(nextTile, 0)) {
                    do {
                        if (down != Get(nextTile, 0)) {
                            auto origTile = tiles[nextTile];

                            do {
                                FlipRows(nextTile);
                                if (down == Get(nextTile, 0)) {
                                    break;
                                }
                            } while (origTile != tiles[nextTile]);

                            if (down == Get(nextTile, 0)) {
                                break;
                            }
                        }

                        if (down != Get(nextTile, 0)) {
                            auto origTile = tiles[nextTile];

                            do {
                                FlipCols(nextTile);
                                if (down == Get(nextTile, 0)) {
                                    break;
                                }
                            } while (origTile != tiles[nextTile]);

                            if (down == Get(nextTile, 0)) {
                                break;
                            }
                        }

                        Rotate(nextTile);
                        if (down == Get(nextTile, 0)) {
                            break;
                        }
                    } while (origTile != tiles[nextTile]);
                }

                auto top = Get(nextTile, 0);
                if (down != top) {
                    throw 1;
                }
            }
            else {
                break;
            }

            //cerr << endl;
            //cerr << nextTile << " ";
            puzzle.push_back({});
            puzzle.back().push_back(nextTile);


            continue;
        }

        if (true) {
            auto origTile = tiles[nextTile];
            if (right != Get(nextTile, 3)) {
                do {
                    if (right != Get(nextTile, 3)) {
                        auto origTile = tiles[nextTile];

                        do {
                            FlipRows(nextTile);
                            if (right == Get(nextTile, 3)) {
                                break;
                            }
                        } while (origTile != tiles[nextTile]);

                        if (right == Get(nextTile, 3)) {
                            break;
                        }
                    }

                    if (right != Get(nextTile, 3)) {
                        auto origTile = tiles[nextTile];

                        do {
                            FlipCols(nextTile);
                            if (right == Get(nextTile, 3)) {
                                break;
                            }
                        } while (origTile != tiles[nextTile]);

                        if (right == Get(nextTile, 3)) {
                            break;
                        }
                    }

                    Rotate(nextTile);
                    if (right == Get(nextTile, 3)) {
                        break;
                    }


                } while (origTile != tiles[nextTile]);
            }

            auto left = Get(nextTile, 3);
            if (right != left) {
                throw 1;
            }
        }


        puzzle.back().push_back(nextTile);
        //cerr << nextTile << " ";
    }

    for (i64 i = 0; i < puzzle.size(); i++) {
        for (i64 j = 0; j < puzzle[i].size(); j++) {
            cerr << puzzle[i][j] << " ";
        }
        cerr << endl;
    }

    vector<string> image;
    for (i64 i = 0; i < puzzle.size(); i++) {
        for (i64 row = 1; row < tiles[puzzle[i].front()].size() - 1; row++) {
            stringstream ss;

            for (i64 j = 0; j < puzzle[i].size(); j++) {
                for (i64 col = 1; col < tiles[puzzle[i][j]][row].size() - 1; col++) {
                    ss << tiles[puzzle[i][j]][row][col];
                }
            }

            image.push_back(ss.str());
        }
    }

    auto vmin = tiles.begin()->first - 1;
    tiles[vmin] = image;

    if (true) {
        i64 tile = vmin;

        auto origTile = tiles[tile];
        do {
            if (true) {
                auto origTile = tiles[tile];

                do {
                    i64 R = CountPattern(vmin);
                    cout << R << endl;

                    FlipRows(tile);
                } while (origTile != tiles[tile]);
            }

            if (true) {
                auto origTile = tiles[tile];

                do {
                    i64 R = CountPattern(vmin);
                    cout << R << endl;

                    FlipCols(tile);
                } while (origTile != tiles[tile]);
            }

            i64 R = CountPattern(vmin);
            cout << R << endl;

            Rotate(tile);
        } while (origTile != tiles[tile]);
    }

    return 0;
}