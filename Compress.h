#ifndef COMPRESS_H
#define COMPRESS_H

struct HEAD
{
	char type[4];
	int length;
	int weight[256];
};
 

int Compress(const char *pFilename);
 
int InitHead(const char * pFilname, HEAD & sHead);
int Encode(const char *, char**, char *, const int);
char StrTobyte(const char * pBinStr);
int WriteFile(const char * pFilename, const HEAD sHead, const char * pBuffer, const int nSize);
int TestWeight(int weight[]);
 
#endif