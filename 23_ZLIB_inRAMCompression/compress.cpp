// by DanRollins:
// https://www.experts-exchange.com/articles/3189/In-Memory-Compression-and-Decompression-Using-ZLIB.html
//STL
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "compress.hpp"


int main()
{
    BYTE pbSrc[]="hello hello hello hello there";

    //-------------- compress (save the original length)

    int nLenOrig= strlen( (char*)pbSrc )+1; // include terminating NULL
    int nLenDst= GetMaxCompressedLen( nLenOrig );
    BYTE* pbDst= new BYTE [nLenDst];  // alloc dest buffer

    int nLenPacked= CompressData( pbSrc, nLenOrig, pbDst, nLenDst );
    cout << "orig size: " << nLenOrig << endl;
    cout << "compressed size: " << nLenPacked << endl;
    if ( nLenPacked == -1 ) return(1);  // error

    //-------------- uncompress (uses the saved original length)

    BYTE* pbPacked=   pbDst;
    BYTE* pbUnpacked= new BYTE[ nLenOrig ];

    int nLen= UncompressData( pbPacked, nLenPacked, pbUnpacked, nLenOrig );
    cout << "uncompressed size: " << nLen << endl;

    // breakpoint here and view pbUnpacked to confirm
    delete pbDst;            // do some cleanup
    delete pbUnpacked;
    return 0; 
}
