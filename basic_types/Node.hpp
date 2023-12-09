#if !defined(__NODE_HPP__)
#define __NODE_HPP__

#include "macros.hpp"

BASIC_NAMESPACE_BEGIN

struct Node
{
    id_t id;
    Node(id_t __id);
};

BASIC_NAMESPACE_END

#endif // __NODE_HPP__
