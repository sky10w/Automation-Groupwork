#if !defined(__EDGE_HPP__)
#define __EDGE_HPP__

#include "macros.hpp"
#include "Node.hpp"

BASIC_NAMESPACE_BEGIN

struct Edge
{
    id_t id;
    Node *from, *to;
    Edge(Node *__from, Node *__to, id_t __id);
};

BASIC_NAMESPACE_END

#endif // __EDGE_HPP__
