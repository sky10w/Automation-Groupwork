#include "FAtoNFAwithEpsilon.hpp"

const ConvertREtoNFAEpsilon::item_t ConvertREtoNFAEpsilon::leftBracket = { '(' };
const ConvertREtoNFAEpsilon::item_t ConvertREtoNFAEpsilon::rightBracket = { ')' };
const ConvertREtoNFAEpsilon::item_t ConvertREtoNFAEpsilon::plus = { '+' };
const ConvertREtoNFAEpsilon::item_t ConvertREtoNFAEpsilon::concat = { '&' };
const ConvertREtoNFAEpsilon::item_t ConvertREtoNFAEpsilon::loop = { '*' };

// Fully Tested
std::list<ConvertREtoNFAEpsilon::item_t> ConvertREtoNFAEpsilon::_midToPost( const std::string& __re )
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
                std::cerr << "The brackets don\'t match\n";
            }

            while (signStk.top() != leftBracket)
            {
                if (signStk.empty())
                {
                    std::cerr << "The brackets don\'t match\n";
                }
                resList.push_back( signStk.top() );
                signStk.pop();
            }

            // pop out the left bracket
            if (signStk.empty())
            {
                std::cerr << "The brackets don\'t match\n";
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

ConvertREtoNFAEpsilon::ConvertREtoNFAEpsilon()
{
    std::cout << "Test\n";
}

void ConvertREtoNFAEpsilon::testMidToPost( const std::string& __re )
{
    auto list = _midToPost( __re );
    for (auto& i : list)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

ato::Map ConvertREtoNFAEpsilon::convert( const std::string& __re )
{
    auto itemList = _midToPost( __re );
    ato::Map mp;

    std::stack<ato::Map::iterator> startStk;
    std::stack<ato::Map::iterator> endStk;

    startStk.push( mp.insertNode( ato::node_t::START ) );
    endStk.push( mp.insertNode( ato::node_t::END ) );

    ato::Map::iterator pre = startStk.top();

    for (auto& item : itemList)
    {
        if (item == '0' || item == '1')
        {
            pre = mp.expandNode( pre, item );
        } else if (item == '*')
        {
            pre = mp.expandNode( pre, ato::EPSILON );
        }

    }
    return ato::Map();
}

// if (item == '0' || item == '1')
        // {
        //     ato::Map tempMp;
        //     tempMp.insertNode( ato::node_t::START );
        //     tempMp.insertNode( ato::node_t::END );
        //     // tempMp.insertEdge( tempMp.begin(), *( tempMp.last().begin() ), item );
        //     numStk.push( { item , tempMp } );

        // } else if (item == '*')
        // {
        //     auto tar = numStk.top();
        //     auto& mp = tar.second;
        //     // mp.insertEdge( *( mp.last().begin() ), mp.begin(), ato::EPSILON );
        // } else if (item == '+')
        // {
        //     // 结果中后部的结点
        //     auto tar1 = numStk.top();
        //     numStk.pop();
        //     // 结果中前部的结点
        //     auto tar2 = numStk.top();
        //     ato::Map tempMp;

        // }