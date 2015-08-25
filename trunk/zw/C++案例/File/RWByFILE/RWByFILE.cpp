/************************************************************************/
/* 说明：使用fopen操作文件。读，写	
/************************************************************************/
#include<stdio.h>
#include<string.h>
//写文件
void filewrite()
{
	char cFileName[100];
	char cFileContent[1024];
	FILE *file;
	printf("please input the file name you want to open or create:\r\n");
	scanf("%s",cFileName);
	file=fopen(cFileName,"wb");
	if (file)
	{
		printf("\r\nplease input the content you want to write to the file:\r\n");
		scanf("%s",cFileContent);
		fwrite(cFileContent,1,strlen(cFileContent),file);
	}
	fclose(file);
}
//文件读
void fileread()
{
	char cFileName[100];
	char cFileContent[1024];
	memset(cFileContent,0,1024);//冲0
	FILE *file;
	printf("please input the file name you want to read:\r\n");
	scanf("%s",cFileName);
	file=fopen(cFileName,"rb");
	if (file)
	{
		printf("the file content is:\r\n");
		fread(cFileContent,10,1,file);
		printf("%s",cFileContent);
	}
	fclose(file);
}
void main()
{
	//filewrite();
	fileread();
}