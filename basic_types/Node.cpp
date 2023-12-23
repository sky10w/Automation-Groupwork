#include "Node.hpp"

BASIC_NAMESPACE_BEGIN



Node::Node( id_t __id, node_t __type )
    : id( __id )
    , type( __type )
    , edge()
    , revEdge()
{}
Node::Node( const Node& __src )
    : id( __src.id )
    , type( __src.type )
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
    auto temp = new Edge_t( this, __to );
    // Insert an Edge into this Node
    this->_insertEdge( temp, __val );
    // Insert a revEdge into target Node
    __to->_insertRevEdge( temp->rev(), __val );
}
void Node::insertRevEdge( Node* __to, val_t __val )
{
    auto temp = new RevEdge_t( this, __to );
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
        if (res2.second == false)
        {
            std::cerr << "A repeated Edge from\t" << __ori->rev()->to() << " to " << __ori->to() << " inserted" << '\n';
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
        if (res2.second == false)
        {
            std::cerr << "A repeated RevEdge from\t" << __rev->ori()->to() << " to " << __rev->to() << " inserted" << '\n';
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

    auto temp = Edge_t::generateTemp( __to );
    auto tar = this->edge[__val].find( &temp );
    if (tar == this->edge[__val].end())
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    RevEdge_t* tarRev = ( *tar )->rev();
    this->_eraseEdge( *tar, __val );
    __to->_eraseRevEdge( tarRev, __val );
}
void Node::eraseRevEdge( Node* __to, val_t __val )
{
    if (this->revEdge.find( __val ) == this->revEdge.end())
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }

    auto temp = RevEdge_t::generateTemp( __to );
    auto tar = this->revEdge[__val].find( &temp );

    if (tar == this->revEdge[__val].end())
    {
        std::cerr << "Cannot erase a non-exist Edge" << '\n';
        return;
    }
    Edge_t* tarOri = ( *tar )->ori();
    this->_eraseRevEdge( *tar, __val );
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


bool EdgeCmp::operator()( Edge_t* __a, Edge_t* __b ) const
{
    return __a->to() < __b->to();
}
bool RevEdgeCmp::operator()( RevEdge_t* __a, RevEdge_t* __b ) const
{
    return __a->to() < __b->to();
}

BASIC_NAMESPACE_END

