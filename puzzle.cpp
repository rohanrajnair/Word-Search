//
//  puzzle.cpp
//  HW07
//
//  Created by Rohan Nair on 5/29/17.
//  Copyright © 2017 Rohan Nair. All rights reserved.
//

#include "puzzle.hpp"
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

puzzle::puzzle(string dict, string puzzle){
    _dict = dict;
    _puzzle = puzzle;
    ifstream dictfile;
    ifstream puzzlefile;
    dictfile.open(_dict);
    puzzlefile.open(puzzle);
    if (dictfile.fail()){
        cout << "failed to open dictionary" << endl;
        exit(1);
    }
    
    string s;
    
    while (dictfile >> s){
        _words.insert(s);
    }
    
    
    if (puzzlefile.fail()){
        cout << "failed to open puzzle" << endl;
        exit(1);
    }
    string t;
    int current_row = 0;
    int current_column = 0;
    while (getline(puzzlefile, t)){
        current_column = 0;
        for (int i = 0; i < t.length(); ++i){
            if (t[i] != ' '){
                grid[current_row][current_column] = t[i];
                ++ current_column;
            }
        }
        _numcolumns = current_column;
        ++ current_row;
    }
    _numrows = current_row;
}


void puzzle::print_grid(){
    for (int i = 0; i < _numrows; ++i){
        for (int j = 0; j < _numcolumns; ++j){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int puzzle::getrows(){
    return _numrows;
}

int puzzle::getcolumns(){
    return _numcolumns; 
}


map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_E(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> words;
    string temp;
    for (int i = c; i < _numcolumns; ++i){
        temp += grid[r][i];
    }
    for (int i = 6; i <= temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r, c+i-1))));
        }
    }
    return words;
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_W(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>>words;
    string temp;
    for (int i = c; i >= 0; --i){
        temp += grid[r][i];
    }
    for (int i = 6; i <= temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r, c-i+1))));
        }
    }
    return words; 
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_S(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> words;
    string temp;
    for (int i = r; i < _numrows; ++i){
        temp += grid[i][c];
    }
    for (int i = 6; i <=temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r+i-1, c))));
        }
    }
    return words; 
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_N(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> words;
    string temp;
    for (int i = r; i >= 0; --i){
        temp += grid[i][c];
    }
    for (int i = 6; i <= temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r-i+1, c))));
        }
    }
    return words; 
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_SE(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> words;
    string temp;
    for (int i = r, j = c; i < _numrows && j < _numcolumns; ++i, ++j){
        temp += grid[i][j];
    }
    for (int i = 6; i <= temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r+i-1, c+i-1))));
        }
    }
    return words; 
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_SW(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> words;
    string temp;
    for (int i = r, j = c; i < _numrows && j >= 0; ++i, --j){
        temp += grid[i][j];
    }
    for (int i = 6; i <= temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r+i-1, c-i+1))));
        }
    }
    return words;
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_NE(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> words;
    string temp;
    for (int i = r, j = c; i >= 0 && j < _numcolumns; --i, ++j){
        temp += grid[i][j];
    }
    for (int i = 6; i <= temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r-i+1, c+i-1))));
        }
    }
    return words;
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_NW(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> words;
    string temp;
    for (int i = r, j = c; i >= 0 && j >= 0; --i, --j){
        temp += grid[i][j];
    }
    for (int i = 6; i <= temp.length(); ++i){
        auto search = _words.find(temp.substr(0,i));
        if (search != _words.end()){
            words.insert(make_pair(temp.substr(0,i), make_pair(make_pair(r,c),make_pair(r-i+1, c-i+1))));
        }
    }
    return words;
}

map<string,pair<pair<int,int>,pair<int,int>>> puzzle::search_all(int r, int c){
    map<string,pair<pair<int,int>,pair<int,int>>> n = search_N(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> s = search_S(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> e = search_E(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> w = search_W(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> ne = search_NE(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> nw = search_NW(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> se = search_SE(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> sw = search_SW(r, c);
    map<string,pair<pair<int,int>,pair<int,int>>> all;
    all.insert(n.begin(), n.end());
    all.insert(s.begin(), s.end());
    all.insert(e.begin(), e.end());
    all.insert(w.begin(), w.end());
    all.insert(ne.begin(), ne.end());
    all.insert(nw.begin(), nw.end());
    all.insert(se.begin(), se.end());
    all.insert(sw.begin(), sw.end());
    return all;
}

void puzzle::solve(){
    map<string,pair<pair<int,int>,pair<int,int>>> m;
    for (int i = 0; i < _numrows; ++i){
        for (int j = 0; j < _numcolumns; ++j){
            map<string,pair<pair<int,int>,pair<int,int>>> n = search_all(i, j);
            m.insert(n.begin(),n.end());
   
        }

    }
    for(auto elem : m){
        cout << elem.first << " from (" << elem.second.first.first << "," << elem.second.first.second << ") to (" << elem.second.second.first << "," << elem.second.second.second << ")" << endl;
    }
}





