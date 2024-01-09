#include "macros.hpp"

BASIC_NAMESPACE_BEGIN


std::ostream& operator<<( std::ostream& __lhs, node_t& __rhs )
{
    if (__rhs == node_type::START_END)
    {
        std::cout << "Start&End";
    } else if (__rhs == node_type::START)
    {
        std::cout << "Start";
    } else if (__rhs == node_type::END)
    {
        std::cout << "End";
    } else
    {
        std::cout << "Middle";
    }
    return __lhs;
}


BASIC_NAMESPACE_END