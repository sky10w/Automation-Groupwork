#include"RG.hpp"


void RG::DFAtoRG( Map DFA )
{
    T.insert( T.end(), 0 );
    T.insert( T.end(), 1 );
    Map::iterator it;
    it = DFA.begin();
    V[it] = 'S';
    Map::iterator_set Alliterset = DFA.all();

    int countfalp = 0;

    for (auto iter = Alliterset.begin(); iter != Alliterset.end(); iter++)
    {
        V[*iter] = 'A' + countfalp;
        countfalp++;
    }

    for (auto iter = Alliterset.begin(); iter != Alliterset.end(); iter++)
    {
        string tempstr;
        string tempstr2;
        Map::iterator_set tempset;
        tempset.clear();
        tempset = iter->next( '0' );
        Map::iterator_set::iterator iterator;

        tempstr.clear();
        tempstr2.clear();
        tempstr = V[*iter];
        tempstr = tempstr + "->0";
        tempstr2 = V[*iterator];
        tempstr = tempstr + tempstr2;

        P.insert( P.end(), tempstr );


        tempset = iter->next( '1' );

        tempstr.clear();
        tempstr2.clear();
        tempstr = V[*iter];
        tempstr = tempstr + "->1";
        tempstr2 = V[*iterator];
        tempstr = tempstr + tempstr2;

        P.insert( P.end(), tempstr );

    }

    return;
}

void RG::printRG()
{
    cout << "RG = {V,T,S,P}" << endl;

    cout << "V = {";
    map<Map::iterator, char>::iterator it1;
    for (it1 = V.begin(); it1 != V.end(); it1++)
    {
        cout << it1->second << ",";
    }
    cout << "}" << endl;

    cout << "T = {";
    vector<char>::iterator it2;
    for (it2 = T.begin(); it2 != T.end(); it2++)
    {
        cout << *it2 << ",";
    }
    cout << "}" << endl;

    cout << "S = " << 'S' << endl;

    cout << "P = ";
    vector<string>::iterator it3;
    for (it3 = P.begin(); it3 != P.end(); it3++)
    {
        cout << *it3 << endl;
    }
    return;
}