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
            while (seq[signStk.top()] > seq[__sign])
            {
                if (signStk.top() == leftBracket || signStk.empty())
                {
                    return;
                }
                resList.push_front( signStk.top() );
                signStk.pop();
                if (signStk.empty())
                {
                    return;
                }
            }
            signStk.push( __sign );
        };


    for (int i = 0; i < __fa.length(); ++i)
    {
        switch (__fa[i])
        {
        case '(':
            signStk.push( leftBracket );
            break;

        case ')':
            while (signStk.top() != leftBracket)
            {
                if (signStk.empty())
                {
                    throw std::runtime_error( "The brackets don\'t match" );
                }
                resList.push_front( signStk.top() );
                signStk.pop();
            }

            // pop out the left bracket
            signStk.pop();
            break;

        case '*':
            pushSign( loop );
            break;

        case '+':
            pushSign( plus );
            break;

        default:
            if (!resList.empty())
            {
                pushSign( concat );
            }
            resList.push_back( __fa[i] );
            break;
        }
    }

    return resList;
}

void ConvertFAtoNFAEpsilon::testMidToPost( const std::string& __fa )
{
    auto list = _midToPost( __fa );
    for (auto& i : list)
    {
        if (i == concat)
        {
            continue;
        }
        std::cout << i << ' ';
    }
}

ato::Map ConvertFAtoNFAEpsilon::convert( const std::string& __fa )
{
    return ato::Map();
}

