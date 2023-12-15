#include "Map.hpp"

BASIC_NAMESPACE_BEGIN

Map::Map()
    : _edgeList(),
      _reverseEdgeList(),
      _nodeList(),
      _nodeSize(0),
      _startNode(nullptr)
{
}

Map::Map(size_t __nodeSize)
    : Map()
{
    _nodeList.resize(__nodeSize, new Node(++_nodeSize, node_t::MIDDLE));
}

void Map::_insertEdge(id_t __fromId, id_t __toId, val_t __edgeVal)
{
    auto &li = _edgeList[__fromId];
    auto tar = li.find(__edgeVal);
    if (tar == li.end())
    {
        li.insert(std::pair<val_t, Node_set>(__edgeVal, Node_set({_nodeList[__toId]})));
    }
    else
    {
        li[__edgeVal].insert(_nodeList[__toId]);
    }
}

void Map::_insertReverseEdge(id_t __toId, id_t __fromId, val_t __edgeVal)
{
    auto &li = _reverseEdgeList[__fromId];
    auto tar = li.find(__edgeVal);
    if (tar == li.end())
    {
        li.insert(std::pair<val_t, Node_set>(__edgeVal, Node_set({_nodeList[__toId]})));
    }
    else
    {
        li[__edgeVal].insert(_nodeList[__toId]);
    }
}

void Map::insertEdge(id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal)
{
    _insertEdge(__fromNodeId, __toNodeId, __edgeVal);
    _insertReverseEdge(__fromNodeId, __toNodeId, __edgeVal);
}

id_t Map::insertNode(node_t __nodeType)
{

    _nodeList[++_nodeSize] = new Node(_nodeSize, __nodeType);
    if (__nodeType == node_t::START)
    {
        if (_startNode != nullptr)
        {
            throw std::runtime_error("A node marked \'start\' already exists.");
        }
        else
        {
            _startNode = _nodeList[_nodeSize];
        }
    }

    return _nodeSize;
}

BASIC_NAMESPACE_END