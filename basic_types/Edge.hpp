#if !defined(__EDGE_HPP__)
#define __EDGE_HPP__

#include "macros.hpp"
#include "Node.hpp"
#include <unordered_set>

BASIC_NAMESPACE_BEGIN

struct Edge
{
    id_t id;
    Node *from, *to;
    std::unordered_set<val_t> valList;
    Edge(Node *__from, Node *__to, id_t __id);
    void insertVal(const val_t &__val);
};

BASIC_NAMESPACE_END

#endif // __EDGE_HPP__
