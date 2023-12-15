#if !defined(__NODE_HPP__)
#define __NODE_HPP__

#include "macros.hpp"
#include <map>
#include <set>

BASIC_NAMESPACE_BEGIN

struct Node;

using Node_set = std::set<struct Node*>;
struct Node
{
    id_t id;
    node_t type;
    std::map<val_t, Node_set> edge;
    std::map<val_t, Node_set> revEdge;
    Node( id_t __id, node_t __val );
};



BASIC_NAMESPACE_END

#endif // __NODE_HPP__
