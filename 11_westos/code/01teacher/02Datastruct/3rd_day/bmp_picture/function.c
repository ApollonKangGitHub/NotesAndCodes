#include "bmp.h"

int checkPath(char *path)
{
    FILE *fd;
    int len=strlen(path)/sizeof(char);
    char ext[3];

    strncpy(ext,&path[len-3],3);
    if(!(ext[0]=='b'&&ext[1]=='m'&&ext[2]=='p'))
    {
        printf("Error(checkPath): the extension of the file is not bmp.\n");
        return -1;
    }

    fd=fopen(path,"r");
    if(!fd)
    {
        printf("Error(checkPath): can not open the file.\n");
        return -1;
    }
    fclose(fd);

    return 0;
}

int readBmpFileHeader(char *path,BITMAPFILEHEADER *bmfh)
{
    int ret;
    FILE *fd;

    ret=checkPath(path);
    if(ret==-1)
    {
        printf("Error(readBmpFileHeader): the path of the image is invalid.\n");
        return -1;
    }

    fd=fopen(path,"rb");
    if(fd==0)
    {
        printf("Error(readBmpFileHeader): can not open the image.\n");
        return -1;
    }

    if(fread(&bmfh->bfType,sizeof(WORD),1,fd)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfType of the File Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmfh->bfSize,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfSize of the File Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmfh->bfReserved1,sizeof(WORD),1,fd)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfReserved1 of the File Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmfh->bfReserved2,sizeof(WORD),1,fd)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfReserved2 of the File Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmfh->bfOffBits,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpFileHeader): can not read the bfOffBits of the File Header.\n");
        fclose(fd);
        return -1;
    }

    fclose(fd);
    return 0;
}

