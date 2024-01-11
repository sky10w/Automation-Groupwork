#include"nfa.hpp"

/*typedef set<int> StateSet;

ato::Map convertNFA(map<int, map<char, StateSet>> nfaWithEpsilon) {
    ato::Map nfa;
    map<int, map<char, StateSet>> transitions = nfaWithEpsilon;
    set<int> visitedStates;
    stack<int> statesToVisit;
    // 获取起始状态
    int startState = nfaWithEpsilon.begin()->first;
    nfa.startState = startState;
    // 遍历含有空串的NFA
    statesToVisit.push(startState);
    while (!statesToVisit.empty()) {
        int currentState = statesToVisit.top();
        statesToVisit.pop();
        visitedStates.insert(currentState);
        // 获取当前状态的转移
        map<char, StateSet> currentTransitions = transitions[currentState];
        for (auto transition : currentTransitions) {
            char input = transition.first;
            StateSet destinationStates = transition.second;
            // 添加转移到NFA
            nfa.transitions[currentState][input] = destinationStates;
            // 若含有空串转移，则加入待访问的状态
            if (input == '\0') {
                for (int state : destinationStates) {
                    if (visitedStates.find(state) == visitedStates.end()) {
                        statesToVisit.push(state);
                    }
                }
            }

        }
    }
    // 设置接受状态
    for (auto state : visitedStates) {
        if (transitions[state].find('\0') != transitions[state].end()) {
            nfa.acceptStates.insert(state);
        }
    }

    return nfa;
}*/
void convertNFA( ato::Map& enfa )
{
    map<Map::iterator, Map::iterator_set> closure;
    map<Map::iterator, Map::iterator_set> closure0;
    map<Map::iterator, Map::iterator_set> closure1;
    //map<Map::iterator,Map::iterator_set> closure2;
    /*
    for(auto &x:enfa.all()){
        x.clearflag();
        closure0[x]=x.e_closure();
        cout<<closure0[x].size()<<' ';
    }*/
    // cout << endl;
    //step1 获取闭包的边
    for (auto& x : enfa.all())
    {
        closure0[x] = e_closure( set_next( '0', e_closure( x ) ) );
    }

    for (auto& x : enfa.all())
        closure1[x] = e_closure( set_next( '1', e_closure( x ) ) );
    /*
    for(auto &x:enfa.all())
        closure2[x]=x.next_closure('2');
    */
    //step2 重建边
    for (auto& x : closure0)
    {
        for (auto& y : x.second)
            enfa.insertEdge( x.first, y, '0' );
    }
    for (auto& x : closure1)
    {
        for (auto& y : x.second)
            enfa.insertEdge( x.first, y, '1' );
    }
    /*
    for(auto &x:closure2){3


        for(auto &y:x.second)
            enfa.insertEdge(x.first,y,'2');
    }*/
    //step 3 重新确认终态
    for (auto& x : enfa.all())
    {
        // x.clearflag();
        closure[x] = e_closure( x );
        for (auto& y : closure[x])
            if (y.type() == node_t::END)
                enfa.setNodeType( x, node_t::END );
    }


    //step 4 删空转移边
    for (auto& x : enfa.all())
        for (auto& y : enfa.all())
            enfa.eraseEdge( x, y, 'E' );

    //return enfa;
}