#ifndef _NFA_TO_DFA_HPP_
#define _NFA_TO_DFA_HPP_
#include "basic_types/Map.hpp"
#include <iostream>
#include <unordered_set>
#include <set>
using namespace std;
using namespace ato;

ato::Map NtoD( ato::Map& _NFA );//NFA转化为DFA的函数

typedef struct DFAState
{
    ato::Map::iterator_set StateNtoD;//状态的集合
    ato::Map::iterator SetNode;//每种状态只有一种节点
}DFAState;//一个包含NFA状态的集合

bool Insertf(vector<DFAState>S,Map::iterator_set &I);//遍历已存入的状态，如果没有，则返回true

DFAState Move(DFAState &S,val_t edge);//Move得到的新的状态

bool Recursion(DFAState State,ato::Map &DFA);//递归函数用于构建DFA

#endif