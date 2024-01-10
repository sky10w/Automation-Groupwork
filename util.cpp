#include "util.hpp"



ato::Map::iterator_set e_closure( ato::Map::iterator __iter )
{
    ato::Map::iterator_set res = { __iter };
    std::queue<ato::Map::iterator> q;
    q.push( __iter );

    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        if (cur.next( ato::EPSILON ).empty())
            continue;
        auto temp = cur.next( ato::EPSILON );
        for (auto i : temp)
        {
            auto insRes = res.insert( i );
            if (insRes.second == false)
                continue;
            q.push( i );
        }
    }
    return res;
}

ato::Map::iterator_set e_closure( ato::Map::iterator_set __iterSet )
{
    ato::Map::iterator_set res;
    for (auto j : __iterSet)
    {
        auto temp = e_closure( j );
        res.insert( temp.begin(), temp.end() );
    }
    return res;
}


ato::Map::iterator_set set_next( ato::val_t __val, ato::Map::iterator_set __set )
{
    ato::Map::iterator_set res;
    for (auto i : __set)
    {
        for (auto j : i.next( __val ))
        {
            res.insert( j );
        }
    }
    return res;
}

ato::Map easyDFAGenerator( int __pts, std::vector<std::pair<int, int>> __form, std::vector<int> __end )
{
    ato::Map mp;
    std::vector<ato::Map::iterator> pts;
    for (int i = 0; i < __pts; i++)
    {
        pts.push_back( mp.insertNode( ato::node_t::MIDDLE ) );
    }
    mp.setNodeType( pts[0], ato::node_t::START );
    for (auto& i : __end)
    {
        mp.setNodeType( pts[i], ato::node_t::END );
    }
    for (int i = 0; i < __form.size(); i++)
    {
        mp.insertEdge( pts[i], pts[__form[i].first], '0' );
        mp.insertEdge( pts[i], pts[__form[i].second], '1' );
    }

    return mp;
}
