#ifndef __MACROS_HPP__
#define __MACROS_HPP__

#define BASIC_NAMESPACE_BEGIN \
    namespace ato             \
    {
#define BASIC_NAMESPACE_END }

enum class node_type : int
{
    START,
    MIDDLE,
    END
};

using id_t = int;

using val_t = char;

using node_t = enum node_type;

class Converter
{
};

#endif