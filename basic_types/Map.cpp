#include "Map.hpp"

BASIC_NAMESPACE_BEGIN

Map::Map(size_t __nodeSize)
{
    _nodeList.resize(__nodeSize, new Node(++_nodeSize));
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

BASIC_NAMESPACE_END