int readBmpInfoHeader(char *path,BITMAPINFOHEADER *bmih)
{
    FILE *fd;
    int ret;

    ret=checkPath(path);
    if(ret==-1)
    {
        printf("Error(readBmpInfoHeader): the path of the image is invalid.\n");
        return -1;
    }

    fd=fopen(path,"rb");
    if(fd==0)
    {
        printf("Error(readBmpInfoHeader): can not open the file.\n");
        return -1;
    }

    fseek(fd,14,SEEK_SET);

    if(fread(&bmih->biSize,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biSize of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biWidth,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biWidth of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biHeight,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biHeight of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biPlanes,sizeof(WORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biPlanes of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biBitCount,sizeof(WORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biBitCount of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biCompression,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biCompression of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biSizeImage,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biSizeImage of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biXPelsPerMeter,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biXPelsPerMeter of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biYPelsPerMeter,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biYPelsPerMeter of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biClrUsed,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biClrUsed of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    if(fread(&bmih->biClrImportant,sizeof(DWORD),1,fd)!=1)
    {
        printf("Error(readBmpInfoHeader): can not read the biClrImportant of the Info Header.\n");
        fclose(fd);
        return -1;
    }

    fclose(fd);
    return 0;
}

int readBmpPixelData(char *path,BYTE *imgData)
{
    FILE *fd;
    int ret;
    BYTE *data;
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;
    DWORD sizeImage;

    ret=checkPath(path);
    if(ret==-1)
    {
        printf("Error(readBmpPixelData): the path of the image is invalid.\n");
        return -1;
    }

    ret=readBmpFileHeader(path,&bmfh);
    if(ret==-1)
    {
        printf("Error(readBmpPixelData): can not read the File Header.\n");
        return -1;
    }

    ret=readBmpInfoHeader(path,&bmih);
    if(ret==-1)
    {
        printf("Error(readBmpPixelData): can not read the Info Header.\n");
        return -1;
    }
   
    sizeImage=bmih.biHeight*((int)((bmih.biWidth*bmih.biBitCount+31)/32)*4)*sizeof(BYTE);
    data=(BYTE*)malloc(sizeImage);
    if(!data)
    {
        printf("Error(readBmpPixelData): can not allocate temporary memory.\n");
        return -1;
    }

    fd=fopen(path,"rb");
    if(!fd)
    {
        printf("Error(readBmpPixelData): can not open the image.\n");
        free(data);
        return -1;
    }
    fseek(fd,bmfh.bfOffBits,SEEK_SET);

    ret=fread(data,sizeof(BYTE)*sizeImage,1,fd);
    if(ret==0)
    {
        if(feof(fd))
        {
        }
        if(ferror(fd))
        {
            printf("Error(readBmpPixelData): can not read the pixel data.\n");
            free(data);
            fclose(fd);
            return -1;
        }
    }

    memcpy(imgData,data,sizeImage);

    free(data);
    fclose(fd);
    return 0;
}

int printBmpFileHeader(char *path)
{
    BITMAPFILEHEADER bmfh;
    int ret;

    ret=checkPath(path);
    if(ret==-1)
    {
        printf("Error(printBmpFileHeader): the path is invalid.\n");
        return -1;
    }

    ret=readBmpFileHeader(path,&bmfh);
    if(ret==-1)
    {
        printf("Error(printBmpFileHeader): can not read the File Header.\n");
        return -1;
    }

    printf("-----The content of the File Header-----\n");
    printf("\t bfType : %d\n",bmfh.bfType);
    printf("\t bfSize : %ld\n",bmfh.bfSize);
    printf("\t bfReserved1 : %d\n",bmfh.bfReserved1);
    printf("\t bfReserved2 : %d\n",bmfh.bfReserved2);
    printf("\t bfOffBits : %ld\n",bmfh.bfOffBits);

    return 0;
}

int printBmpInfoHeader(char *path)
{
    BITMAPINFOHEADER bmih;
    int ret;

    ret=checkPath(path);
    if(ret==-1)
    {
        printf("Error(printBmpInfoHeader): the path is invalid.\n");
        return -1;
    }

    ret=readBmpInfoHeader(path,&bmih);
    if(ret==-1)
    {
        printf("Error(printBmpInfoHeader): can not read the Info Header.\n");
        return -1;
    }

    printf("-----The content of the Info Header-----\n");
    printf("\t biSize : %ld\n",bmih.biSize);
    printf("\t biWidth : %ld\n",bmih.biWidth);
    printf("\t biHeight : %ld\n",bmih.biHeight);
    printf("\t biPlanes : %d\n",bmih.biPlanes);
    printf("\t biBitCount : %d\n",bmih.biBitCount);
    printf("\t biCompression : %ld\n",bmih.biCompression);
    printf("\t biSizeImage : %ld\n",bmih.biSizeImage);
    printf("\t biXPelsPerMeter : %ld\n",bmih.biXPelsPerMeter);
    printf("\t biYPelsPerMeter : %ld\n",bmih.biYPelsPerMeter);
    printf("\t biClrUsed : %ld\n",bmih.biClrUsed);
    printf("\t biClrImportant : %ld\n",bmih.biClrImportant);

    return 0;
}
int printMenu()
{
    int ret;
    printf("-----Choose a menu item-----\t\n");
    printf("1. Print File Header        \t\n");
    printf("2. Print Info Header        \t\n");
    printf("3. Save As the image        \t\n");
    printf("0. Exit                 \t\n");
    scanf("%d",&ret);
    if(ret>=0 && ret<=3)
    {
        return ret;
    }
    else
    {
        return 0;
    }
}

int saveBmpFileHeader(FILE *fp,BITMAPFILEHEADER *bmfh)
{
    if(fwrite(&bmfh->bfType,sizeof(WORD),1,fp)!=1)
    {
        printf("Error(saveBmpFileHeader): can not write bfType of the File Header.\n");
        return -1;
    }

    if(fwrite(&bmfh->bfSize,sizeof(DWORD),1,fp)!=1)
    {
        printf("Error(saveBmpFileHeader): can not write bfSize of the File Header.\n");
        return -1;
    }

    if(fwrite(&bmfh->bfReserved1,sizeof(WORD),1,fp)!=1)
    {
        printf("Error(saveBmpFileHeader): can not write bfReserved1 of the File Header.\n");
        return -1;
    }

    if(fwrite(&bmfh->bfReserved2,sizeof(WORD),1,fp)!=1)
    {
        printf("Error(saveBmpFileHeader): can not write bfReserved2 of the File Header.\n");
        return -1;
    }

    if(fwrite(&bmfh->bfOffBits,sizeof(DWORD),1,fp)!=1)
    {
        printf("Error(saveBmpFileHeader): can not write bfOffBits of the File Header.\n");
        return -1;
    }

    return 0;
}

int saveBmpInfoHeader(FILE *fp,BITMAPINFOHEADER *bmih)
{
    if(fwrite(&bmih->biSize,sizeof(DWORD),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biSize of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biWidth,sizeof(LONG),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biWidth of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biHeight,sizeof(LONG),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biHeight of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biPlanes,sizeof(WORD),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biPlanes of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biBitCount,sizeof(WORD),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biBitCount of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biCompression,sizeof(DWORD),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biCompression of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biSizeImage,sizeof(DWORD),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biSizeImage of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biXPelsPerMeter,sizeof(LONG),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biXPelsPerMeter of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biYPelsPerMeter,sizeof(LONG),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biYPelsPerMeter of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biClrUsed,sizeof(DWORD),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biClrUsed of the Info Header.\n");
        return -1;
    }

    if(fwrite(&bmih->biClrImportant,sizeof(DWORD),1,fp)!=1)
    {
        printf("Error(saveBmpInfoHeader): can not write biClrImportant of the Info Header.\n");
        return -1;
    }

    return 0;
}

int saveBmpClrPalette(FILE *fp)
{
    RGBQUAD pal[256];
    int i;

    for(i=0;i<256;i++)
    {
        pal[i].rgbBlue=i;
        pal[i].rgbGreen=i;
        pal[i].rgbRed=i;
        pal[i].rgbReserved=0;
    }

    if(fwrite(pal,sizeof(RGBQUAD)*256,1,fp)!=1)
    {
        printf("Error(saveBmpClrPalette): can not write Color Palette.\n");
        return -1;
    }

    return 0;
}

int saveBmp(char *Newpath,char *Oldpath)
{
    int ret;
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;
    BYTE *img;
    FILE *fp;

    ret=readBmpFileHeader(Oldpath,&bmfh);
    if(ret==-1)
    {
        printf("Error(saveBmp): can not read the File Header.\n");
        return -1;
    }

    ret=readBmpInfoHeader(Oldpath,&bmih);
    if(ret==-1)
    {
        printf("Error(saveBmp): can not read the Info Header.\n");
        return -1;
    }

    img=(BYTE*)malloc(bmih.biHeight*(bmih.biWidth*bmih.biBitCount+31)/32*4*sizeof(BYTE));
    if(!img)
    {
        printf("Error(saveBmp): can not allocate memory for the image.\n");
        return -1;
    }

    ret=readBmpPixelData(Oldpath,img);
    if(ret==-1)
    {
        printf("Error(saveBmp): can not read the pixel data.\n");
        free(img);
        return -1;
    }

    fp=fopen(Newpath,"wb");
    if(!fp)
    {
        printf("Error(saveBmp): can not open the file.\n");
        free(img);
        return -1;
    }

    ret=saveBmpFileHeader(fp,&bmfh);
    if(ret==-1)
    {
        printf("Error(saveBmp): can not write the File Header.\n");
        free(img);
        fclose(fp);
        return -1;
    }

    ret=saveBmpInfoHeader(fp,&bmih);
    if(ret==-1)
    {
        printf("Error(saveBmp): can not write the Info Header.\n");
        free(img);
        fclose(fp);
        return -1;
    }

    if(bmih.biBitCount==8)
    {
        ret=saveBmpClrPalette(fp);
        if(ret==-1)
        {
            printf("Error(saveBmp): can not write the Color Palette.\n");
            free(img);
            fclose(fp);
            return -1;
        }
    }

    if(bmih.biBitCount!=8 && bmih.biBitCount!=24)
    {
        printf("Error(saveBmp): only supported 8 or 24 bits.\n");
        free(img);
        fclose(fp);
        return -1;
    }

    ret=fwrite(img,bmih.biHeight*(bmih.biWidth*bmih.biBitCount+31)/32*4*sizeof(BYTE),1,fp);
    if(ret!=1)
    {
        printf("Error(saveBmp): can not write the pixel data.\n");
        free(img);
        fclose(fp);
        return -1;
    }

    free(img);
    fclose(fp);
    return 0;
}




