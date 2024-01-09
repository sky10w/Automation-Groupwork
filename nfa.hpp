#ifndef __3NFA_TO_NFA_HPP__
#define __3NFA_TO_NFA_HPP__

#include "basic_types/Map.hpp"
#include "util.hpp"
#include <iostream>
#include<algorithm>
#include <stack>
#include <list>
#include <set>

using namespace std;
using namespace ato;

//NFA convertNFA(map<int, map<char, StateSet>> nfaWithEpsilon);
//ato::Map::iterator next_eclosure(ato::Map& );
void convertNFA( ato::Map& enfa );


#endif