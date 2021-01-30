#ifndef CGRL_H
#define CGRL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Engine/FreeImage/FreeImage.h"
#include "Engine/GL/glew.h"

//Macros
#define CGRL_Export  extern __declspec(dllexport)
#define GRL_CPrintErrorMsgToConsole GRL_CGetErr
#define GRL_CPrintMsgToConsole GRL_CPrint
#define GRL_CPrintMsg printf

#define GRL_CPrintVariableInMemory(X) \
        GRL_CPrintMsg("This variable is located at: %p\n", X) \

//Integers
typedef int GRL_I8;
typedef int GRL_I32;
typedef int GRL_I64;

//Signed integers
typedef signed int GRL_SI8;
typedef signed int GRL_SI32;
typedef signed int GRL_SI64;

//Unsigned integers
typedef unsigned int GRL_USI8;
typedef unsigned int GRL_USI32;
typedef unsigned int GRL_USI64;

//Const integers
typedef const int GRL_CNTI8;
typedef const int GRL_CNTI32;
typedef const int GRL_CNTI64;

//Short
typedef short GRL_SHRT;

//Signed short
typedef signed short GRL_SSHRT;

//Unsigned short
typedef unsigned short GRL_USSHRT;

//Const short
typedef const short GRL_CNTSHRT;

//Double
typedef double GRL_DBL;

//Const double
typedef const double GRL_CNTDBL;

//Boolean
typedef bool GRL_Bool;
#define GRL_ERROR -1
#define GRL_FALSE 0
#define GRL_TRUE 1
#define GRL_ZERO GRL_FALSE
#define GRL_EXIT GRL_FALSE

//Char
typedef char GRL_CHR;

//Signed char
typedef signed char GRL_SCHR;

//Unsigned char
typedef unsigned char GRL_USCHR;

//Const char
typedef const char GRL_CNTCHR;

//Void
typedef void GRL_Void;

//Data
typedef const void* GRL_Data;

//End

//Type definition
typedef enum GRL_Extenstions {
    GRL_ExtUnkown = FIF_UNKNOWN,
    GRL_ExtBMP = FIF_BMP,
    GRL_ExtICO = FIF_ICO,
    GRL_ExtJPEG = FIF_JPEG,
    GRL_ExtPNG = FIF_PNG,
    GRL_ExtTIFF = FIF_TIFF,
    GRL_ExtGIF = FIF_GIF,
    GRL_ExtHDR = FIF_HDR
} GRL_Extenstions;

//Type definition
struct GRL_Img;

typedef struct GRL_Img {
    FIBITMAP* ImgData;
    GRL_USI8 ImgWidth;
    GRL_USI8 ImgHeight;
    GRL_USCHR* ImgBits;
    GRL_CNTCHR* ImgFile;
} GRL_Img;

//Type definition
struct GRL_Buffer;

typedef struct GRL_Buffer {
    GRL_I8 TextureNum;
    GRL_USI8 TextureId;
    GRL_I8 BufferNum;
    GRL_USI8 BufferId;
} GRL_Buffer;

//Type definition
struct GRL_Texture;

typedef struct GRL_Texture {
    struct GRL_Img* ImgSrc;
    struct GRL_Buffer* BufferInfo;
} GRL_Texture;

CGRL_Export GRL_Bool GRL_CInit();

CGRL_Export GRL_Void GRL_CLoadImg(struct GRL_Img* GRL, GRL_CNTCHR* GRL_File, GRL_Extenstions GRL_Flags);

CGRL_Export GRL_Void GRL_CFreeImg(struct GRL_Img* GRL);

CGRL_Export GRL_I8 GRL_CShutdown();

CGRL_Export GRL_Void GRL_CSetImgToTexture(struct GRL_Texture* GRL_Text, struct GRL_Img* GRL);

CGRL_Export GRL_Void GRL_CRenderTexture(struct GRL_Texture* GRL);

CGRL_Export GRL_Void GRL_CFreeTexture(struct GRL_Texture* GRL);

CGRL_Export GRL_Void GRL_CSetBufferToTexture(struct GRL_Texture* GRL_Texture, struct GRL_Buffer* GRL_Buffer);

CGRL_Export GRL_Void GRL_CSetupBufferForApp(GRL_I8 GRL_BufferNums, struct GRL_Buffer* GRL_Buffer);

CGRL_Export GRL_Void GRL_CShutdownBufferForApp(struct GRL_Buffer* GRL_Buffer);

CGRL_Export GRL_Void GRL_CSetupTextureForRendering(GRL_I8 GRL_TextureNums, struct GRL_Buffer* GRL_Buffer);

CGRL_Export GRL_Void GRL_CShutdownTextureForRendering(struct GRL_Buffer* GRL_Buffer);

CGRL_Export GRL_USCHR* GRL_CGetImgBits(struct GRL_Img* GRL);

CGRL_Export GRL_CNTCHR* GRL_CGetImgFile(struct GRL_Img* GRL);

CGRL_Export GRL_CNTCHR* GRL_CSetImgFile(struct GRL_Img* GRL, GRL_CNTCHR* GRL_File);

CGRL_Export GRL_CNTCHR* GRL_CPrint(GRL_CNTCHR* _msg);

CGRL_Export GRL_CNTCHR* GRL_CGetErr(GRL_CNTCHR* _err);

#endif