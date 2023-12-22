#if !defined(__MAP_HPP__)
#define __MAP_HPP__

#include "macros.hpp"
#include "Node.hpp"
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
    Node_set _nodeList;
    Node_set _endNode;
    Node* _startNode;
    size_t _nodeSize = 0;

public:
    Map();
    void insertEdge( iterator __from, iterator __to, val_t __edgeVal );
    iterator insertNode( node_t __nodeType );

    void eraseEdge( iterator __from, iterator __to, val_t __edgeVal );
    void eraseNode( iterator& __target );

    iterator expandNode( iterator __fromId, val_t __edgeVal );
    iterator_set next( iterator __from, val_t __val );
    iterator_set revNext( iterator __from, val_t __val );
    // 开始状态
    iterator begin();
    // 结束状态
    iterator_set dest();
    iterator end();
};

struct Map::iterator
{
    Node& operator*() const { return *_m_val; }
    bool operator==( const Node* __rhs ) const { return this->_m_val == __rhs; }
    bool operator==( const iterator& __rhs ) const { return this->_m_val == __rhs._m_val; }
    bool operator<( const iterator& __rhs ) const { return this->_m_val < __rhs._m_val; }
    Node* operator->() { return ( this->_m_val ); }
    Node* get() const;
    iterator_set next( val_t __val ) const;
    void deprecate();
    explicit iterator( Node* __node );
    iterator( const iterator& __rhs );
private:
    Node* _m_val;
};

struct Map::iterator_cmp
{
    bool operator()( struct iterator a, struct iterator b ) const;  //仿函数，重载operator()运算符
};


BASIC_NAMESPACE_END

#endif // __MAP_HPP__}}
