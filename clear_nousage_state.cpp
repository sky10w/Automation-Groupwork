#include "clear_nousage_state.hpp"

void clear_state(ato::Map& enfa){
    int idx=0;
    while(idx){
        idx=0;
        for(auto x:enfa.all()){
            if(!x.next('0').size()&&!x.next('1').size()&&!x.next('E').size()&&x.type()!=node_t::END)
                enfa.eraseNode(x),idx++;
            else if(!x.revNext('0').size()&&!x.revNext('1').size()&&!x.revNext('E').size()&&x.type()!=node_t::START)
                enfa.eraseNode(x),idx++;
        }
    }
}