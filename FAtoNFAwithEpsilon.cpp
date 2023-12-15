#include <iostream>
#include <stack>
#include "basic_types/Map.hpp"
#include "FAtoNFAwithEpsilon.hpp"

const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::leftBracket = { '(' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::rightBracket = { ')' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::plus = { '+' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::concat = { '&' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::loop = { '*' };

std::list<ConvertFAtoNFAEpsilon::item_t> ConvertFAtoNFAEpsilon::_midToPost( const std::string& __fa )
{
    // item_t tempList;
    std::stack<item_t> signStk;
    std::list<item_t> resList;

    std::map<item_t, int> seq = {
        {plus, 0},
        {concat, 1},
        {loop, 2}
    };
    auto pushSign = [&]( const item_t& __sign )
        {
            while (!signStk.empty())
            {
                if (seq[signStk.top()] > seq[__sign])
                {
                    if (signStk.top() == leftBracket)
                    {
                        break;
                    }
                    resList.push_back( signStk.top() );
                    signStk.pop();
                } else
                {
                    break;
                }
            }

            signStk.push( __sign );
        };

    auto pushConcat = [&]( int i )
        {
            // 不能是第一个字符
            if (i == 0)
                return;

            // 前一个字符不是 + 或 (
            if (__fa[i - 1] == plus || __fa[i - 1] == leftBracket)
                return;

            // 加入 &
            pushSign( concat );

        };


    for (int i = 0; i < __fa.length(); ++i)
    {
        switch (__fa[i])
        {
        case '(':
            pushConcat( i );
            signStk.push( leftBracket );
            break;

        case ')':
            if (signStk.empty())
            {
                throw std::runtime_error( "The brackets don\'t match" );
            }

            while (signStk.top() != leftBracket)
            {
                if (signStk.empty())
                {
                    throw std::runtime_error( "The brackets don\'t match" );
                }
                resList.push_back( signStk.top() );
                signStk.pop();
            }

            // pop out the left bracket
            if (signStk.empty())
            {
                throw std::runtime_error( "The brackets don\'t match" );
            }
            signStk.pop();
            break;

        case '*':
            pushSign( loop );
            break;

        case '+':
            pushSign( plus );
            break;

        default:
            pushConcat( i );

            resList.push_back( __fa[i] );
            break;
        }
    }

    while (!signStk.empty())
    {
        resList.push_back( signStk.top() );
        signStk.pop();
    }

    return resList;
}

void ConvertFAtoNFAEpsilon::testMidToPost( const std::string& __fa )
{
    auto list = _midToPost( __fa );
    for (auto& i : list)
    {
        std::cout << i << ' ';
    }
}

ato::Map ConvertFAtoNFAEpsilon::convert( const std::string& __fa )
{
    auto itemList = _midToPost( __fa );

    std::stack<std::pair<item_t, int>> numStk;
    std::vector<ato::Map> mapVec;

    for (int i = 0; auto & item : itemList)
    {
        if (item == '0' || item == '1')
        {
            numStk.push( { item , ++i } );
            mapVec.push_back( ato::Map() );
        } else if (item == '*')
        {
            auto tar = numStk.top();
        }


    }
    return ato::Map();
}

