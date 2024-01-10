#include "clear_nousage_state.hpp"

void clear_state( ato::Map& enfa )
{
    int idx = 0;

    //去不可由开始状态到达的状态
    std::map<Map::iterator, bool> isvisited;
    isvisited.clear();
    for (auto i : enfa.all())
    {
        isvisited.insert( { i,0 } );
    }
    auto start = enfa.begin();
    std::queue<Map::iterator> visitable;
    visitable.push( start );
    std::cout << "clear_state:" << std::endl;
    while (visitable.size())
    {
        auto x = visitable.front();
        isvisited[x] = 1;
        visitable.pop();
        auto tmp1 = x.next( '1' );
        auto tmp2 = x.next( '0' );
        auto to_add = tmp1;
        to_add.insert( tmp2.begin(), tmp2.end() );
        Map::iterator_set to_delete;
        for (auto x : to_add)
            if (isvisited[x]) to_delete.insert( x );
        for (auto x : to_delete)
            to_add.erase( x );
        for (auto x : to_add)
            visitable.push( x );
        std::cout << visitable.size() << std::endl;
    }
    for (auto x : enfa.all())
        if (!isvisited[x])
            enfa.eraseNode( x );
    //去不可达终结状态的状态
    /*
    for(auto x:enfa.all()){
        if(x.type()==node_t::END) continue;
        Map::iterator_set y;
        auto x1=x.next('1');
        auto x2=x.next('2');
        y.insert(x1.begin(),x1.end());
        y.insert(x2.begin(),x2.end());
        int flag=0;
        while(y.size()){
            for(auto z:y)
                if(z.type()==node_t::END){
                    flag=1;
                    break;
                }
            auto tmp1=set_next('0',y);
            auto tmp2=set_next('1',y);
            y.clear();
            y.insert(tmp1.begin(),tmp1.end());
            y.insert(tmp2.begin(),tmp2.end());
        }

    }*/


}