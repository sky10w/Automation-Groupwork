#include"DFA-minimization.hpp"
#include"basic_types/Map.hpp"
int main(){
    std::cout<<"hello world!"<<std::endl;
    Map test;
    auto q0 = test.insertNode(node_t::MIDDLE);
    auto q1 = test.insertNode(node_t::MIDDLE);
    auto q2 = test.insertNode(node_t::MIDDLE);
    auto q3 = test.insertNode(node_t::MIDDLE);
    auto q4 = test.insertNode(node_t::END);
    auto q5 = test.insertNode(node_t::MIDDLE);
    auto q6 = test.insertNode(node_t::MIDDLE);
    auto q7 = test.insertNode(node_t::MIDDLE);
    auto q8 = test.insertNode(node_t::END);
    auto q9 = test.insertNode(node_t::MIDDLE);
    test.insertEdge(q0,q1,'0');
    test.insertEdge(q0,q5,'1');
    test.insertEdge(q1,q5,'0');
    test.insertEdge(q1,q2,'1');
    test.insertEdge(q2,q6,'1');
    test.insertEdge(q2,q3,'0');
    test.insertEdge(q3,q2,'0');
    test.insertEdge(q3,q4,'1');
    test.insertEdge(q4,q8,'0');
    test.insertEdge(q4,q1,'1');
    test.insertEdge(q5,q6,'1');
    test.insertEdge(q5,q1,'0');
    test.insertEdge(q6,q2,'1');
    test.insertEdge(q6,q7,'0');
    test.insertEdge(q7,q8,'1');
    test.insertEdge(q7,q6,'0');
    test.insertEdge(q8,q4,'1');
    test.insertEdge(q8,q5,'0');
    test.insertEdge(q9,q5,'1');
    test.insertEdge(q9,q7,'0');
    minimize(test);
    //test.mergeNode(q0,q1);
    //std::cout<<test.all().size()<<std::endl;
    //std::cout<<66666<<std::endl;
    
    
    
    
    
    
    return 0;
}