#include "FAtoNFAwithEpsilon.hpp"

int main( int argc, char const* argv[] )
{
    ConvertFAtoNFAEpsilon test;
    test.testMidToPost( "01*" );

    return 0;
}