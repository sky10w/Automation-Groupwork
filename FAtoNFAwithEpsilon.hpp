#ifndef __FA_TO_NFAWITHEPSILON_HPP__
#define __FA_TO_NFAWITHEPSILON_HPP__

#include "basic_types/Map.hpp"
#include <stack>

class ConvertFAtoNFAEpsilon
{
public:
    using item_t = ato::val_t;

private:
    static const item_t leftBracket;
    static const item_t rightBracket;
    static const item_t plus;
    static const item_t concat;
    static const item_t loop;
    std::list<item_t> _midToPost( const std::string& __fa );

public:
    void testMidToPost( const std::string& __fa );
    ato::Map convert( const std::string& __fa );
};

#endif