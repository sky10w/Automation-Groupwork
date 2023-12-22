#include "Node.hpp"

BASIC_NAMESPACE_BEGIN

Node::Node( id_t __id, node_t __type )
    : id( __id )
    , type( __type )
    , edge()
    , revEdge()
{}


/**
 *  Find next Nodes
*/
Edge_set Node::next( val_t __val )
{
    if (this->edge.find( __val ) == this->edge.end())
    {
        std::cerr << "No Edge Found" << '\n';
        return Edge_set();
    }
    return this->edge[__val];
}

RevEdge_set Node::revNext( val_t __val )
{
    if (this->revEdge.find( __val ) == this->revEdge.end())
    {
        std::cerr << "No Edge Found" << '\n';
        return RevEdge_set();
    }
    return this->revEdge[__val];
}


/**
 * Edge insert & erase
*/
void Node::insertEdge( Node* __to, val_t __val )
{
    auto temp = new Edge( this, __to );
    // Insert an Edge into this Node
    this->_insertEdge( temp, __val );
    // Insert a revEdge into target Node
    __to->_insertRevEdge( temp->rev(), __val );
}
void Node::insertRevEdge( Node* __to, val_t __val )
{
    auto temp = new RevEdge( this, __to );
    this->_insertRevEdge( temp, __val );
    __to->_insertEdge( temp->ori(), __val );
}
void Node::_insertEdge( Edge_t* __ori, val_t __val )
{
    auto res = this->edge.find( __val );
    if (res == this->edge.end())
    {
        this->edge.insert( { __val, { __ori } } );
    } else
    {
        auto res2 = this->edge[__val].insert( __ori );
        if (res2.second == true)
        {
            std::cerr << "A repeated Edge inserted" << '\n';
        }
    }
}
void Node::_insertRevEdge( RevEdge_t* __rev, val_t __val )
{
    auto res = this->revEdge.find( __val );
    if (res == this->revEdge.end())
    {
        this->revEdge.insert( { __val, { __rev } } );
    } else
    {
        auto res2 = this->revEdge[__val].insert( __rev );
        if (res2.second == true)
        {
            std::cerr << "A repeated Edge inserted" << '\n';
        }
    }
}

void Node::eraseEdge( Node* __to, val_t __val )
{
    if (this->edge.find( __val ) == this->edge.end())
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    Edge_t* tar = nullptr;
    for (auto& i : this->edge[__val])
    {
        if (i->to() == __to)
        {
            tar = i;
        }
    }
    if (tar == nullptr)
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    RevEdge_t* tarRev = tar->rev();
    this->_eraseEdge( tar, __val );
    __to->_eraseRevEdge( tarRev, __val );
}
void Node::eraseRevEdge( Node* __to, val_t __val )
{
    if (this->revEdge.find( __val ) == this->revEdge.end())
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    RevEdge_t* tar = nullptr;
    for (auto& i : this->revEdge[__val])
    {
        if (i->to() == __to)
        {
            tar = i;
        }
    }
    if (tar == nullptr)
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    Edge_t* tarOri = tar->ori();
    this->_eraseRevEdge( tar, __val );
    __to->_eraseEdge( tarOri, __val );
}
void Node::_eraseEdge( Edge_t* __ori, val_t __val )
{
    if (this->edge.find( __val ) == this->edge.end())
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    auto tar = this->edge[__val].find( __ori );
    if (tar == this->edge[__val].end())
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    delete ( *tar );
    this->edge[__val].erase( tar );
}
void Node::_eraseRevEdge( RevEdge_t* __rev, val_t __val )
{
    if (this->revEdge.find( __val ) == this->revEdge.end())
    {
        std::cerr << "Cannot erase a non-exist RevEdge" << '\n';
        return;
    }
    auto tar = this->revEdge[__val].find( __rev );
    if (tar == this->revEdge[__val].end())
    {
        std::cerr << "Cannot erase a non-exist RevEdge" << '\n';
        return;
    }
    delete ( *tar );
    this->revEdge[__val].erase( tar );
}

void Node::clear()
{
    for (auto i = edge.begin(); i != edge.end(); i++)
    {
        auto& tar = ( *i ).second;
        for (auto j = tar.begin(); j != tar.end(); j++)
        {
            auto& tarNode = *j;
            tarNode->to()->_eraseRevEdge( tarNode->rev(), ( *i ).first );
            delete ( *j );
            tar.erase( j );
        }
    }
}

const Node& Node::operator=( const Node& __rhs )
{
    this->edge = __rhs.edge;
    this->revEdge = __rhs.revEdge;
    this->id = __rhs.id;
    this->type = __rhs.type;
    return *this;
}
Node::~Node()
{
    this->clear();
}

// // Edge Container

// void EdgeContainer::_access()
// {
//     if (this->empty())
//     {
//         throw std::runtime_error( "Cannot get access to a nullptr" );
//     }
// }

// EdgeContainer::EdgeContainer( Node* __from, Node* __to )
//     :_M_edge( new Edge_t( __from, __to ) )
// {}

// EdgeContainer::EdgeContainer( EdgeContainer& __rhs )
//     : _M_edge( __rhs._M_edge )
// {
//     __rhs._M_edge = nullptr;
// }

// EdgeContainer::EdgeContainer( EdgeContainer&& __rhs )
//     : _M_edge( __rhs._M_edge )
// {
//     __rhs._M_edge = nullptr;
// }

// EdgeContainer::EdgeContainer( Edge_t* __val )
//     : _M_edge( __val )
// {}

// bool EdgeContainer::empty()
// {
//     return _M_edge == nullptr;
// }

// RevEdgeContainer EdgeContainer::rev()
// {
//     _access();
//     return _M_edge->rev();
// }

// Node* EdgeContainer::to()
// {
//     _access();
//     return _M_edge->to();
// }

// EdgeContainer::~EdgeContainer()
// {
//     if (_M_edge != nullptr)
//     {
//         delete _M_edge;
//         _M_edge = nullptr;
//     }
// }


// // Rev Container

// void RevEdgeContainer::_access()
// {
//     if (this->empty())
//     {
//         throw std::runtime_error( "Cannot get access to a nullptr" );
//     }
// }

// RevEdgeContainer::RevEdgeContainer( RevEdgeContainer& __rhs )
//     : _M_edge( __rhs._M_edge )
// {
//     __rhs._M_edge = nullptr;
// }

// RevEdgeContainer::RevEdgeContainer( RevEdgeContainer&& __rhs )
//     :_M_edge( __rhs._M_edge )
// {
//     __rhs._M_edge = nullptr
// }

// RevEdgeContainer::RevEdgeContainer( RevEdge_t* __edge )
//     : _M_edge( __edge )
// {}

// bool RevEdgeContainer::empty()
// {
//     return _M_edge == nullptr;
// }

// EdgeContainer RevEdgeContainer::ori()
// {
//     _access();
//     return EdgeContainer( _M_edge->ori() );
// }

// Node* RevEdgeContainer::to()
// {
//     _access();
//     return _M_edge->to();
// }

// RevEdgeContainer::~RevEdgeContainer()
// {
//     if (_M_edge != nullptr)
//     {
//         delete _M_edge;
//         _M_edge = nullptr;
//     }
// }

BASIC_NAMESPACE_END


