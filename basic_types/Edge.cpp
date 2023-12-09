#include "Edge.hpp"

BASIC_NAMESPACE_BEGIN

Edge::Edge(Node *__from, Node *__to, id_t __id)
    : from(__from),
      to(__to),
      id(__id)
{
}

void Edge::insertVal(const val_t &__val)
{
    valList.insert(__val);
}

BASIC_NAMESPACE_END
