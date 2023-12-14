#if !defined(__MAP_HPP__)
#define __MAP_HPP__

#include "macros.hpp"
#include "Edge.hpp"
#include <unordered_map>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <exception>
#include <stdexcept>

BASIC_NAMESPACE_BEGIN

// class Basic_Map
// {
// public:
//     // using Edge_Set = std::set<Edge *>;

// protected:
//     std::unordered_map<id_t, std::map<val_t, Edge_Set>> _edgeList;
//     std::unordered_map<id_t, std::map<val_t, Edge_Set>> _reverseEdgeList;
//     size_t _edgeSize = 0;

//     std::vector<Node *> _nodeList;
//     std::map<id_t, Node *> _endNode;

//     Node *_startNode;
//     size_t _nodeSize = 0;
// };

class Map
{
public:
    using Node_set = std::set<Node*>;
    using Edge_set = std::map<val_t, Node_set>;

private:
    // 如：edgeList[0][1]是从 0结点 经过 1 能到达的边的集合
    // 又如：edgeList[0]可以获得0结点的邻接表
    std::unordered_map<id_t, std::map<val_t, Node_set>> _edgeList;

    // 反向的邻接表，便于获取指向某节点的边
    std::unordered_map<id_t, std::map<val_t, Node_set>> _reverseEdgeList;
    size_t _edgeSize = 0;

    std::vector<Node*> _nodeList;
    std::map<id_t, Node*> _endNode;

    Node* _startNode;
    size_t _nodeSize = 0;
    void _insertEdge( id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal );
    void _insertReverseEdge( id_t __fromId, id_t __toId, val_t __edgeVal );

public:
    Map();
    Map( size_t __nodeSize );
    void insertEdge( id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal );
    id_t insertNode( node_t __nodeType );
};

// 该类为所有转换嘞的接口，
// 所有的转换都最好通过 “新建类，继承该接口，并重写该类的convert成员函数” 来实现
class Converter
{
public:
    virtual Map convert() = 0;
};

BASIC_NAMESPACE_END

#endif // __MAP_HPP__
