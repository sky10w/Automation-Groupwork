#include "FAtoNFAwithEpsilon.hpp"

int main( int argc, char const* argv[] )
{
    ConvertFAtoNFAEpsilon test;
    test.testMidToPost( "01*(0+1)*1" );

    return 0;
}