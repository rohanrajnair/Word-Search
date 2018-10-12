#include <iostream>
#include "puzzle.hpp"
#include <algorithm>
#include <map>
using namespace std;



int main(){
    string dictfile, puzzlefile;
    cout << "enter a dictionary file name (full path): " << endl;
    cin >> dictfile;
    cout << "enter a puzzle file name (full path): " << endl;
    cin >> puzzlefile;
    puzzle p (dictfile,puzzlefile);
    p.solve();
}
