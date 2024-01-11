#include "DFA-minimization.hpp"
#include<cstring>
const int N = 100;//点上限
const int M = 4000;//边上限
int h[100000];//点的坐标由N*a+b得来 这里尽量开大
int e[M];
int ne[M];
int cnt = 0;
int st[M] = { 0 };
int  flag[N][N] = { 0 };
void dfs( int t )
{

    for (int i = h[t];i != -1;i = ne[i])
    {//及其所有关联边
        int j = e[i];
        //std::cout<<j/N<<' '<<j%N<<std::endl;
        if (st[j]) continue;
        flag[j / N][j % N] = 1;
        st[j] = 1;
        dfs( j );
    }
}
//11111
std::map<ato::Map::iterator, int> get;
void add( int a, int b )
{
    //std::cout<<"add edge:"<<std::endl;
    //std::cout<<a/N<<' '<<a%N<<std::endl;
    //std::cout<<b/N<<' '<<b%N<<std::endl;
    e[cnt] = b;
    ne[cnt] = h[a];
    h[a] = cnt++;
}
inline int getid( ato::Map::iterator x, ato::Map::iterator y )
{
    return N * get[x] + get[y];
}
void minimize( ato::Map& dfa )
{

    memset( h, -1, sizeof h );
    get.clear();

    memset( flag, 0, sizeof flag );
    int size = dfa.all().size();

    int idx = 0;

    for (auto x : dfa.all())
    {
        get[x] = idx++;
    }

    //step1
    for (auto x : dfa.all())
    {
        if (x.type() == node_t::END) continue;
        for (auto y : dfa.all())
        {
            //std::cout<<get[y]<<std::endl;
            if (y.type() != node_t::END) continue;
            if (get[x] > get[y])
                flag[get[y]][get[x]] = 1;
            else
                flag[get[x]][get[y]] = 1;//先标记非终结状态和终结状态的状态对
        }
    }

    // for (int j = 0;j <= 2;j++)
    // {
    //     for (int i = 0;i <= 2;i++)
    //     {
    //         if (j <= i) continue;
    //         std::cout << flag[i][j] << ' ';
    //     }
    //     std::cout << std::endl;
    // }
    //std::cout<<h[11]<<std::endl;
    //step2
    idx = 0;
    int idx2 = 0;
    for (auto& x : dfa.all())
    {
        for (auto& y : dfa.all())
        {


            if (get[y] <= get[x]) continue;//保证(qx,qy)(qy,qx)只会访问一个
            //std::cout<<get[x]<<' '<<get[y]<<std::endl;
            idx++;
            // if (flag[get[x]][get[y]]) continue;
            auto x0 = *x.next( '0' ).begin();
            auto y0 = *y.next( '0' ).begin();
            auto x1 = *x.next( '1' ).begin();
            auto y1 = *y.next( '1' ).begin();
            bool x0_empty = x.next( '0' ).size();
            bool y0_empty = y.next( '0' ).size();
            bool x1_empty = x.next( '1' ).size();
            bool y1_empty = y.next( '1' ).size();
            if (get[x0] >= get[y0]) std::swap( x0, y0 ), std::swap( x0_empty, y0_empty );
            if (get[x1] >= get[y1]) std::swap( x1, y1 ), std::swap( x1_empty, y1_empty );
            if ((flag[get[x0]][get[y0]]) || (flag[get[x1]][get[y1]]))
            {//DFA这个返回的iter set应该只有一个元素
                //std::cout<<get[x]<<' '<<get[y]<<std::endl;
                flag[get[x]][get[y]] = 1;//可区分则标记该状态
                memset( st, 0, sizeof st );
                dfs( getid( x, y ) );
                //std::cout<<"123456789"<<std::endl;
            } else
            {

                if (flag[get[x0]][get[y0]] == 0)
                {//不可区分则关联
                    //add( getid( x, y ), getid( x0, y0 ) );
                    add( getid( x0, y0 ), getid( x, y ) );
                }
                if (flag[get[x1]][get[y1]] == 0)
                {
                    //add( getid( x, y ), getid( x1, y1 ) );
                    add( getid( x1, y1 ), getid( x, y ) );
                }
            }

            // for (int j = 0;j <= 8;j++)
            // {
            //     for (int i = 0;i <= 8;i++)
            //     {
            //         //if(j<=i) continue;
            //         std::cout << flag[i][j] << ' ';
            //     }
            //     std::cout << std::endl;
            // }
        }

    }
    std::cerr << "----------------" << '\n';
    for (int j = 0;j <= dfa.all().size() - 1;j++)
    {
        for (int i = 0;i <= dfa.all().size();i++)
        {
            if (j <= i) continue;
            std::cerr << flag[i][j] << ' ';
        }
        std::cerr << std::endl;
    }

    std::vector< Map::iterator_set > identical;
    identical.clear();
    for (auto& x : dfa.all())
    {
        for (auto& y : dfa.all())
        {
            if (get[y] <= get[x]) continue;//保证(qx,qy)(qy,qx)只会访问一个

            if (!flag[get[x]][get[y]])
            {//如果不可区分,记录不可区分状态
                idx2++;
                //std::cout<<get[x]<<' '<<get[y]<<std::endl;
                if (identical.size() == 0)
                {
                    Map::iterator_set tmp;
                    tmp.insert( x );
                    tmp.insert( y );
                    identical.push_back( tmp );
                } else
                    for (auto& z : identical/*直接遍历 效率好低 不过无所谓了 数据太小*/)
                    {
                        if (z.find( x ) != z.end() || z.find( y ) != z.end())
                        {
                            z.insert( y );
                            z.insert( x );
                            break;//找到的话就塞进去
                        } else if (identical.back() == z)
                        {//找不到就新建
                            Map::iterator_set tmp;
                            tmp.insert( x );
                            tmp.insert( y );
                            identical.push_back( tmp );
                        }
                    }
            }
        }
    }
    for (auto& x : identical)
    {
        //std::cout<<x.size()<<std::endl;
        // node_t tempType = node_t::MIDDLE;
        while (x.size() > 1)
        {
            auto a = x.begin();
            auto b = --x.end();

            //std::cout << get[*a] << ' ' << get[*b] << std::endl;

            // auto tempSave = *b;
            // tempType += b.operator*().type().get();
            if (b.operator*().type() == ato::node_t::MIDDLE) std::swap( a, b );
            dfa.mergeNode( *a, *b );//最后的合并
            x.erase( b );
        }
        // dfa.setNodeType( a.operator*(), tempType.get() );
    }
    //step3,似乎不需要了


}















