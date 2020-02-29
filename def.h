#define BI_RGB		   0
#define BI_RLE8 	   1
#define BI_RLE4 	   2
#define BI_BITFIELDS   3
#define BI_JPEG 	   4
#define BI_PNG		   5


typedef char           CHAR;
typedef short          SHORT;
typedef unsigned int   LONG;
typedef unsigned int   DWORD;
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef float          FLOAT;
typedef int            INT;
typedef unsigned int   UINT;

typedef unsigned int   UINT32;
typedef unsigned int   UINT32;
typedef unsigned char  UINT8;
typedef unsigned short UINT16;

typedef struct tagFILE{
    WORD      bfType;
    DWORD     bfSize;
    WORD      bfReserved1;
    WORD      bfReserved2;
    DWORD     bfOffBits;
} mBITMAPFILE;

typedef struct tagINFO{
    DWORD      biSize;
    LONG       biWidth;
    LONG       biHeight;
    WORD       biPlanes;
    WORD       biBitCount;
    DWORD      biCompression;
    DWORD      biSizeImage;
    LONG       biXPelsPerMeter;
    LONG       biYPelsPerMeter;
    DWORD      biClrUsed;
    DWORD      biClrImportant;
} mBITMAPINFO;