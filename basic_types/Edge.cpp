#include "Edge.hpp"

BASIC_NAMESPACE_BEGIN

Edge::Edge(Node *__from, Node *__to, id_t __id)
    : from(__from),
      to(__to),
      id(__id)
{
}

BASIC_NAMESPACE_END
