#include"nfa.hpp"

typedef set<int> StateSet;

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
}