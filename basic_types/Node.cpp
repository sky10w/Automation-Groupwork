#include "Node.hpp"

BASIC_NAMESPACE_BEGIN

Node::Node( id_t __id, node_t __type )
    : id( __id )
    , type( __type )
    , edge()
    , revEdge()
{}
using Node_set = std::set<Node*>;

BASIC_NAMESPACE_END