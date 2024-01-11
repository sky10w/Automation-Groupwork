#include "Map.hpp"


BASIC_NAMESPACE_BEGIN

// Map::iterator_set __closure__flag;


const Node* Map::iterator::get() const
{
    return this->_m_val;
}

node_t Map::iterator::type() const
{
    return _m_val->type.t;
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

    std::map<iterator, iterator> oldToNew;
    for (auto& i : __src.all())
    {
        oldToNew.insert( { i, this->insertNode( i.type().get() ) } );
    }
    for (auto& i : __src.all())
    {
        for (auto& j : i._m_val->edge)
        {
            for (auto& edge : j.second)
            {
                this->insertEdge( oldToNew[i], oldToNew[iterator( edge->to() )], j.first );
            }
        }
    }

    // std::map<Node*, Node*> oldToNew;
    // for (auto& i : __src._nodeList)
    // {
    //     oldToNew.insert( { i, new Node( *i ) } );
    //     if (i == __src._startNode)
    //     {
    //         this->_startNode = oldToNew[i];
    //     }
    // }
    // for (auto& i : __src._endNode)
    // {
    //     this->_endNode.insert( oldToNew[i] );
    // }
    // for (auto& i : oldToNew)
    // {
    //     for (auto& valSet : i.first->edge)
    //     {
    //         for (auto& edge : valSet.second)
    //         {
    //             i.second->insertEdge( oldToNew[edge->to()], valSet.first );
    //         }
    //     }
    //     _nodeList.insert( i.second );
    // }
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

    // if (__to.type() == ato::node_t::START)
    // {
    //     this->setNodeType( __to, node_t::MIDDLE );
    //     this->setNodeType( __from, node_t::START );
    // }
    _edgeSize++;
}

Map::iterator Map::insertNode( node_t::_type __nodeType )
{
    auto temp = new Node( _nodeSize, ato::node_t::MIDDLE );
    this->setNodeType( Map::iterator( temp ), __nodeType );
    _nodeList.insert( temp );

    _nodeSize++;
    return iterator( temp );
}

void Map::setNodeType( iterator __tar, node_t::_type __nodeType )
{
    // 此处包括StartnEnd和Start、StartnEnd和End的情况
    if (__tar.type() == __nodeType) return;

    // End
    if (__tar.type() == node_t::END && __nodeType == node_t::MIDDLE)
    {
        _endNode.erase( _endNode.find( __tar._m_val ) );
    } else if (__nodeType == node_t::END || __nodeType == node_t::START_END)
    {
        _endNode.insert( &(*__tar) );
    }

    // Start
    if (__tar.type() == node_t::START && __nodeType == node_t::MIDDLE)
    {
        _startNode = nullptr;
        std::cerr << "Warning: startNode is nullptr now" << '\n';
    } else if (__nodeType == node_t::START || __nodeType == node_t::START_END)
    {
        if (_startNode != nullptr)
        {
            // 改变startNode
            if (_startNode->type == ato::node_t::START_END) _startNode->type = ato::node_t::END;
            else _startNode->type = ato::node_t::MIDDLE;
        }
        _startNode = &(*__tar);
    }

    __tar->type += __nodeType;
}/*
void Map::setTrapNode(iterator __trap)
{
    this->_trapNode=__trap.get();
}
*/
Map::iterator Map::expandNode( Map::iterator __from, val_t __edgeVal )
{
    Map::iterator newNode = this->insertNode( node_t::MIDDLE );
    this->insertEdge( __from, newNode, __edgeVal );
    return newNode;
}

Map::iterator Map::mergeNode( iterator __dest, iterator __src )
{
    this->setNodeType( __dest, __src._m_val->type.t );
    for (auto& i : __src->edge)
    {
        for (auto edge = i.second.begin(); edge != i.second.end(); )
        {
            auto cur = *(edge++);
            // if (cur->to() == __dest.get())
            // {
            //     this->eraseEdge( __src, __dest, i.first );
            //     continue;
            // }
            cur->rev()->setTo( __dest._m_val );
        }
    }
    for (auto& i : __src->revEdge)
    {
        for (auto edge = i.second.begin(); edge != i.second.end(); )
        {
            auto cur = *(edge++);
            // if (cur->to() == __dest.get())
            // {
            //     this->eraseEdge( __dest, __src, i.first );
            //     continue;
            // }
            cur->ori()->setTo( __dest._m_val );
        }
    }

    __dest->edge.insert( __src->edge.begin(), __src->edge.end() );
    __dest->revEdge.insert( __src->revEdge.begin(), __src->revEdge.end() );
    __src->edge.clear();
    __src->revEdge.clear();

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
        std::cerr << "Better not concat two empty Map" << '\n';
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
        std::cerr << "Warning: the startNode of left Map is nullptr" << '\n';
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
        std::cerr << "This Map is empty\n";
    }
    int cnt = 0;
    std::map<Node*, int> id;
    for (auto& i : _nodeList)
    {
        id.insert( { i, ++cnt } );
        std::cerr << "id-" << cnt << " : " << i << '\n';
    }
    for (auto& i : _nodeList)
    {
        std::cerr << "id-" << id[i];

        if (i->type == ato::node_t::START)
        {
            std::cerr << " [start]";
        }
        if (i->type == ato::node_t::END)
        {
            std::cerr << " [end]";
        }
        if (i->edge.empty())
        {
            std::cerr << '\n';
            continue;
        }
        std::cerr << " :\n";
        for (auto& j : i->edge)
        {
            if (j.second.empty()) continue;
            std::cerr << "\t" << j.first << " -> ";
            size_t tempCnt = 0;
            for (auto& k : j.second)
            {
                tempCnt++;
                if (tempCnt == j.second.size())
                {
                    std::cerr << id[k->to()];
                    break;
                }
                std::cerr << id[k->to()] << ", ";
            }
            std::cerr << '\n';
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


