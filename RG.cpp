#include"RG.hpp"

const char trap = 'X';
void RG::DFAtoRG( Map& DFA )
{
    P.clear();
    T.push_back( '0' );
    T.push_back( '1' );
    Map::iterator it;
    it = DFA.begin();
    V[it] = 'S';
    Map::iterator_set Alliterset = DFA.all();

    int countfalp = 0;

    for (auto& x : Alliterset)
    {
        if (x.type() == node_t::END) continue;
        if (x == *x.next( '0' ).begin() && x == *x.next( '1' ).begin())
            V[x] = trap;
    }
    for (auto& x : Alliterset)
    {
        if (V.find( x ) != V.end() && V[x] == trap || V[x] == 'S') continue;
        V[x] = ('A' + countfalp);
        countfalp++;
    }

    for (auto& x : Alliterset)
    {

        if (V[x] == trap) continue;
        string strstart;
        strstart += V[x];
        strstart += "->";
        string strtemp = strstart;
        auto temp1 = *(x.next( '0' ).begin());
        auto temp2 = *(x.next( '1' ).begin());
        Map::iterator_set tempset;
        if (V[temp1] != trap)
        {
            strtemp += "0";
            strtemp += V[temp1];

        }
        if (V[temp2] != trap)
        {
            if (strtemp != strstart)
                strtemp += "|";
            strtemp += "1";
            strtemp += V[temp2];
        }
        if (x.type() == node_t::END)
        {
            if (strtemp != strstart)
                strtemp += "|";
            strtemp += "ε";
        }
        P.push_back( strtemp );
        /*
        for (iterator = tempset.begin(); iterator != tempset.end(); iterator++)
        {
            tempstr2.clear();
            tempstr = tempstr + "|";
            tempstr2 = V[*iterator];
            tempstr = tempstr + tempstr2;
        }
        P.insert(P.end(), tempstr);


        tempset = iter->next( '1' );

        tempstr.clear();
        tempstr2.clear();
        tempstr = V[*iter];
        tempstr = tempstr + "->1";
        tempstr2 = V[*iterator];
        tempstr = tempstr + tempstr2;


        for (auto iterator = tempset.begin(); iterator != tempset.end(); iterator++)
        {
            tempstr2.clear();
            tempstr = tempstr + "|";
            tempstr2 = V[*iterator];
            tempstr = tempstr + tempstr2;
        }
        */
        /*
        tempset.clear();
        tempset = iter->next( '1' );
        for (iterator = tempset.begin(); iterator != tempset.end(); iterator++)
        {
            tempstr.clear();
            tempstr2.clear();
            tempstr = V[*iter];
            tempstr = tempstr + "->1";
            tempstr2 = V[*iterator];
            tempstr = tempstr + tempstr2;
            P.insert( P.end(), tempstr );
        }
        */

    }

    return;
}

void RG::printRG( ostream& __ost )
{
    __ost << "RG = {V,T,S,P}" << endl;

    __ost << "V = {";
    map<Map::iterator, char>::iterator it1;
    for (it1 = V.begin(); it1 != V.end(); it1++)
    {
        if (it1->second == trap) continue;
        if (it1 != V.begin()) __ost << ',';
        __ost << it1->second;
    }
    __ost << "}" << endl;

    __ost << "T = {";
    vector<char>::iterator it2;
    for (it2 = T.begin(); it2 != T.end(); it2++)
    {
        if (it2 != T.begin()) __ost << ',';

        __ost << *it2;
    }
    __ost << "}" << endl;

    __ost << "S = " << 'S' << endl;

    __ost << "P = ";
    for (auto x : P)
    {
        __ost << x << endl;
    }
    return;
}