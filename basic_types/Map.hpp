#if !defined(__MAP_HPP__)
#define __MAP_HPP__

#include "macros.hpp"
#include "Edge.hpp"
#include <unordered_map>
#include <map>
#include <vector>
#include <list>

BASIC_NAMESPACE_BEGIN

struct Basic_Map
{
    std::unordered_map<id_t, std::map<id_t, Edge *>> _edgeList;
    std::unordered_map<id_t, std::map<id_t, Edge *>> _reverseEdgeList;
    size_t _edgeSize = 0;

    std::vector<Node *> _nodeList;
    std::map<id_t, Node *> _endNode;

    Node *_startNode;
    size_t _nodeSize = 0;
};

class Map
{
private:
    // edgeList可以理解为一个二维数组，又可以理解为一个邻接表
    // 如：edgeList[0]可以获得0结点的邻接表
    // 同时：edgeList[0][1]又是从 0结点 到 1结点 边的指针
    std::unordered_map<id_t, std::map<id_t, Edge *>> _edgeList;

    // 反向的邻接表，便于获取指向某节点的边
    std::unordered_map<id_t, std::map<id_t, Edge *>> _reverseEdgeList;
    size_t _edgeSize = 0;

    std::vector<Node *> _nodeList;

    Node *_startNode;
    size_t _nodeSize = 0;

public:
    Map();
    Map(size_t __nodeSize);
    ~Map();
    void insertEdge(id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal);
    id_t insertNode(node_t __nodeType);
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
