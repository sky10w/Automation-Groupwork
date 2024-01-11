#include "DFA-output.hpp"



void printDFA( const ato::Map& __dfa, std::ostream& __ost )
{
    std::vector<ato::Map::iterator> set;
    int cnt = 0;
    std::map<ato::Map::iterator, int> mp;
    set.push_back( {} );
    for (auto& i : __dfa.all())
    {
        set.push_back( i );
        mp.insert( { i, set.size() - 1 } );
    }

    // print Headline
    __ost << std::setw( 4 ) << ' ' << " | "
        << std::setw( 4 ) << '0' << " | "
        << std::setw( 4 ) << '1' << '\n';

    __ost << std::setw( 4 ) << "----" << "-|-"
        << std::setw( 4 ) << "----" << "-|-"
        << std::setw( 4 ) << "----" << '\n';
    for (int i = 1; i < set.size(); i++)
    {
        auto temp = std::string( "q" ) + std::to_string( i );
        if (set[i].type() == ato::node_t::START)
        {
            temp.insert( 0, "#" );
        } else if (set[i].type() == ato::node_t::END)
        {
            temp.insert( 0, "*" );
        }
        auto n0 = set[i].next( '0' ).begin().operator*();
        auto n1 = set[i].next( '1' ).begin().operator*();
        auto to0 = std::string( "q" ) + std::to_string( mp[n0] );
        auto to1 = std::string( "q" ) + std::to_string( mp[n1] );
        __ost << std::setw( 4 ) << temp << " | "
            << std::setw( 4 ) << to0 << " | "
            << std::setw( 4 ) << to1 << '\n';
    }
}

void toDot( const ato::Map& __dfa, std::ostream& __ost )
{
    // Init
    __ost << "strict digraph G {" << '\n'
        << "rankdir = LR;" << '\n'
        << "node[shape=circle]" << '\n'
        << "edge[arrowhead=vee]" << '\n';
    int cnt = 0;
    std::map<ato::Map::iterator, bool> vis;
    std::map<ato::Map::iterator, int> id;
    for (auto& i : __dfa.all())
    {
        vis.insert( { i, false } );
        id.insert( { i, ++cnt } );
    }
    __ost << "s -> q" << id[__dfa.begin()] << '\n';
    for (auto& i : __dfa.all())
    {
        if (i.type() == ato::node_t::END)
            __ost << "q" << id[i] << "[shape=doublecircle]" << '\n';
    }

    std::queue<ato::Map::iterator> q;
    q.push( __dfa.begin() );
    while (!q.empty())
    {
        auto cur = q.front();
        vis[cur] = true;
        q.pop();
        auto to0 = cur.next( '0' ).begin().operator*();
        auto to1 = cur.next( '1' ).begin().operator*();
        if (vis[to0] == false)
        {
            q.push( to0 );
            vis[to0] = true;
        }
        if (vis[to1] == false)
        {
            q.push( to1 );
            vis[to1] = true;
        }
        __ost << "q" << id[cur] << " -> q" << id[to0] << "[label=\"0\"]" << '\n'
            << "q" << id[cur] << " -> q" << id[to1] << "[label=\"1\"]" << '\n';
    }

    __ost << '}' << '\n';
    // system( "dot -Tpng graph.dot -o graph.png" );
}
