#ifndef __M_NODE_HPP__
#define __M_NODE_HPP__


#include "Edge_imp.hpp"
#include <iostream>
#include <map>
#include <set>
#include <memory>

BASIC_NAMESPACE_BEGIN

struct Node;
template <typename _T>
class Edge;
template <typename _T>
class RevEdge;

// template class Edge<Node>;
// template class RevEdge<Node>;


using Node_set = std::set<Node*>;

using Edge_t = Edge<Node>;
using RevEdge_t = RevEdge<Node>;

class EdgeCmp
{
public:
    bool operator()( Edge_t* __a, Edge_t* __b ) const;
};
class RevEdgeCmp
{
public:
    bool operator()( RevEdge_t* __a, RevEdge_t* __b ) const;
};

using Edge_set = std::set<Edge_t*, EdgeCmp>;
using RevEdge_set = std::set<RevEdge_t*, RevEdgeCmp>;

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
    Node( const Node& __src );
    virtual ~Node();
private:
    void _insertEdge( Edge_t* __ori, val_t __val );
    void _insertRevEdge( RevEdge_t* __rev, val_t __val );
    void _eraseEdge( Edge_t* __ori, val_t __val );
    void _eraseRevEdge( RevEdge_t* __rev, val_t __val );
};



BASIC_NAMESPACE_END

#endif // __NODE_HPP__