/*



void minimize2( ato::Map& __dfa )
{
    __dfa.outputTest();
    std::map<NodePairCmp::pair, NodePairCmp::pair, NodePairCmp> mp;
    std::map<NodePairCmp::pair, bool, NodePairCmp> mark;
    std::map<ato::Map::iterator, ato::Map::iterator> fa;
    std::map<ato::Map::iterator, ato::Map::iterator_set> finalSet;


    auto full = __dfa.all();
    for (auto i : full)
    {
        fa.insert( { i, i } );
    }
    for (auto i = full.begin(); i != full.end(); i++)
    {
        for (auto j = std::next( i ); j != full.end(); j++)
        {
            if (j == full.end()) break;
            if (((*i).type() == ato::node_t::END && (*j).type() != ato::node_t::END)
                || ((*j).type() == ato::node_t::END && (*i).type() != ato::node_t::END))
            {
                mark.insert( { { *i, *j }, true } );
            } else
            {
                mark.insert( { { *i, *j }, false } );
            }
        }
    }

    for (auto i : __dfa.dest())
    {
        for (auto j : full)
        {
            if (j.type() == ato::node_t::END) continue;
            mark.insert( { {i,j},true } );
            std::cout << "Insert mark " << i.get() << " and " << j.get() << '\n';
        }
    }
    for (auto i = full.begin(); i != full.end(); i++)
    {
        for (auto j = std::next( i ); j != full.end(); j++)
        {
            for (auto c : { '0', '1' })
            {
                auto nx0 = i.operator*().next( c ).begin().operator*();
                auto ny0 = j.operator*().next( c ).begin().operator*();
                if (nx0 == ny0) continue;
                if (mark[{ nx0, ny0 }] == true)
                {
                    auto tempA = *i, tempB = *j;
                    mark[{tempA, tempB}] = true;
                    std::cout << "Insert mark " << tempA.get() << " and " << tempB.get() << '\n';
                    while (mp.find( { tempA, tempB } ) != mp.end())
                    {
                        auto tempRes = *(mp.find( { tempA, tempB } ));
                        tempA = tempRes.second.first;
                        tempB = tempRes.second.second;
                        mark[{tempA, tempB}] = true;
                        std::cout << "Insert mark " << tempA.get() << " and " << tempB.get() << '\n';
                    }
                } else
                {
                    mp.insert( { {nx0, ny0},{*i, *j} } );
                }
            }
        }
    }

    for (auto& i : mark)
    {
        if (i.second == false)
        {
            auto x = i.first.first, y = i.first.second;
            fa[y] = x;
        }
    }

    for (auto& i : full)
    {
        auto ans = fa[i];
        while (ans != fa[ans])
        {
            ans = fa[ans];
        }
        auto findRes = finalSet.find( ans );
        if (findRes == finalSet.end())
        {
            finalSet.insert( { ans, {i} } );
        } else
        {
            findRes.operator*().second.insert( i );
        }
    }

    for (auto& i : finalSet)
    {
        node_t::_type tempType = ato::node_t::MIDDLE;
        auto tar = i.second.begin().operator*();
        for (auto j = std::next( i.second.begin() ); j != i.second.end(); j++)
        {
            if (j == i.second.end()) break;

            if (j.operator*().type() == ato::node_t::START_END)
            {
                __dfa.mergeNode( tar, j.operator*() );
                continue;
            }

            if (j.operator*().type() == ato::node_t::START)
            {
                if (tempType == ato::node_t::END) tempType = ato::node_t::START_END;
                else tempType = ato::node_t::START;
            }
            if (j.operator*().type() == ato::node_t::END)
            {
                if (tempType == ato::node_t::START) tempType = ato::node_t::START_END;
                else tempType = ato::node_t::END;
            }
            __dfa.mergeNode( tar, j.operator*() );
        }
        __dfa.setNodeType( tar, tempType );
    }


}

*/