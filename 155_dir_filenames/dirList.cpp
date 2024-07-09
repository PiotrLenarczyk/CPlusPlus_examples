#include <string>
#include <iostream>
#include <vector>
#include <filesystem> 

namespace fs=std::filesystem;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	std::string path = "/tmp";
	std::string file = "";
	std::vector<std::string> fileList;
	if ( fs::is_directory(path) )
	{	for (const auto & entry : fs::directory_iterator(path))
		{
			if (entry.is_directory()) //non-recursive file list
				continue;
			file = entry.path();
			fileList.push_back( file );
		};
		printf( "\"%s\" file list (%i files):\n", path.c_str(), (int)fileList.size() );	
		for ( int i = 0; i < fileList.size(); i++ )
			printf( "\t%s\n", fileList[i].c_str() );
	}else
		printf( "Path \"%s\" does not exist.\n", path.c_str() );
			
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
