#ifndef __FA_TO_NFAWITHEPSILON_HPP__
#define __FA_TO_NFAWITHEPSILON_HPP__

#include "basic_types/Map.hpp"
#include <stack>
#include <list>

class ConvertFAtoNFAEpsilon
{
public:
    using item_t = ato::val_t;

private:
    // 各个符号
    static const item_t leftBracket;
    static const item_t rightBracket;
    static const item_t plus;
    static const item_t concat;
    static const item_t loop;

    // 将中缀表达式转换为后缀表达式，便于后续操作
    std::list<item_t> _midToPost( const std::string& __re );

public:
    // 仅测试用
    void testMidToPost( const std::string& __re );

    // 输入FA，返回一个带空转移的NFA
    ato::Map convert( const std::string& __re );
};

#endif