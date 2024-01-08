#include "Map.hpp"


BASIC_NAMESPACE_BEGIN


const Node* Map::iterator::get() const
{
    return this->_m_val;
}

node_t Map::iterator::type() const
{
    return _m_val->type;
}

Map::iterator_set Map::iterator::next( val_t __val ) const
{
    iterator_set temp;
    if (this->get()->edge.find( __val ) == this->get()->edge.end())
    {
        return temp;
    }
    for (auto& i : this->_m_val->edge[__val])
    {
        temp.insert( iterator( i->to() ) );
    }
    return temp;
}

Map::iterator_set Map::iterator::revNext( val_t __val ) const
{
    iterator_set temp;
    if (this->get()->revEdge.find( __val ) == this->get()->revEdge.end())
    {
        return temp;
    }
    for (auto& i : this->_m_val->revEdge[__val])
    {
        temp.insert( iterator( i->to() ) );
    }
    return temp;
}


void Map::iterator::deprecate()
{
    this->_m_val = nullptr;
}

bool Map::iterator_cmp::operator()( struct iterator __a, struct iterator __b ) const  //仿函数，重载operator()运算符
{
    return __a < __b;
}


Map::iterator::iterator()
    :_m_val( nullptr )
{}

Map::iterator::iterator( Node* __node )
    :_m_val( __node )
{}

Map::iterator::iterator( const iterator& __rhs )
{
    _m_val = __rhs._m_val;
}

bool Map::iterator::operator==( const Node* __rhs ) const
{
    return this->_m_val == __rhs;
}

Map::Map()
    : _startNode( nullptr )
    , _edgeSize( 0 )
    , _nodeSize( 0 )
{}

Map::Map( const Map& __src )
{
    _startNode = nullptr;
    if (__src.empty())
    {
        return;
    }
    this->_nodeSize = __src._nodeSize;

    std::map<Node*, Node*> oldToNew;
    for (auto& i : __src._nodeList)
    {
        oldToNew.insert( { i, new Node( *i ) } );
        if (i == __src._startNode)
        {
            this->_startNode = oldToNew[i];
        }
    }
    for (auto& i : __src._endNode)
    {
        this->_endNode.insert( oldToNew[i] );
    }
    for (auto& i : oldToNew)
    {
        for (auto& valSet : i.first->edge)
        {
            for (auto& edge : valSet.second)
            {
                i.second->insertEdge( oldToNew[edge->to()], valSet.first );
            }
        }
        _nodeList.insert( i.second );
    }
}

Map::Map( Map&& __src )
    : _nodeList( std::move( __src._nodeList ) )
    , _endNode( std::move( __src._endNode ) )
    , _startNode( __src._startNode )
    , _edgeSize( __src._edgeSize )
    , _nodeSize( __src._nodeSize )
{}



void Map::insertEdge( Map::iterator __from, Map::iterator __to, val_t __edgeVal )
{
    __from->insertEdge( __to._m_val, __edgeVal );

    if (__to.type() == ato::node_t::START)
    {
        this->setNodeType( __from, node_t::START );
    }
    _edgeSize++;
}

Map::iterator Map::insertNode( node_t __nodeType )
{
    auto temp = new Node( _nodeSize, __nodeType );
    _nodeList.insert( temp );
    if (__nodeType == node_t::START)
    {
        if (_startNode != nullptr)
        {
            std::cout << "Warning: startNode is changed!" << '\n';
            _startNode = temp;
        } else
        {
            _startNode = temp;
        }
    } else if (__nodeType == node_t::END)
    {
        _endNode.insert( temp );
    }

    _nodeSize++;
    return iterator( temp );
}

void Map::setNodeType( iterator __tar, node_t __nodeType )
{
    if (__tar.type() == __nodeType) return;

    if (__tar.type() == node_t::END && __nodeType != node_t::END)
    {
        _endNode.erase( _endNode.find( __tar._m_val ) );
    } else if (__nodeType == node_t::END && __tar.type() != node_t::END)
    {
        _endNode.insert( &(*__tar) );
    }

    if (__tar.type() == node_t::START && __nodeType != node_t::START)
    {
        _startNode = nullptr;
    } else if (__nodeType == node_t::START && __tar.type() != node_t::START)
    {
        // 改变startNode
        _startNode->type = ato::node_t::MIDDLE;
        _startNode = &(*__tar);
    }

    __tar->type = __nodeType;

}

Map::iterator Map::expandNode( Map::iterator __from, val_t __edgeVal )
{
    Map::iterator newNode = this->insertNode( node_t::MIDDLE );
    this->insertEdge( __from, newNode, __edgeVal );
    return newNode;
}

Map::iterator Map::mergeNode( iterator __dest, iterator __src )
{
    this->setNodeType( __dest, __src.type() );
    for (auto& i : __src->edge)
    {
        for (auto edge = i.second.begin(); edge != i.second.end(); )
        {
            auto cur = *(edge++);
            if (cur->to() == __dest.get())
            {
                this->eraseEdge( __src, __dest, i.first );
                continue;
            }
            cur->rev()->setTo( __dest._m_val );
        }
    }
    for (auto& i : __src->revEdge)
    {
        for (auto edge = i.second.begin(); edge != i.second.end(); )
        {
            auto cur = *(edge++);
            if (cur->to() == __dest.get())
            {
                this->eraseEdge( __dest, __src, i.first );
                continue;
            }
            cur->ori()->setTo( __dest._m_val );
        }
    }

    __dest->edge.insert( __src->edge.begin(), __src->edge.end() );
    __dest->revEdge.insert( __src->revEdge.begin(), __src->revEdge.end() );

    auto index = _nodeList.find( __src._m_val );
    _nodeList.erase( index );
    __src->clear();
    __src.deprecate();

    return __dest;
}

