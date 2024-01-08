#include"nfa.hpp"

typedef set<int> StateSet;

ato::Map convertNFA( ato::Map nfaWithEpsilon )
{
    set<ato::Map::iterator> visitedStates;
    stack<ato::Map::iterator> statesToVisit;
    // 获取起始状态
    auto startState = nfaWithEpsilon.begin();
    // 遍历含有空串的NFA
    statesToVisit.push( startState );
    while (!statesToVisit.empty())
    {
        auto currentState = statesToVisit.top();
        statesToVisit.pop();
        // 获取当前状态的转移
        auto nodes = nfaWithEpsilon.all();
        for (auto node = nodes.begin(); node != nodes.end();)
        {
            auto cur = *(node++);
            auto to = node.operator*().next( ato::EPSILON );
            if (to.empty()) continue;

            for (auto i = to.begin(); i != to.end();)
            {
                auto cur2 = *(i++);
                nfaWithEpsilon.mergeNode( cur2, cur );
                if (statesToVisit.top() != cur2)
                {
                    statesToVisit.push( cur2 );
                }
            }

        }

        //     map<char, StateSet> currentnfaWithEpsilon = transitions[currentState];
        //     for (auto transition : currentnfaWithEpsilon)
        //     {
        //         char input = transition.first;
        //         StateSet destinationStates = transition.second;
        //         // 添加转移到NFA
        //         nfa.nfaWithEpsilon[currentState][input] = destinationStates;
        //         // 若含有空串转移，则加入待访问的状态
        //         if (input == '\0')
        //         {
        //             for (int state : destinationStates)
        //             {
        //                 if (visitedStates.find( state ) == visitedStates.end())
        //                 {
        //                     statesToVisit.push( state );
        //                 }
        //             }
        //         }
        //     }
        // 
        // // 设置接受状态
        // for (auto state : visitedStates)
        // {
        //     if (nfaWithEpsilon[state].find( '\0' ) != transitions[state].end())
        //     {
        //         nfa.acceptStates.insert( state );
        //     }
        // }
    }

    return nfaWithEpsilon;
}