#if !defined(__NODE_HPP__)
#define __NODE_HPP__

/**
 * This file is complete
*/



#include "macros.hpp"
#include "Edge.hpp"
#include <iostream>
#include <map>
#include <set>
#include <memory>

BASIC_NAMESPACE_BEGIN


struct Node;

template struct Edge<struct Node>;
template struct RevEdge<struct Node>;

using Node_set = std::set<struct Node*>;

using Edge_t = struct Edge<Node>;
using RevEdge_t = struct RevEdge<Node>;

using Edge_set = std::set<Edge_t*>;
using RevEdge_set = std::set<RevEdge_t*>;

struct Node
{
    id_t id;
    node_t type;
    std::map<val_t, Edge_set> edge;
    std::map<val_t, RevEdge_set> revEdge;

    Edge_set next( val_t __val );
    RevEdge_set revNext( val_t __val );
    void insertEdge( Node* __to, val_t __val );
    void insertRevEdge( Node* __to, val_t __val );
    void eraseEdge( Node* __to, val_t __val );
    void eraseRevEdge( Node* __to, val_t __val );
    void clear();
    const Node& operator=( const Node& __rhs );
    Node( id_t __id, node_t __type );
    virtual ~Node();
private:
    void _insertEdge( Edge_t* __ori, val_t __val );
    void _insertRevEdge( RevEdge_t* __rev, val_t __val );
    void _eraseEdge( Edge_t* __ori, val_t __val );
    void _eraseRevEdge( RevEdge_t* __rev, val_t __val );
};



BASIC_NAMESPACE_END

#endif // __NODE_HPP__
