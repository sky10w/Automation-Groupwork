#if !defined(__NODE_HPP__)
#define __NODE_HPP__

#include "macros.hpp"

BASIC_NAMESPACE_BEGIN

struct Node
{
    id_t id;
    node_t type;
    Node(id_t __id, node_t __val);
};

BASIC_NAMESPACE_END

#endif // __NODE_HPP__
