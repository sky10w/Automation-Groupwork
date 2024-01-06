#ifndef __3NFA_TO_NFA_HPP__
#define __3NFA_TO_NFA_HPP__

#include "basic_types/Map.hpp"
#include <iostream>
#include <stack>
#include <list>

using namespace std;
using namespace ato;

NFA convertNFA(map<int, map<char, StateSet>> nfaWithEpsilon);



#endif