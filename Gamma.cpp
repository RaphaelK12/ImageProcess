#include <math.h>
#include "stdio.h"
#include "stdafx.h"
 
//typedef unsigned char UNIT8; //�� 8 λ�޷�������ʾ 0��255 ֮�������
unsigned char g_GammaLUT[256];
//ȫ�����飺����256��Ԫ�ص�gammaУ�����ұ�
//Buildtable()������0-255ִ�����²�����
//�ٹ�һ����Ԥ����������һ��;
//�ڽ�������� gamma ���ұ�
//�ӹ�ʽ��fPrecompensation=1/gamma

void BuildTable(float fPrecompensation )
{
	int i;
	float f;
	for( i=0;i<256;i++)
	{
		f=(i+0.5F)/256;						//normalization
		f=(float)pow(f,fPrecompensation);
		g_GammaLUT[i]=(unsigned char)(f*256-0.5F);  //unnormalization
	}
}
 
int GammaCorrection(unsigned char *src, int iWidth, int iHeight, float fGamma, unsigned char *Dst)
{
	printf("GammaCorrection, Gamma=%f\n",fGamma);

	int iCols,iRows;
	BuildTable(1/fGamma);//gamma LUT initialize

	if( src==NULL)
	{
		printf("input data is error!\n");
		return -1;
	}

	//correct pixel by pixel
	for(iRows=0; iRows<iHeight; iRows++)
	{
		for(iCols=0; iCols<iWidth; iCols++)
		{
			Dst[iRows*iWidth+iCols]=g_GammaLUT[src[iRows*iWidth+iCols]];
		}
	}
	return 0;
}