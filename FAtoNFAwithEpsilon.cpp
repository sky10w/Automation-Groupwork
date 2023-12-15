#include <iostream>
#include <stack>
#include "basic_types/Map.hpp"
#include "FAtoNFAwithEpsilon.hpp"

const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::leftBracket = { '(' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::rightBracket = { ')' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::plus = { '+' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::concat = { '&' };
const ConvertFAtoNFAEpsilon::item_t ConvertFAtoNFAEpsilon::loop = { '*' };

// Fully Tested
std::list<ConvertFAtoNFAEpsilon::item_t> ConvertFAtoNFAEpsilon::_midToPost( const std::string& __re )
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
            if (__re[i - 1] == plus || __re[i - 1] == leftBracket)
                return;

            // 加入 &
            pushSign( concat );

        };


    for (int i = 0; i < __re.length(); ++i)
    {
        switch (__re[i])
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

            resList.push_back( __re[i] );
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

void ConvertFAtoNFAEpsilon::testMidToPost( const std::string& __re )
{
    auto list = _midToPost( __re );
    for (auto& i : list)
    {
        std::cout << i << ' ';
    }
}

ato::Map ConvertFAtoNFAEpsilon::convert( const std::string& __re )
{
    auto itemList = _midToPost( __re );

    std::stack<std::pair<item_t, ato::Map>> numStk;

    for (int i = 0; auto & item : itemList)
    {
        if (item == '0' || item == '1')
        {
            ato::Map tempMp;
            tempMp.insertNode( ato::node_t::START );
            tempMp.insertNode( ato::node_t::END );
            tempMp.insertEdge( tempMp.begin(), *( tempMp.last().begin() ), item );
            numStk.push( { item , tempMp } );

        } else if (item == '*')
        {
            auto tar = numStk.top();
            auto& mp = tar.second;
            mp.insertEdge( *( mp.last().begin() ), mp.begin(), ato::EPSILON );
        } else if (item == '+')
        {
            // 结果中后部的结点
            auto tar1 = numStk.top();
            numStk.pop();
            // 结果中前部的结点
            auto tar2 = numStk.top();
            ato::Map tempMp;

        }


    }
    return ato::Map();
}

