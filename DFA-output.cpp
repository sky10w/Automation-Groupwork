#include "DFA-output.hpp"



void printDFA( const ato::Map& __dfa )
{
    std::vector<ato::Map::iterator> set;
    int cnt = 0;
    std::map<ato::Map::iterator, int> mp;
    for (auto& i : __dfa.all())
    {
        set.push_back( i );
        mp.insert( { i, set.size() - 1 } );
    }

    // print Headline
    std::cout << std::setw( 4 ) << ' ' << " | "
        << std::setw( 4 ) << '0' << " | "
        << std::setw( 4 ) << '1' << '\n';

    std::cout << std::setw( 4 ) << "----" << "-|-"
        << std::setw( 4 ) << "----" << "-|-"
        << std::setw( 4 ) << "----" << '\n';
    for (int i = 0; i < set.size(); i++)
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
        std::cout << std::setw( 4 ) << temp << " | "
            << std::setw( 4 ) << to0 << " | "
            << std::setw( 4 ) << to1 << '\n';
    }
}