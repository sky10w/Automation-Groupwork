#ifndef __MACROS_HPP__
#define __MACROS_HPP__

#define BASIC_NAMESPACE_BEGIN \
    namespace ato             \
    {
#define BASIC_NAMESPACE_END }

#include <iostream>

BASIC_NAMESPACE_BEGIN

const char EPSILON = 'E';

struct node_type
{
    enum _type : int
    {
        START = 0,
        MIDDLE = 1,
        END = 2,
        START_END = 3
    };
    _type t;
    node_type( _type b );
    _type get() const;
    _type operator+=( _type b );
    bool operator==( _type b );
    bool operator!=( _type b );
    _type operator-=( _type b );
};
using node_t = struct node_type;

// enum class node_type : int
// {
//     START,
//     MIDDLE,
//     END,
//     START_END
// };
// using node_t = enum class node_type;



std::ostream& operator<<( std::ostream& __lhs, node_t& __rhs );



using id_t = int;

using val_t = char;


BASIC_NAMESPACE_END

#endif