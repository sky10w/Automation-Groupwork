#ifndef __DFA_MINIMIZATION_HPP__
#define __DFA_MINIMIZATION_HPP__


#include"basic_types/Map.hpp"
#include<iostream>
#include<map>
#include<set>
#include<algorithm>
using namespace ato;

void add( int a, int b );

int getid( ato::Map::iterator x, ato::Map::iterator y );

void minimize( ato::Map& dfa );

struct NodePairCmp
{
    // using pair = std::pair<ato::Map::iterator, ato::Map::iterator>;
    struct pair
    {
        ato::Map::iterator first;
        ato::Map::iterator second;
        pair( ato::Map::iterator a, ato::Map::iterator b )
        {
            if (a.get() < b.get())
            {
                first = a, second = b;
                return;
            }
            first = b, second = a;
        }
    };

    bool operator()( const pair a, const pair b ) const
    {
        return (a.first == b.first) ? a.second < b.second : a.first < b.first;
    }

};

// void minimize2( ato::Map& __dfa );



#endif