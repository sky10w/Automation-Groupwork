#include "Map.hpp"

BASIC_NAMESPACE_BEGIN

/*
std::set<Map::iterator> Map::iterator::next( val_t __next )
{
    std::set<Map::iterator, Map::iterator_cmp> temp;
    for (auto& i : _m_val->to[__next])
    {
        const Map::iterator s( i );
        temp.insert( s );
    }
    return temp;
}

Map::iterator::iterator( Node* __node )
    :_m_val( __node )
{}
*/


Map::Map()
    : _edgeList(),
    // _reverseEdgeList(),
    _nodeList(),
    _nodeSize( 0 ),
    _startNode( nullptr ),
    _endNode()
{}


Map::Map( size_t __nodeSize )
    : Map()
{
    _nodeList.resize( __nodeSize, new Node( ++_nodeSize, node_t::MIDDLE ) );
}

void Map::_insertEdge( id_t __fromId, id_t __toId, val_t __edgeVal )
{
    auto& li = _edgeList[__fromId];
    auto tar = li.find( __edgeVal );
    if (tar == li.end())
    {
        li.insert( std::pair<val_t, Node_set>( __edgeVal, Node_set( { _nodeList[__toId] } ) ) );
    } else
    {
        li[__edgeVal].insert( _nodeList[__toId] );
    }
}

// void Map::_insertReverseEdge( id_t __toId, id_t __fromId, val_t __edgeVal )
// {
//     auto& li = _reverseEdgeList[__fromId];
//     auto tar = li.find( __edgeVal );
//     if (tar == li.end())
//     {
//         li.insert( std::pair<val_t, Node_set>( __edgeVal, Node_set( { _nodeList[__toId] } ) ) );
//     } else
//     {
//         li[__edgeVal].insert( _nodeList[__toId] );
//     }
// }

void Map::insertEdge( id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal )
{
    _insertEdge( __fromNodeId, __toNodeId, __edgeVal );
    // _insertReverseEdge( __fromNodeId, __toNodeId, __edgeVal );
    _edgeSize++;
}

id_t Map::insertNode( node_t __nodeType )
{
    _nodeSize++;
    _nodeList[_nodeSize] = new Node( _nodeSize, __nodeType );
    if (__nodeType == node_t::START)
    {
        if (_startNode != nullptr)
        {
            throw std::runtime_error( "A node marked \'start\' already exists." );
        } else
        {
            _startNode = _nodeList[_nodeSize];
        }
    } else if (__nodeType == node_t::END)
    {
        _endNode.insert( _nodeList[_nodeSize] );
    }

    return _nodeSize;
}

id_t Map::expand( id_t __fromId, val_t __edgeVal )
{
    id_t newNode = this->insertNode( node_t::MIDDLE );
    this->insertEdge( __fromId, newNode, __edgeVal );
    return newNode;
}

// void Map::eraseEdge( id_t __fromId, id_t __toId, val_t __edgeVal )
// {
//     auto tarVal = _edgeList[__fromId][__edgeVal];
//     auto tar = tarVal.find( _nodeList[__toId] );
//     if (tar == tarVal.end())
//     {
//         throw std::runtime_error( "No such edge exists" );
//     }
//     tarVal.erase( tar );
// }

// void Map::eraseNode( id_t __target )
// {
//     auto tar = _edgeList[__target];
//     tar.clear();
//     _nodeList[__target]->id = 0;
// }

void Map::concat( const Map& __rhs )
{

}


id_t Map::begin()
{
    if (_startNode == nullptr)
        return 0;
    return _startNode->id;
}

std::set<id_t> Map::last()
{
    std::set<id_t> temp;
    for (auto& i : _endNode)
    {
        temp.insert( i->id );
    }

    return temp;
}

id_t Map::end()
{
    return 0;
}



BASIC_NAMESPACE_END

