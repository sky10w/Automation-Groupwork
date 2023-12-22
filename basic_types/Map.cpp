#include "Map.hpp"

BASIC_NAMESPACE_BEGIN

Node* Map::iterator::get() const
{
    return this->_m_val;
}

Map::iterator_set Map::iterator::next( val_t __val ) const
{
    iterator_set temp;
    for (auto& i : this->_m_val->edge[__val])
    {
        temp.insert( iterator( i->to() ) );
    }
    return temp;
}

void Map::iterator::deprecate()
{
    this->_m_val = nullptr;
}

bool Map::iterator_cmp::operator()( struct iterator __a, struct iterator __b ) const  //仿函数，重载operator()运算符
{
    return __a < __b;
}


Map::iterator::iterator( Node* __node )
    :_m_val( __node )
{}

Map::iterator::iterator( const iterator& __rhs )
{
    _m_val = __rhs._m_val;
}

Map::Map()
    : _nodeList()
    , _nodeSize( 0 )
    , _startNode( nullptr )
    , _endNode()
{}



void Map::insertEdge( Map::iterator __from, Map::iterator __to, val_t __edgeVal )
{
    __from->insertEdge( __to.get(), __edgeVal );

    if (__to->type == ato::node_t::START)
    {
        __to->type = ato::node_t::MIDDLE;
    }
    _edgeSize++;
}

Map::iterator Map::insertNode( node_t __nodeType )
{
    _nodeSize++;
    auto temp = new Node( _nodeSize, __nodeType );
    _nodeList.insert( temp );
    if (__nodeType == node_t::START)
    {
        if (_startNode != nullptr)
        {
            _startNode = temp;
        } else
        {
            _startNode = temp;
        }
    } else if (__nodeType == node_t::END)
    {
        _endNode.insert( temp );
    }

    return iterator( temp );
}

Map::iterator Map::expandNode( Map::iterator __from, val_t __edgeVal )
{
    Map::iterator newNode = this->insertNode( node_t::MIDDLE );
    this->insertEdge( __from, newNode, __edgeVal );
    return newNode;
}

void Map::eraseEdge( Map::iterator __from, Map::iterator __to, val_t __edgeVal )
{
    __from->eraseEdge( __to.get(), __edgeVal );
}

void Map::eraseNode( Map::iterator& __target )
{
    auto iter = _nodeList.find( __target.get() );
    _nodeList.erase( iter );

    __target->clear();
    delete __target.get();
    __target.deprecate();
}

Map::iterator_set Map::next( iterator __from, val_t __val )
{
    Map::iterator_set temp;
    for (auto& i : __from->edge[__val])
    {
        temp.insert( Map::iterator( i->to() ) );
    }
    return temp;
}

Map::iterator_set Map::revNext( iterator __from, val_t __val )
{
    auto temp = Map::iterator_set();
    for (auto& i : __from->revEdge[__val])
    {
        temp.insert( Map::iterator( i->to() ) );
    }
    return temp;
}

Map::iterator_set Map::dest()
{
    auto temp = Map::iterator_set();
    for (auto i : _endNode)
    {
        temp.insert( Map::iterator( i ) );
    }
    return temp;
}

Map::iterator Map::end()
{
    return Map::iterator( nullptr );
}

Map::iterator Map::begin()
{
    return Map::iterator( _startNode );
}

bool operator==( Node* __lhs, Map::iterator __rhs )
{
    return __lhs == __rhs.get();
}

BASIC_NAMESPACE_END


