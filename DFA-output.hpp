#ifndef __DFA_OUTPUT_HPP__
#define __DFA_OUTPUT_HPP__

#include "basic_types/Map.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <fstream>


void printDFA( const ato::Map& __dfa );

void toDot( const ato::Map& __dfa );

#endif