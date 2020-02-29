#include "stdio.h"
#include "string.h"

#include "BMPOperation.h"
#include "def.h"

#define BYTE_PER_LINE(w,c)	(((((w))*(c)+31)/32)*4)

//save bmp
int save_bmp(unsigned char* buf,int width, int height, char* filepath)
{
	printf("save_bmp\n");

	FILE * bmpfile;
	bmpfile = fopen(filepath,"wb");
	if (!bmpfile) {
		fprintf (stderr, "Could not open file \"%s\".\n", filepath);
		return -1;
	}
	
	int pixelnum = width*height;

	int	m_nBitCount = 24;
	int m_nWidth = width;
	int m_nHeight = height;
	int nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);

	mBITMAPFILE bm;
	bm.bfType=0x4d42; //('M'*256+'B')&0xffff;
	bm.bfSize=(nByteWidth*m_nHeight)&0xffffffff;
	bm.bfReserved1=0;
	bm.bfReserved2=0;
	bm.bfOffBits=sizeof(mBITMAPFILE)+sizeof(mBITMAPINFO);
	//fwrite(&bm,sizeof(BYTE),sizeof(mBITMAPFILE), bmpfile);
	BYTE type[2] = {0x42, 0x4d};
	fwrite(type, 1, 2, bmpfile);

	BYTE size[4];
	size[0]=(nByteWidth*m_nHeight)&0xff;
	size[1]=((nByteWidth*m_nHeight)>>8)&0xff;
	size[2]=((nByteWidth*m_nHeight)>>16)&0xff;
	size[3]=((nByteWidth*m_nHeight)>>24)&0xff;
	fwrite(size, 1, 4, bmpfile);

	BYTE reserve[4] = {0 ,0 , 0, 0};
	fwrite(reserve, 1, 4, bmpfile);

	BYTE bits[4];
	bits[0]= (sizeof(mBITMAPFILE)+sizeof(mBITMAPINFO)-2)&0xff;
	bits[1]=((sizeof(mBITMAPFILE)+sizeof(mBITMAPINFO)-2)>>8)&0xff;
	bits[2]=((sizeof(mBITMAPFILE)+sizeof(mBITMAPINFO)-2)>>16)&0xff;
	bits[3]=((sizeof(mBITMAPFILE)+sizeof(mBITMAPINFO)-2)>>24)&0xff;
	fwrite(bits, 1, 4, bmpfile);

	mBITMAPINFO bmi;
	bmi.biSize=sizeof(mBITMAPINFO);
	bmi.biWidth=m_nWidth;
	bmi.biHeight=m_nHeight;
	bmi.biPlanes=1;
	bmi.biBitCount=m_nBitCount;
	bmi.biCompression=BI_RGB;
	bmi.biSizeImage=0;
	bmi.biXPelsPerMeter=0;
	bmi.biYPelsPerMeter=0;
	bmi.biClrUsed=0;
	bmi.biClrImportant=0;
	fwrite(&bmi,sizeof(BYTE),sizeof(mBITMAPINFO), bmpfile);	//
	//vertical flip

	BYTE *p1,*p2;
	BYTE pm[nByteWidth];
	memset(pm, 0, sizeof(pm));
	for(int y=0;y<m_nHeight/2;y++)
	{
		p1=buf+y*nByteWidth;
		p2=buf+(m_nHeight-y-1)*nByteWidth;
		memcpy(pm,p1,nByteWidth);
		memcpy(p1,p2,nByteWidth);
		memcpy(p2,pm,nByteWidth);
	}
	if (nByteWidth == 76) nByteWidth = 80;
	fwrite(buf,sizeof(unsigned char), nByteWidth*m_nHeight, bmpfile);	//
	fclose(bmpfile);

	return 0;
}


//read bmp
int read_bmp(char* filepath, unsigned char* buf,int width,int height)
{
	printf("read_bmp\n");
	FILE* bmpfile = fopen(filepath,"rb");
	if (!bmpfile) {
		fprintf (stderr, "Could not open file \"%s\".\n", filepath);
		return -1;
	}
	mBITMAPFILE bm;
	fread(&bm,sizeof(char),sizeof(mBITMAPFILE),bmpfile);
	mBITMAPINFO bmi;
	fread(&bmi,sizeof(char),sizeof(mBITMAPINFO),bmpfile);
	int m_nWidth = bmi.biWidth;
	width = m_nWidth;
	int m_nHeight = bmi.biHeight;
	height = m_nHeight;
	int	m_nBitCount = bmi.biBitCount;
	int nByteWidth=BYTE_PER_LINE(m_nWidth,m_nBitCount);

	memset(buf, 0, nByteWidth*m_nHeight);
	fread(buf, sizeof(unsigned char), nByteWidth*m_nHeight, bmpfile);
	
	//vertical flip
	//BYTE *p1,*p2,*pm;
	//BYTE pm[nByteWidth];
	//memset(pm, 0, sizeof(pm));
	//for (int y=0; y<m_nHeight/2; y++)
	//{
	//	p1=buf+y*nByteWidth;
	//	p2=buf+(m_nHeight-y-1)*nByteWidth;
	//	memcpy(pm,p1,nByteWidth);
	//	memcpy(p1,p2,nByteWidth);
	//	memcpy(p2,pm,nByteWidth);
	//}
	fclose(bmpfile);

	return 0;
}
