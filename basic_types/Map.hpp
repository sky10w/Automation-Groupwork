#if !defined(__MAP_HPP__)
#define __MAP_HPP__

#include "macros.hpp"
#include "Edge.hpp"
#include <unordered_map>
#include <map>
#include <set>
#include <stdexcept>
#include <iostream>

BASIC_NAMESPACE_BEGIN


class Map
{
public:
    struct iterator;
    struct iterator_cmp;
    using iterator_set = std::set<struct iterator, struct iterator_cmp>;

private:
    size_t _edgeSize = 0;
    std::unordered_map<Node*, std::map<val_t, Node_set>> _edgeList;
    std::unordered_map<Node*, std::map<val_t, Node_set>> _revEdgeList;

    Node_set _nodeList;
    Node_set _endNode;
    Node* _startNode;
    size_t _nodeSize = 0;

    void _insertEdge( iterator __from, iterator __to, val_t __edgeVal );
    void _insertRevEdge( iterator __from, iterator __to, val_t __revEdgeVal );
public:
    Map();
    void insertEdge( iterator __from, iterator __to, val_t __edgeVal );
    iterator insertNode( node_t __nodeType );
    iterator expand( iterator __fromId, val_t __edgeVal );

    void eraseEdge( iterator __from, iterator __to, val_t __edgeVal );
    void eraseNode( iterator __target );

    iterator_set next( iterator __from, val_t __val );
    iterator_set dest();
    iterator end();
    iterator begin();
};

struct Map::iterator
{
    Node& operator*() { return *_m_val; }
    bool operator==( const iterator& __rhs ) { return this->_m_val == __rhs._m_val; }
    bool operator<( const iterator& __rhs ) { return this->_m_val < __rhs._m_val; }
    Node* operator->() { return ( this->_m_val ); }
    Node* get();
    iterator( Node* __node );
    iterator( const iterator& __rhs );
    // friend Map::iterator_hash;
private:
    Node* _m_val;
};

struct Map::iterator_cmp
{
    bool operator()( struct iterator a, struct iterator b ) const;  //仿函数，重载operator()运算符
};





// -----Use ID-----

// class Map
// {
// public:
//     using Node_set = std::set<Node*>;
//     using Edge_set = std::map<val_t, Node_set>;

// private:
//     // 如：edgeList[0][1]是从 0结点 经过 1 能到达的边的集合
//     // 又如：edgeList[0]可以获得0结点的邻接表
//     std::unordered_map<id_t, std::map<val_t, Node_set>> _edgeList;

//     // 反向的邻接表，便于获取指向某节点的边
//     // std::unordered_map<id_t, std::map<val_t, Node_set>> _reverseEdgeList;
//     size_t _edgeSize = 0;

//     std::vector<Node*> _nodeList;
//     std::set<Node*> _endNode;
//     Node* _startNode;
//     size_t _nodeSize = 0;

//     void _insertEdge( id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal );
//     void _insertReverseEdge( id_t __fromId, id_t __toId, val_t __edgeVal ) = delete;
//     Node* _getNode( id_t __id ) = delete;


// public:
//     Map();
//     Map( size_t __nodeSize );

//     void insertEdge( id_t __fromNodeId, id_t __toNodeId, val_t __edgeVal );
//     id_t insertNode( node_t __nodeType );
//     id_t expand( id_t __fromId, val_t __edgeVal );

//     // 如果用id_t作为每个结点的唯一标识，那么几乎不可能进行删除
//     // void eraseEdge( id_t __fromId, id_t __toId, val_t __edgeVal );
//     // void eraseNode( id_t __target );

//     void concat( const Map& __rhs );

//     id_t begin();
//     std::set<id_t> last();
//     id_t end();
// };


BASIC_NAMESPACE_END

#endif // __MAP_HPP__
