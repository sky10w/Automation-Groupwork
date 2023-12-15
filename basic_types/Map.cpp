#include "Map.hpp"

BASIC_NAMESPACE_BEGIN

// size_t Map::iterator_hash::operator()( const Map::iterator& __iter ) const
// {
//     return std::hash<Node*>()( __iter._m_val );
// }

Node* Map::iterator::get()
{
    return this->_m_val;
}

bool Map::iterator_cmp::operator()( struct iterator a, struct iterator b ) const  //仿函数，重载operator()运算符
{
    return a < b;
}


Map::iterator::iterator( Node* __node )
    :_m_val( __node )
{}

Map::iterator::iterator( const iterator& __rhs )
{
    _m_val = __rhs._m_val;
}

Map::Map()
    : _edgeList(),
    // _reverseEdgeList(),
    _nodeList(),
    _nodeSize( 0 ),
    _startNode( nullptr ),
    _endNode()
{}


void Map::_insertEdge( Map::iterator __from, Map::iterator __to, val_t __edgeVal )
{
    auto tar = __from->edge.find( __edgeVal );
    if (tar == __from->edge.end())
    {
        auto res = __from->edge.insert( std::pair<val_t, Node_set>( __edgeVal, Node_set( { __to.get() } ) ) );
        if (res.second)
        {
            std::cerr << "You are inserting two completely same edge." << std::endl;
        }
    } else
    {
        __from->edge[__edgeVal].insert( __to.get() );
    }
}

void Map::_insertRevEdge( Map::iterator __to, Map::iterator __from, val_t __revEdgeVal )
{
    auto tar = __from->revEdge.find( __revEdgeVal );
    if (tar == __from->revEdge.end())
    {
        auto res = __from->revEdge.insert( std::pair<val_t, Node_set>( __revEdgeVal, Node_set( { __to.get() } ) ) );
        if (res.second)
        {
            std::cerr << "You are inserting two completely same reverse revEdge." << std::endl;
        }
    } else
    {
        __from->revEdge[__revEdgeVal].insert( __to.get() );
    }
}

void Map::insertEdge( Map::iterator __from, Map::iterator __to, val_t __edgeVal )
{
    _insertEdge( __from, __to, __edgeVal );
    _insertRevEdge( __from, __to, __edgeVal );

    if (__to->type == ato::node_t::START)
        __to->type = ato::node_t::MIDDLE;
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
            throw std::runtime_error( "A node marked \'start\' already exists." );
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

Map::iterator Map::expand( Map::iterator __from, val_t __edgeVal )
{
    Map::iterator newNode = this->insertNode( node_t::MIDDLE );
    this->insertEdge( __from, newNode, __edgeVal );
    return newNode;
}

void Map::eraseEdge( Map::iterator __from, Map::iterator __to, val_t __edgeVal )
{
    auto tarVal = _edgeList[__from.get()][__edgeVal];
    auto tar = tarVal.find( __to.get() );
    if (tar == tarVal.end())
    {
        throw std::runtime_error( "No such edge exists" );
    }
    tarVal.erase( tar );
}

void Map::eraseNode( Map::iterator __target )
{
    auto tar = _edgeList[__target.get()];
    tar.clear();
    __target->id = 0;
}

Map::iterator_set Map::next( iterator __from, val_t __val )
{
    Map::iterator_set temp;
    for (auto& i : _edgeList[__from.get()][__val])
    {
        temp.insert( Map::iterator( i ) );
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






// ----- Use ID ------



// void Map::_insertEdge( id_t __fromId, id_t __to, val_t __edgeVal )
// {
//     auto& li = _edgeList[__fromId];
//     auto tar = li.find( __edgeVal );
//     if (tar == li.end())
//     {
//         li.insert( std::pair<val_t, Node_set>( __edgeVal, Node_set( { _nodeList[__to] } ) ) );
//     } else
//     {
//         li[__edgeVal].insert( _nodeList[__to] );
//     }
// }

// // void Map::_insertReverseEdge( id_t __to, id_t __fromId, val_t __edgeVal )
// // {
// //     auto& li = _reverseEdgeList[__fromId];
// //     auto tar = li.find( __edgeVal );
// //     if (tar == li.end())
// //     {
// //         li.insert( std::pair<val_t, Node_set>( __edgeVal, Node_set( { _nodeList[__to] } ) ) );
// //     } else
// //     {
// //         li[__edgeVal].insert( _nodeList[__to] );
// //     }
// // }

// void Map::insertEdge( id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal )
// {
//     _insertEdge( __fromNodeId, __toNodeId, __edgeVal );
//     // _insertReverseEdge( __fromNodeId, __toNodeId, __edgeVal );
//     _edgeSize++;
// }

// id_t Map::insertNode( node_t __nodeType )
// {
//     _nodeSize++;
//     _nodeList[_nodeSize] = new Node( _nodeSize, __nodeType );
//     if (__nodeType == node_t::START)
//     {
//         if (_startNode != nullptr)
//         {
//             throw std::runtime_error( "A node marked \'start\' already exists." );
//         } else
//         {
//             _startNode = _nodeList[_nodeSize];
//         }
//     } else if (__nodeType == node_t::END)
//     {
//         _endNode.insert( _nodeList[_nodeSize] );
//     }

//     return _nodeSize;
// }

// id_t Map::expand( id_t __fromId, val_t __edgeVal )
// {
//     id_t newNode = this->insertNode( node_t::MIDDLE );
//     this->insertEdge( __fromId, newNode, __edgeVal );
//     return newNode;
// }

// // void Map::eraseEdge( id_t __fromId, id_t __to, val_t __edgeVal )
// // {
// //     auto tarVal = _edgeList[__fromId][__edgeVal];
// //     auto tar = tarVal.find( _nodeList[__to] );
// //     if (tar == tarVal.end())
// //     {
// //         throw std::runtime_error( "No such edge exists" );
// //     }
// //     tarVal.erase( tar );
// // }

// // void Map::eraseNode( id_t __target )
// // {
// //     auto tar = _edgeList[__target];
// //     tar.clear();
// //     _nodeList[__target]->id = 0;
// // }

// void Map::concat( const Map& __rhs )
// {

// }


// id_t Map::begin()
// {
//     if (_startNode == nullptr)
//         return 0;
//     return _startNode->id;
// }

// std::set<id_t> Map::last()
// {
//     std::set<id_t> temp;
//     for (auto& i : _endNode)
//     {
//         temp.insert( i->id );
//     }

//     return temp;
// }

// id_t Map::end()
// {
//     return 0;
// }



BASIC_NAMESPACE_END

