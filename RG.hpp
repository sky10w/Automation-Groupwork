#include<iostream>
#include<vector>
#include"basic_types/Map.hpp"

using namespace std;
using namespace ato;


class RG
{

private:
    map<Map::iterator, char> V;
    vector<char> T;
    vector<string> P;

public:
    void DFAtoRG( Map DFA );
    void printRG();
};