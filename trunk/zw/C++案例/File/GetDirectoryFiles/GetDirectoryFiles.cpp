//////////////////////////////////////////////////////////////////////////
//说明：获取指定文件夹下文件的列表，和文件大小
//////////////////////////////////////////////////////////////////////////
#include<windows.h>
#include <stdio.h>
#include<iostream>
#include<string>
using namespace std;
void main()
{
	string strFiles;
	WIN32_FIND_DATA fdata;
	BOOL bFinished=FALSE;
	int nIndex=0;
	string path="files";
	string fileName=path+"\\*.*";
	HANDLE hSearch=FindFirstFile((LPCTSTR)fileName.c_str(),&fdata);
	if(hSearch == INVALID_HANDLE_VALUE)    
	{
        return;
	}
	while(!bFinished)  
    {  
        if(!(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
			strFiles+=fdata.cFileName;
			char temp[32];
			sprintf(temp,"%u",fdata.nFileSizeLow);
			strFiles+="    ";
			strFiles+=temp;
			strFiles+="\r\n";
            nIndex++;
        }
        
        if(!FindNextFile(hSearch, &fdata))    
        {  
            if (GetLastError() == ERROR_NO_MORE_FILES)    
                bFinished = TRUE;  
        }    
    }
    FindClose(hSearch);
	printf("%s",strFiles.c_str());
}
