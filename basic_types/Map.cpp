#include "Map.hpp"

BASIC_NAMESPACE_BEGIN

Map::Map()
    : _edgeList(),
      _reverseEdgeList(),
      _nodeList(),
      _nodeSize(0)
{
}

Map::Map(size_t __nodeSize)
{
    _nodeList.resize(__nodeSize, new Node(++_nodeSize, node_t::MIDDLE));
}

void Map::insertEdge(id_t __fromId, id_t __toId, val_t __edgeVal)
{

    auto &li = _edgeList[__fromId];
    auto tar = li.find(__toId);
    if (tar == li.end())
    {
        li.insert(std::pair(__toId, new Edge(_nodeList[__fromId], _nodeList[__toId], ++_edgeSize)));
    }
    else
    {
        (*tar).second->insertVal(__edgeVal);
    }
}

id_t Map::insertNode(node_t __nodeType)
{
    _nodeList[++_nodeSize] = new Node(_nodeSize, __nodeType);

    return _nodeSize;
}

BASIC_NAMESPACE_END