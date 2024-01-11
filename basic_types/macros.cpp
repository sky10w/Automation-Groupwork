#include "macros.hpp"

BASIC_NAMESPACE_BEGIN

node_type::node_type( _type b )
    :t( b )
{}

node_type::_type node_type::get() const
{
    return this->t;
}

node_type::_type node_type::operator+=( node_type::_type b )
{
    if (b == node_type::MIDDLE)
    {
        this->t = node_type::MIDDLE;
    } else if ((this->t == node_type::START && b == node_type::END)
        || (this->t == node_type::END && b == node_type::START))
    {
        this->t = node_type::START_END;
    } else if (b == node_type::START_END)
    {
        this->t = node_type::START_END;
    } else if (this->t == node_type::MIDDLE)
    {
        this->t = b;
    }
    return this->t;
}
bool node_type::operator==( _type b )
{
    if (this->t == node_type::START_END && (b == node_type::START || b == node_type::END)) return true;
    return this->t == b;
}
bool node_type::operator!=( _type b )
{
    if (this->t == node_type::START_END && (b == node_type::START || b == node_type::END)) return false;
    return this->t != b;
}
node_type::_type node_type::operator-=( _type b )
{
    if (this->t == node_type::START_END)
    {
        if (b == node_type::END)
            this->t = node_type::START;
        if (b == node_type::START)
            this->t = node_type::END;
    } else if (this->t == b) this->t = node_type::MIDDLE;

    return this->t;
}


std::ostream& operator<<( std::ostream& __lhs, node_t& __rhs )
{
    if (__rhs == node_type::START_END)
    {
        __lhs << "Start&End";
    } else if (__rhs == node_type::START)
    {
        __lhs << "Start";
    } else if (__rhs == node_type::END)
    {
        __lhs << "End";
    } else
    {
        __lhs << "Middle";
    }
    return __lhs;
}


BASIC_NAMESPACE_END