#include "NFAtoDFA.hpp"

bool Insertf( vector<DFAState>S, Map::iterator_set& I )
{
    if (!I.size()) return false;
    for (auto k : S)
    {
        if (k.StateNtoD == I)
        {
            return false;
        }
    }
    return true;
}

DFAState Move( DFAState& S, val_t edge )
{
    //std::cout<<S.StateNtoD.size()<<endl;
    DFAState result;
    for (auto& k : S.StateNtoD)
    {
        auto x = k.next( edge );//遍历一个状态集内的所有状态

        for (auto& i : x)
        {
            result.StateNtoD.insert( i );//将状态全部输入dfa中
        }
    }
    //cout<<result.StateNtoD.size()<<endl;
    return result;
}
vector<DFAState>Set;
ato::Map::iterator trapState;
bool trapTriggered;
void Recursion( DFAState State, ato::Map& DFA )
{
    // cout << DFA.all().size() << endl;
    //State为输入状态，Set为整个状态集的集合，DFA为要返回的DFA
    //int _bool1 = 0;
    //int _bool2 = 0;
    DFAState dfa1 = Move( State, '0' );
    DFAState dfa2 = Move( State, '1' );
    int a1 = dfa1.StateNtoD.size(), a2 = dfa2.StateNtoD.size();
    bool st1 = Insertf( Set, dfa1.StateNtoD );

    if (st1 == true)
    {

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
        Set.push_back( dfa1 );
        DFA.insertEdge( State.SetNode, dfa1.SetNode, '0' );
        Recursion( dfa1, DFA );
    } else if (st1 == false)
    {
        bool checkIf = false;
        for (auto m : Set)
        {
            if (dfa1.StateNtoD == m.StateNtoD)
            {
                dfa1 = m;
                DFA.insertEdge( State.SetNode, dfa1.SetNode, '0' );
                checkIf = true;
            }
            //_bool1 = 1;//出现循环构建循环边，并返回，递归完成
        }
        if (!checkIf)
        {
            DFA.insertEdge( State.SetNode, trapState, '0' );
            trapTriggered = true;
            std::cerr << "Trap triggered" << '\n';
        }
    }
    bool nd1 = Insertf( Set, dfa2.StateNtoD );//对不同输入求状态然后判断是否加入新状态
    if (nd1 == true)
    {

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
        Set.push_back( dfa2 );
        DFA.insertEdge( State.SetNode, dfa2.SetNode, '1' );
        Recursion( dfa2, DFA );
    } else if (nd1 == false)
    {
        bool checkIf = false;
        for (auto m : Set)
        {
            if (dfa2.StateNtoD == m.StateNtoD)
            {
                dfa2 = m;
                DFA.insertEdge( State.SetNode, dfa2.SetNode, '1' );
                checkIf = true;
            }
            //_bool2 = 1;
        }
        if (!checkIf)
        {
            DFA.insertEdge( State.SetNode, trapState, '1' );
            trapTriggered = true;
            std::cerr << "Trap triggered" << '\n';
        }
    }
    //从新加入的状态及其对应节点开始递归
}


ato::Map NtoD( ato::Map& _NFA )
{
    ato::Map DFA;
    trapState = DFA.insertNode( ato::node_t::MIDDLE );
    DFA.insertEdge( trapState, trapState, '0' );
    DFA.insertEdge( trapState, trapState, '1' );
    trapTriggered = false;


    DFAState q0;

    //std::vector<DFAState>StateSet;//记录状态集
    for (auto& i : _NFA.all())
    {
        if (i.type() == node_t::START)
        {

            q0.StateNtoD.insert( i );//将初始状态存入初始状态集中

            q0.SetNode = DFA.insertNode( node_t::START );
            if (i.type() == node_t::END)
                DFA.setNodeType( q0.SetNode, node_t::END );//定位首节点
        }
    }
    Set.push_back( q0 );
    //cout<<DFA.all().size()<<endl;

    Recursion( q0, DFA );
    _NFA.clear();

    if (!trapTriggered)
    {
        DFA.eraseNode( trapState );
    }
    return DFA;
}


