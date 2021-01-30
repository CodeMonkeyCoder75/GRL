#include "pch.h"
#include "CGRL.h"

GRL_Bool GRL_CInit() {
    FreeImage_Initialise(GRL_ZERO);
    return GRL_EXIT;
};

GRL_Void GRL_CLoadImg(struct GRL_Img* GRL, GRL_CNTCHR* GRL_File, GRL_Extenstions GRL_Flags) {
    FILE* f = fopen(GRL_File, "r");
    if (!f) {
        fclose(f);
        GRL_CPrintErrorMsgToConsole("Unfortunately for you, your image hasn't been found!");
    }
    else {
        fclose(f);
        GRL_CPrintMsgToConsole("Fortunately for you, your image has been found!");
        GRL->ImgData = FreeImage_Load(FreeImage_GetFileType(GRL_File, 0), GRL_File, GRL_Flags);
        if (GRL->ImgData == GRL_ZERO || !GRL->ImgData) {
            GRL_CPrintErrorMsgToConsole("Unfortunately for you, your image isn't loaded!");
        }
        else {
            GRL_CPrintMsgToConsole("lucky for you, your image is loaded!");
            GRL->ImgFile = GRL_File;
            GRL->ImgWidth = FreeImage_GetWidth(GRL->ImgData);
            GRL->ImgHeight = FreeImage_GetHeight(GRL->ImgData);
            GRL_CPrintMsg("%s\nThe width of the image is: %s\nThe height of the image is: %s\n", GRL_CGetImgFile(GRL), (GRL_CNTCHR*)GRL->ImgWidth, (GRL_CNTCHR*)GRL->ImgHeight);
        };
    };
};

GRL_Void GRL_CFreeImg(struct GRL_Img* GRL) {
    FreeImage_Unload(GRL->ImgData);
    GRL->ImgData = (FIBITMAP*)GRL_ZERO;
    GRL->ImgFile = (GRL_CNTCHR*)GRL_ZERO;
    GRL->ImgWidth = GRL_ZERO;
    GRL->ImgHeight = GRL_ZERO;
    GRL->ImgBits = (GRL_USCHR*)GRL_ZERO;
    GRL_CPrintMsgToConsole("Image data is freed!");
};

GRL_I8 GRL_CShutdown() {
    FreeImage_DeInitialise();
    return GRL_EXIT;
};

GRL_Void GRL_CSetImgToTexture(struct GRL_Texture* GRL_Text, struct GRL_Img* GRL) {
    GRL_CPrintMsgToConsole("Converting the image into a texture!");
    GRL_Text->ImgSrc = GRL;
    GRL_CPrintMsgToConsole("Successfully converted the image into a texture!");
};

GRL_Void GRL_CRenderTexture(struct GRL_Texture* GRL) {
    if (GRL->ImgSrc->ImgData == GRL_ZERO || !GRL->ImgSrc->ImgData) {
        GRL_CPrintErrorMsgToConsole("Cannot render the texture, there is no data!");
    }
    else {
        GRL_CPrintMsgToConsole("Rendering the texture now!");
        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(GRL->ImgSrc->ImgData);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
        FreeImage_Unload(pImage);
        nWidth = GRL_ZERO;
        nHeight = GRL_ZERO;
    };
};

GRL_Void GRL_CSetBufferToTexture(struct GRL_Texture* GRL_Texture, struct GRL_Buffer* GRL_Buffer) {
    if (!GRL_Buffer) {
        GRL_CPrintErrorMsgToConsole("Cannot get the buffer data!");
    }
    else {
        GRL_CPrintMsgToConsole("Got the buffer data!");
        GRL_Texture->BufferInfo = GRL_Buffer;
        GRL_CPrintMsgToConsole("Successfully copied the buffer data to the texture object!");
        GRL_CShutdownBufferForApp(GRL_Buffer);
        GRL_CShutdownTextureForRendering(GRL_Buffer);
    };
};

GRL_Void GRL_CSetupTextureForRendering(GRL_I8 GRL_TextureNums, struct GRL_Buffer* GRL_Buffer) {
    GRL_Buffer->TextureNum = GRL_TextureNums;
    GRL_CPrintMsgToConsole("Generating textures now!");
    glGenTextures(GRL_Buffer->TextureNum, &GRL_Buffer->TextureId);
    GRL_CPrintMsgToConsole("Binding textures now!");
    glBindTexture(GL_TEXTURE_2D, GRL_Buffer->TextureId);
    GRL_CPrintMsgToConsole("Texture is ready to be rendered!");
};

GRL_Void GRL_CShutdownBufferForApp(struct GRL_Buffer* GRL_Buffer) {
    GRL_CPrintMsgToConsole("Deleting the given buffer now!");
    glDeleteBuffers(GRL_Buffer->BufferNum, &GRL_Buffer->BufferId);
    GRL_CPrintMsgToConsole("The given buffer is now deleted!");
    GRL_Buffer->BufferId = GRL_ZERO;
    GRL_Buffer->BufferNum = GRL_ZERO;
};

GRL_Void GRL_CShutdownTextureForRendering(struct GRL_Buffer* GRL_Buffer) {
    GRL_CPrintMsgToConsole("Deleting the given texture now!");
    glDeleteTextures(GRL_Buffer->TextureNum, &GRL_Buffer->TextureId);
    GRL_CPrintMsgToConsole("The given texture is now deleted!");
    GRL_Buffer->TextureId = GRL_ZERO;
    GRL_Buffer->TextureNum = GRL_ZERO;
};

GRL_USCHR* GRL_CGetImgBits(struct GRL_Img* GRL) {
    if (!GRL->ImgData || GRL->ImgData == GRL_ZERO) {
        GRL_CPrintErrorMsgToConsole("Cannot get the image data!");
    }
    else {
        GRL_CPrintMsgToConsole("Got the image data!");
        GRL->ImgBits = FreeImage_GetBits(GRL->ImgData);
        GRL_CPrintMsg("The bits of the image are : %s\n", GRL->ImgBits);
    };
    return GRL->ImgBits;
};

GRL_CNTCHR* GRL_CGetImgFile(struct GRL_Img* GRL) {
    GRL_CPrintMsg("The location of the image file is: %s\n", GRL->ImgFile);
    return GRL->ImgFile;
};

GRL_CNTCHR* GRL_CSetImgFile(struct GRL_Img* GRL, GRL_CNTCHR* GRL_File) {
    if (GRL->ImgFile != GRL_ZERO) {
        GRL_CPrintErrorMsgToConsole("Cannot set the image file, because there already exits an image file!");
        return GRL_ZERO;
    }
    else {
        GRL_CPrintMsgToConsole("Setting the image file now!");
        GRL->ImgFile = GRL_File;
        GRL_CPrintMsgToConsole("The image file is successfully set to the image object!");
    };
    return GRL->ImgFile;
};

GRL_CNTCHR* GRL_CPrint(GRL_CNTCHR* _msg) {
    GRL_CPrintMsg("%s\n", _msg);
    return _msg;
};

GRL_CNTCHR* GRL_CGetErr(GRL_CNTCHR* _err) {
    GRL_CPrintMsg("Error: %s\n", _err);
    return _err;
};
