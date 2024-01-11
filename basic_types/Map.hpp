#pragma once
#ifndef __M_MAP_HPP__
#define __M_MAP_HPP__

#include "Node.hpp"
#include <unordered_map>
#include <map>
#include <set>
#include <stdexcept>
#include <iostream>
#include <vector>

BASIC_NAMESPACE_BEGIN

class Map
{
public:
    struct iterator;
    struct iterator_cmp;
    using iterator_set = std::set<struct iterator, struct iterator_cmp>;

private:
    Node_set _nodeList;
    Node_set _endNode;
    Node* _startNode;
    
    size_t _edgeSize = 0;
    size_t _nodeSize = 0;

public:
    static Map concat( const Map& __a, const Map& __b );

    Map();
    Map( const Map& __src );
    Map( Map&& __src );

    // 创建一条边
    void insertEdge( iterator __from, iterator __to, val_t __edgeVal );
    // 创建一个结点
    iterator insertNode( node_t::_type __nodeType );
    // 改变结点属性（开始状态，中间状态，结束状态）
    void setNodeType( iterator __tar, node_t::_type __nodeType );

    //void setTrapNode(iterator __trap);
    
    // 删除一条边
    void eraseEdge( iterator __from, iterator __to, val_t __edgeVal );
    // 删除一个结点，且与之相关的边全部被清除s
    void eraseNode( iterator& __target );

    // 快捷地创建一个与已有结点相连的结点
    iterator expandNode( iterator __from, val_t __edgeVal );
    // 合并两个结点，并且，将src合并至dest后，src被弃用
    iterator mergeNode( iterator __dest, iterator __src );


    // 在该Map后连接另一个Map（不常用）
    void concat( const Map& __rhs );
    // 开始状态
    iterator begin() const;
    ////返回陷阱状态
    //iterator trap() const;
    // 返回结束状态的迭代器集合
    iterator_set dest() const;
    // 返回所有结点的迭代器集合
    iterator_set all() const;
    // 返回一个iterator(nullptr)，用于判断越界
    iterator end() const;
    // 返回该Map是否为空
    bool empty() const;
    // 清空该图
    void clear();
    // 测试用输出
    void outputTest();

    Map& operator=( const Map& __rhs );
};

struct Map::iterator
{
    bool operator==( const Node* __rhs ) const;
    bool operator==( const iterator& __rhs ) const { return this->_m_val == __rhs._m_val; }
    bool operator!=( const iterator& __rhs ) const { return this->_m_val != __rhs._m_val; }
    const iterator& operator=( const iterator& __rhs ) { this->_m_val = __rhs._m_val; return *this; }
    bool operator<( const iterator& __rhs ) const { return this->_m_val < __rhs._m_val; }
    // 获得指向实际结点的指针（不常用）
    const Node* get() const;
    // 返回当前结点的类型（开始、中间或结束）
    node_t type() const;
    // 返回该结点通过val能到达的结点集合
    iterator_set next( val_t __val ) const;


    // 返回能通过val的空闭包到达该结点的结点集合的空闭包
    // iterator_set next_closure( val_t __val ) const;
    // //返回该节点空闭包
    // iterator_set e_closure() const;
    // //清理求空闭包过程中的标记
    // void clearflag() const;

    iterator_set revNext( val_t __val ) const;
    // 弃用该迭代器
    void deprecate();
    // 构造函数
    iterator();
    // 复制构造函数
    iterator( const iterator& __rhs );
    friend class Map;
public:

private:
    Node* _m_val;
    Node& operator*() const { return *_m_val; }
    Node* operator->() { return (this->_m_val); }
    explicit iterator( Node* __node );
};

struct Map::iterator_cmp
{
public:
    bool operator()( Map::iterator a, Map::iterator b ) const;  //仿函数，重载operator()运算符
};


BASIC_NAMESPACE_END

#endif // __MAP_HPP__}}
