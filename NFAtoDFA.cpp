#include "NFAtoDFA.hpp"

bool Insertf( vector<DFAState>S, Map::iterator_set I )
{
    for (auto k : S)
    {
        if (k.StateNtoD == I)
        {
            return false;
        }
    }
    return true;
}

DFAState Move( DFAState S, val_t edge )
{
    DFAState result;
    for (auto k : S.StateNtoD)
    {
        auto x = k.next( edge );//遍历一个状态集内的所有状态
        for (auto i : x)
        {
            result.StateNtoD.insert( i );//将状态全部输入dfa中
        }
    }
    return result;
}

bool Recursion( DFAState State, vector<DFAState>& Set, ato::Map& DFA )
{
    //State为输入状态，Set为整个状态集的集合，DFA为要返回的DFA
    int _bool1 = 0;
    int _bool2 = 0;
    DFAState dfa1 = Move( State, '0' );
    DFAState dfa2 = Move( State, '1' );
    bool st = Insertf( Set, dfa1.StateNtoD );
    bool nd = Insertf( Set, dfa2.StateNtoD );//对不同输入求状态然后判断是否加入新状态
    if (st == true)
    {
        Set.push_back( dfa1 );
        int k = 0;//记录节点状态
        for (auto i : dfa1.StateNtoD)
        {
            if (i.type() == node_t::END)
            {
                k = 1;
            }
        }
        if (k)
        {
            dfa1.SetNode = DFA.insertNode( node_t::END );//新状态有新节点
        } else
        {
            dfa1.SetNode = DFA.insertNode( node_t::MIDDLE );
        }
        DFA.insertEdge( State.SetNode, dfa1.SetNode, '0' );
    } else if (st == false)
    {
        for (auto m : Set)
        {
            if (dfa1.StateNtoD == m.StateNtoD)
            {
                DFA.insertEdge( State.SetNode, m.SetNode, '0' );
            }
            _bool1 = 1;//出现循环构建循环边，并返回，递归完成
        }
    }
    if (nd == true)
    {
        Set.push_back( dfa2 );
        int k = 0;
        for (auto i : dfa2.StateNtoD)
        {
            if (i.type() == node_t::END)
            {
                k = 1;
            }
        }
        if (k)
        {
            dfa2.SetNode = DFA.insertNode( node_t::END );
        } else
        {
            dfa2.SetNode = DFA.insertNode( node_t::MIDDLE );
        }
        DFA.insertEdge( State.SetNode, dfa2.SetNode, '1' );
    } else if (nd == false)
    {
        for (auto m : Set)
        {
            if (dfa2.StateNtoD == m.StateNtoD)
            {
                DFA.insertEdge( State.SetNode, m.SetNode, '1' );
            }
            _bool2 = 1;
        }
    }
    if (!_bool1)
    {
        Recursion( dfa1, Set, DFA );
    }
    if (!_bool2)
    {
        Recursion( dfa2, Set, DFA );
    }//从新加入的状态及其对应节点开始递归
}

ato::Map NtoD( ato::Map& _NFA )
{
    ato::Map DFA;

    DFAState q0;
    std::vector<DFAState>StateSet;//记录状态集
    for (auto i : _NFA.all())
    {
        if (i.type() == node_t::START)
        {
            q0.StateNtoD.insert( i );//将初始状态存入初始状态集中
            q0.SetNode = i;//定位首节点
        }
    }

    Recursion( q0, StateSet, DFA );

    return DFA;
}
