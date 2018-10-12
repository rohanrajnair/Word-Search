//
//  puzzle.hpp
//  HW07
//
//  Created by Rohan Nair on 5/29/17.
//  Copyright © 2017 Rohan Nair. All rights reserved.
//

#ifndef puzzle_hpp
#define puzzle_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

class puzzle{
public:
    unordered_set<string> _words;
    puzzle(string dict, string puzzle);
    map<string,pair<pair<int,int>,pair<int,int>>> search_E (int r, int c);
    map<string,pair<pair<int,int>,pair<int,int>>>search_W (int r, int c);
    map<string,pair<pair<int,int>,pair<int,int>>> search_N (int r, int c);
    map<string,pair<pair<int,int>,pair<int,int>>> search_S (int r, int c);;
    map<string,pair<pair<int,int>,pair<int,int>>> search_NE (int r, int c);
    map<string,pair<pair<int,int>,pair<int,int>>> search_SE (int r, int c);
    map<string,pair<pair<int,int>,pair<int,int>>> search_NW (int r, int c);
    map<string,pair<pair<int,int>,pair<int,int>>> search_SW (int r, int c);
    map<string,pair<pair<int,int>,pair<int,int>>> search_all(int r, int c);
    void print_grid();
    int getrows();
    int getcolumns();
    void solve();
private:
    static const int MAX = 300;
    char grid[MAX][MAX];
    int _numrows;
    int _numcolumns;
    string _puzzle;
    string _dict;
};


#endif /* puzzle_hpp */
