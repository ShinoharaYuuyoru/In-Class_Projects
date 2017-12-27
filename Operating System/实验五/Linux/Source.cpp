#include <iostream>
#include <fstream>
#include <string>
#include <ftw.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

string SourceDir;
string TargetDir;

int myCopyFiles(const char* nowSourceDir, const struct stat * pStat, int typeFlag, struct FTW *pftw);

int main(int argc, char * argv[])
{
	if(argc != 3)
	{
		cout<<"argc Error!"<<endl;
		
		return 1;
	}
	
	SourceDir = argv[1];
	TargetDir = argv[2];
	
	nftw(SourceDir.c_str(), myCopyFiles, 512, FTW_PHYS);
}

int myCopyFiles(const char* nowSourceDir, const struct stat * pStat, int typeFlag, struct FTW *pftw)
{
	string nowTargetDir = TargetDir + &nowSourceDir[SourceDir.length()];	//Get full target directory
	
	switch(typeFlag)
	{
		case FTW_D:
		{
			/*If is a directory*/
			mkdir(nowTargetDir.c_str(), pStat->st_mode);
			break;
		}
		case FTW_F:
		{
			/*If is a normal file*/
			ifstream Source(nowSourceDir, ios::in);
			ofstream Target(nowTargetDir, ios::out);
			Target << Source.rdbuf();
			break;
		}
		case FTW_SL:
		{
			/*If is a symbolic link*/
			char linkPath[512];
			char currentWorkDir[512];
			
			readlink(nowSourceDir, linkPath, sizeof(linkPath));	//Read the link, get the LINK TO path
			getcwd(currentWorkDir, sizeof(currentWorkDir));	//Get current work directory
			chdir(TargetDir.c_str());	//Change work directory to Target root
			symlink(linkPath, &nowSourceDir[SourceDir.length() + 1]);	//Create link file. '+ 1' is because in Terminal, now work directory is changed, needn't '/' symbol
			chdir(currentWorkDir);	//Return to original work directory
			break;
		}
	}

	chmod(nowTargetDir.c_str(), pStat->st_mode);
	
	return 0;
}