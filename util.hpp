#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include "basic_types/Map.hpp"
#include <queue>

ato::Map::iterator_set e_closure( ato::Map::iterator __iter );
ato::Map::iterator_set e_closure( ato::Map::iterator_set __iterSet );
ato::Map::iterator_set set_next( ato::val_t __val, ato::Map::iterator_set __set );


#endif
