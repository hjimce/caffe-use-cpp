#include <iostream>
#include <cstring>

#include <dirent.h>
#include<vector>
using namespace std;

void FileHandle(string filePath)
{
    cout<<filePath<<endl;
}

vector<string> DirProcess(string dirPath)
{
	vector<string>fileall;
    DIR *pDir;
    struct dirent *pDirent;

    pDir = opendir(dirPath.c_str());
    if(pDir == NULL)
    {
        cout<<dirPath<<" is not directory..."<<endl;
        return fileall;
    }

    while((pDirent = readdir(pDir)) != NULL)
    {
        //ignore the hidden directory "." & ".."
        if(strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
            continue;

        //judge the directory entry is a directory or not
        if(pDirent->d_type == DT_DIR)
        {//recursive process the directory
            DirProcess(dirPath + '/' + pDirent->d_name);
        }
        else
        {
        	fileall.push_back(dirPath + '/' + pDirent->d_name);
             FileHandle(dirPath + '/' + pDirent->d_name);
        }
    }

    closedir(pDir);

    return fileall;
}
/*bool   ScanDirectory(  const string &src_dir_path,const string &file_extension,vector<string>& src_files)
{
    if (-1==_access( src_dir_path.c_str() ,0) )
    {
        return false;
    }

    _finddata_t fileInfo;
    intptr_t hFile;

    string dirName_filter = src_dir_path + string("\\") + string("*.*");

    if ( ( hFile = _findfirst( dirName_filter.c_str(), &fileInfo ) ) != -1 )
    {
        do
        {

            if ( !(fileInfo.attrib & _A_SUBDIR) )
            {

                if ( file_extension == string(".*") || getFileType(fileInfo.name)== file_extension )
                {
                    string filename = src_dir_path + string("\\") + string(fileInfo.name);
                    src_files.push_back(filename);


                }
            }

        } while (_findnext(hFile,&fileInfo) == 0);
        _findclose(hFile);
    }
    return true;
}
const string getFileType( const string &filename )
{

    string::size_type pos = filename.find_last_of( '.' );

    if ( pos != string::npos )
    {

        return string( filename, pos, string::npos );
    }
    else
    {
        // return null string
        return "";
    }
}*/
