#ifndef __RE_TO_NFAWITHEPSILON_HPP__
#define __RE_TO_NFAWITHEPSILON_HPP__

#include "basic_types/Map.hpp"
#include <iostream>
#include <stack>
#include <list>

class ConvertREtoNFAEpsilon
{
public:
    using val_t = ato::val_t;
private:
    // 各个符号
    static const val_t leftBracket;
    static const val_t rightBracket;
    static const val_t plus;
    static const val_t concat;
    static const val_t loop;

    // 将中缀表达式转换为后缀表达式，便于后续操作
    std::list<val_t> _midToPost( const std::string& __re );

public:
    ConvertREtoNFAEpsilon();
    // 仅测试用
    void testMidToPost( const std::string& __re );

    // 输入RE，返回一个带空转移的NFA
    ato::Map convert( const std::string& __re );
};

#endif