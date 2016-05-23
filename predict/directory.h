#include <string>
using namespace std;

bool   ScanDirectory(  const string &src_dir_path, const string &file_extension,vector<string>& src_files);
const string getFileType( const string &filename );
vector<string> DirProcess(string dirPath);
