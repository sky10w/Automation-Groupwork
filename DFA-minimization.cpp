#include "DFA-minimization.hpp"
#include<cstring>
const int N = 30;//点上限
const int M = 100;//边上限
int h[1000];//点的坐标由N*a+b得来 这里尽量开大
int e[M];
int ne[M];
int cnt = 0;
int st[M];
int  flag[N][N];
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
                flag[get[x]][get[y]] = 1;//先标记非终结状态和中介状态的状态对
        }
    }
    /*
    for(int i=0;i<=N;i++){
        for(int j=0;j<=N;j++){
            if(j<=i) continue;
            std::cout<<flag[i][j]<<' ';
        }
        std::cout<<std::endl;
    }*/
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
            if (flag[get[x]][get[y]]) continue;
            auto x0 = *x.next( '0' ).begin();
            auto y0 = *y.next( '0' ).begin();
            auto x1 = *x.next( '1' ).begin();
            auto y1 = *y.next( '1' ).begin();
            if (get[x0] >= get[y0]) std::swap( x0, y0 );
            if (get[x1] >= get[y1]) std::swap( x1, y1 );
            if (flag[get[x0]][get[y0]] || flag[get[x1]][get[y1]])
            {//DFA这个返回的iter set应该只有一个元素
                flag[get[x]][get[y]] = 1;//可区分则标记该状态
                memset( st, 0, sizeof st );
                dfs( getid( x, y ) );
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
            /*
            for(int i=0;i<=5;i++){
                for(int j=0;j<=5;j++){
                    if(j<=i) continue;
                    std::cout<<flag[i][j]<<' ';
                }
            std::cout<<std::endl;
            }*/
        }

    }
    /*
    for (int j = 0;j <= 5;j++)
    {
        for (int i = 0;i <= 5;i++)
        {
            if (j <= i) continue;
            std::cout << flag[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    */
    std::vector< std::set<Map::iterator> > identical;
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
                    std::set<Map::iterator> tmp;
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
                            std::set<Map::iterator> tmp;
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
        while (x.size() > 1)
        {
            auto a = x.begin();
            auto b = x.rbegin();
            //std::cout << get[*a] << ' ' << get[*b] << std::endl;
            dfa.mergeNode( *a, *b );//最后的合并
            x.erase( *b );
        }
    }
    //step3,似乎不需要了


}