void Map::eraseEdge( Map::iterator __from, Map::iterator __to, val_t __edgeVal )
{
    __from->eraseEdge( __to._m_val, __edgeVal );
    _edgeSize--;
}

void Map::eraseNode( Map::iterator& __target )
{
    auto iter = _nodeList.find( __target._m_val );
    _nodeList.erase( iter );

    __target->clear();
    delete __target._m_val;
    __target.deprecate();
    _nodeSize--;
}


void Map::concat( const Map& __rhs )
{
    if (__rhs.empty())
    {
        return;
    }
    auto temp = Map( __rhs );
    auto post = temp._startNode;
    auto& pre = this->_endNode;
    this->setNodeType( iterator( post ), node_t::MIDDLE );
    for (auto& i : pre)
    {
        i->insertEdge( post, EPSILON );
        this->setNodeType( iterator( i ), node_t::MIDDLE );
    }
}

Map Map::concat( const Map& __a, const Map& __b )
{
    if (__a.empty() && __b.empty())
    {
        std::cout << "Better not concat two empty Map" << '\n';
        return Map();
    }
    if (__a.empty())
    {
        return Map( __b );
    } else if (__b.empty())
    {
        return Map( __a );
    }
    auto tempA = Map( __a );
    auto tempB = Map( __b );
    auto post = tempB._startNode;
    auto& pre = tempA._endNode;
    if (post == nullptr)
    {
        std::cout << "Warning: the startNode of left Map is nullptr" << '\n';
    } else
    {
        tempB.setNodeType( iterator( post ), node_t::MIDDLE );
    }
    for (auto& i : pre)
    {
        i->insertEdge( post, EPSILON );
        tempA.setNodeType( iterator( i ), node_t::MIDDLE );
    }
    return tempA;
}

Map::iterator_set Map::dest() const
{
    auto temp = Map::iterator_set();
    for (auto i : _endNode)
    {
        temp.insert( Map::iterator( i ) );
    }
    return temp;
}

Map::iterator_set Map::all() const
{
    iterator_set temp;
    for (auto& i : _nodeList)
    {
        temp.insert( iterator( i ) );
    }
    return temp;
}

Map::iterator Map::end() const
{
    return Map::iterator( nullptr );
}

bool Map::empty() const
{
    return this->_nodeList.empty();
}

Map& Map::operator=( const Map& __rhs )
{
    if (this == &__rhs)
    {
        return *this;
    }
    _startNode = nullptr;
    if (__rhs.empty())
    {
        this->clear();
        return *this;
    }
    this->_nodeSize = __rhs._nodeSize;
    this->_edgeSize = __rhs._edgeSize;

    std::map<Node*, Node*> oldToNew;
    for (auto& i : __rhs._nodeList)
    {
        oldToNew.insert( { i, new Node( *i ) } );
        if (i == __rhs._startNode)
        {
            this->_startNode = oldToNew[i];
        }
    }
    for (auto& i : __rhs._endNode)
    {
        this->_endNode.insert( oldToNew[i] );
    }
    for (auto& i : oldToNew)
    {
        for (auto& valSet : i.first->edge)
        {
            for (auto& edge : valSet.second)
            {
                i.second->insertEdge( oldToNew[edge->to()], valSet.first );
            }
        }
        _nodeList.insert( i.second );
    }
    return *this;
}

void Map::clear()
{
    for (auto& i : _nodeList)
    {
        i->clear();
    }
    _nodeList.clear();
    _nodeSize = 0;
    _startNode = nullptr;
    _endNode.clear();
}

void Map::outputTest()
{
    if (this->empty())
    {
        std::cout << "This Map is empty\n";
    }
    int cnt = 0;
    std::map<Node*, int> id;
    for (auto& i : _nodeList)
    {
        id.insert( { i, ++cnt } );
        std::cout << "id-" << cnt << " : " << i << '\n';
    }
    for (auto& i : _nodeList)
    {
        std::cout << "id-" << id[i];

        if (i->type == ato::node_t::START)
        {
            std::cout << " [start]";
        } else if (i->type == ato::node_t::END)
        {
            std::cout << " [end]";
        }
        if (i->edge.empty())
        {
            std::cout << '\n';
            continue;
        }
        std::cout << " :\n";
        for (auto& j : i->edge)
        {
            if (j.second.empty()) continue;
            std::cout << "\t" << j.first << " -> ";
            size_t tempCnt = 0;
            for (auto& k : j.second)
            {
                tempCnt++;
                if (tempCnt == j.second.size())
                {
                    std::cout << id[k->to()];
                    break;
                }
                std::cout << id[k->to()] << ", ";
            }
            std::cout << '\n';
        }
    }
}


Map::iterator Map::begin() const
{
    return Map::iterator( _startNode );
}

bool operator==( Node* __lhs, Map::iterator __rhs )
{
    return __lhs == __rhs.get();
}

BASIC_NAMESPACE_END


