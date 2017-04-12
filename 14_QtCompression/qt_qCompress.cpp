//STL
#include <iostream>
#include <stdlib.h>
//Qt
#include <QFile>

using namespace std;

int main()
{

    QString filename = "outputCMP.txt.7z";
    QString command = "rm ";
    command.append( filename );
    int out = system( qPrintable( command ) ); if ( out != 0 ) { cerr << "Delete file error!" << endl; return -1;}
    QFile file( filename );
    if ( !file.open( QIODevice::WriteOnly ) ) {
        cerr << "File open error " << filename.toStdString() << endl;
        return 0;
    }
    //COMPRESSION
    QByteArray list;
    list.append( "aaaa" ).append( " " ).append( "1.1" ).append( "\n" );
    list.append( "bbbbbbb" ); list.append( " " ).append( "2.51" ).append( "\n" );
    list.chop( 1 ); //delete newline character
    list = qCompress( list );
    file.write( list );
    file.close();
    
    //UNCOMPRESSION
    QFile fileRead( filename );
    if ( !fileRead.open( QIODevice::ReadOnly ) ) {
        cerr << "File open error " << filename.toStdString() << endl;
        return 0;
    }
    QByteArray listRead = fileRead.readAll();
    listRead = qUncompress( listRead );
    cout << "listRead: \n" << QString(listRead).toStdString() << endl;
    
    fileRead.close();
    return 0;
}
