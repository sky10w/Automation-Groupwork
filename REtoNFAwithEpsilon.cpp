#include "REtoNFAwithEpsilon.hpp"

const ConvertREtoNFAEpsilon::val_t ConvertREtoNFAEpsilon::leftBracket = { '(' };
const ConvertREtoNFAEpsilon::val_t ConvertREtoNFAEpsilon::rightBracket = { ')' };
const ConvertREtoNFAEpsilon::val_t ConvertREtoNFAEpsilon::plus = { '+' };
const ConvertREtoNFAEpsilon::val_t ConvertREtoNFAEpsilon::concat = { '&' };
const ConvertREtoNFAEpsilon::val_t ConvertREtoNFAEpsilon::loop = { '*' };

// Fully Tested
std::list<ConvertREtoNFAEpsilon::val_t> ConvertREtoNFAEpsilon::_midToPost( const std::string& __re )
{
    // item_t tempList;
    std::stack<val_t> signStk;
    std::list<val_t> resList;

    std::map<val_t, int> seq = {
        {plus, 0},
        {concat, 1},
        {loop, 2}
    };
    auto pushSign = [&]( const val_t& __sign )
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
{}

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

    for (auto& item : itemList)
    {
        if (item == '0' || item == '1')
        {
            startStk.push( mp.insertNode( ato::node_t::MIDDLE ) );
            endStk.push( mp.insertNode( ato::node_t::MIDDLE ) );
            mp.insertEdge( startStk.top(), endStk.top(), item );
        } else if (item == '*')
        {
            mp.insertEdge( endStk.top(), startStk.top(), ato::EPSILON );
            mp.insertEdge( startStk.top(), endStk.top(), ato::EPSILON );
        } else if (item == '&')
        {
            auto s1 = startStk.top();
            auto e1 = endStk.top();
            startStk.pop();
            endStk.pop();
            auto s2 = startStk.top();
            auto e2 = endStk.top();
            startStk.pop();
            endStk.pop();
            mp.insertEdge( e2, s1, ato::EPSILON );
            startStk.push( s2 );
            endStk.push( e1 );
        } else if (item == '+')
        {
            ato::Map::iterator ss[2], ee[2];
            for (int i : {0, 1})
            {
                ss[i] = startStk.top();
                ee[i] = endStk.top();
                startStk.pop();
                endStk.pop();
            }
            auto ns = mp.insertNode( ato::node_t::MIDDLE );
            auto ne = mp.insertNode( ato::node_t::MIDDLE );
            for (int i : {0, 1})
            {
                mp.insertEdge( ns, ss[i], ato::EPSILON );
                mp.insertEdge( ee[i], ne, ato::EPSILON );
            }
            startStk.push( ns );
            endStk.push( ne );
        }
    }
    if (startStk.size() > 1 || endStk.size() > 1)
    {
        std::cout << "Invalid RE" << '\n';
    }
    mp.insertEdge( mp.insertNode( ato::node_t::START ), startStk.top(), ato::EPSILON );
    mp.insertEdge( endStk.top(), mp.insertNode( ato::node_t::END ), ato::EPSILON );

    return mp;
}